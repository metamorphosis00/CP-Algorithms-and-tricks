#!/usr/bin/env python3
"""
Cross-platform local stress tester for competitive programming.
Works on macOS, Linux, Windows (with g++/clang++ and Python 3).

Modes:
  compare  - generator + solution vs brute (default)
  check    - generator + solution + custom checker (for multiple correct answers)
  interactive - solution vs interactor (basic support)

Usage examples:
  python3 stress.py --mode compare --tests 1000 --timeout 2
  python3 stress.py -m check -t 500
  python3 stress.py -m interactive --tests 50
"""

import argparse
import os
import sys
import subprocess
import shutil
import time
import tempfile
from pathlib import Path
from typing import Optional, Tuple

# ============== Colors ==============
class C:
    RESET = "\033[0m"
    RED = "\033[91m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    BLUE = "\033[94m"
    CYAN = "\033[96m"
    BOLD = "\033[1m"

def color(s: str, c: str) -> str:
    if not sys.stdout.isatty():
        return s
    return f"{c}{s}{C.RESET}"

# ============== Config ==============
DEFAULT_FILES = {
    "solution": "solution.cpp",
    "brute": "brute.cpp",
    "generator": "generator.cpp",
    "checker": "checker.cpp",
    "interactor": "interactor.cpp",
    "validator": "validator.cpp",
}

CXX_FLAGS = ["-std=c++17", "-O2", "-Wall", "-Wextra", "-Wno-unused-result"]
TIMEOUT_DEFAULT = 2.0  # seconds

def find_compiler() -> str:
    for cand in [os.environ.get("CXX"), "g++", "clang++", "c++"]:
        if cand and shutil.which(cand):
            return cand
    print(color("Error: no C++ compiler found (g++ / clang++). Install Xcode CLI tools or brew install gcc.", C.RED))
    sys.exit(1)

def compile_cpp(src: Path, out: Path, compiler: str) -> bool:
    if not src.exists():
        print(color(f"Missing source: {src}", C.RED))
        return False
    cmd = [compiler] + CXX_FLAGS + [str(src), "-o", str(out)]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=30)
        if r.returncode != 0:
            print(color(f"Compilation failed for {src.name}:", C.RED))
            print(r.stderr)
            return False
        return True
    except Exception as e:
        print(color(f"Compile error: {e}", C.RED))
        return False

def run_binary(bin_path: Path, input_data: Optional[str] = None,
               timeout: float = TIMEOUT_DEFAULT, args: list = None) -> Tuple[int, str, str, float]:
    """Returns (returncode, stdout, stderr, elapsed)"""
    cmd = [str(bin_path)]
    if args:
        cmd += args
    try:
        start = time.perf_counter()
        proc = subprocess.run(
            cmd,
            input=input_data,
            capture_output=True,
            text=True,
            timeout=timeout,
        )
        elapsed = time.perf_counter() - start
        return proc.returncode, proc.stdout, proc.stderr, elapsed
    except subprocess.TimeoutExpired:
        return -1, "", "TLE", timeout
    except Exception as e:
        return -2, "", str(e), 0.0

def normalize_output(s: str) -> str:
    """Trim trailing whitespace on each line and remove trailing empty lines."""
    lines = [line.rstrip() for line in s.splitlines()]
    while lines and lines[-1] == "":
        lines.pop()
    return "\n".join(lines)

def save_fail(test_id: int, inp: str, sol_out: str, brute_out: str = "",
              extra: str = "", work_dir: Path = Path(".")):
    fail_dir = work_dir / "fails"
    fail_dir.mkdir(exist_ok=True)
    (fail_dir / f"fail_{test_id}.in").write_text(inp, encoding="utf-8")
    (fail_dir / f"fail_{test_id}.sol").write_text(sol_out, encoding="utf-8")
    if brute_out:
        (fail_dir / f"fail_{test_id}.brute").write_text(brute_out, encoding="utf-8")
    if extra:
        (fail_dir / f"fail_{test_id}.info").write_text(extra, encoding="utf-8")
    print(color(f"  Saved to {fail_dir}/fail_{test_id}.*", C.YELLOW))

# ============== Modes ==============
def mode_compare(args, bins, work_dir: Path):
    gen_bin, sol_bin, brute_bin = bins["generator"], bins["solution"], bins["brute"]
    passed = 0
    for i in range(1, args.tests + 1):
        # Generate
        seed = str(args.seed + i) if args.seed is not None else None
        gen_args = [seed] if seed else []
        rc, inp, err, _ = run_binary(gen_bin, timeout=5.0, args=gen_args)
        if rc != 0:
            print(color(f"[{i}] Generator failed (rc={rc}): {err}", C.RED))
            save_fail(i, inp, "", extra=err, work_dir=work_dir)
            return False

        # Optional validator
        if bins.get("validator"):
            vrc, _, verr, _ = run_binary(bins["validator"], input_data=inp, timeout=2.0)
            if vrc != 0:
                print(color(f"[{i}] Validator rejected test: {verr}", C.YELLOW))
                continue  # skip invalid generated test

        # Run solution
        src, sout, serr, stime = run_binary(sol_bin, input_data=inp, timeout=args.timeout)
        if src == -1:
            print(color(f"[{i}] TLE on solution ({args.timeout}s)", C.RED))
            save_fail(i, inp, sout, extra="TLE", work_dir=work_dir)
            return False
        if src != 0:
            print(color(f"[{i}] RE on solution (rc={src}): {serr}", C.RED))
            save_fail(i, inp, sout + "\n" + serr, extra="RE", work_dir=work_dir)
            return False

        # Run brute
        brc, bout, berr, btime = run_binary(brute_bin, input_data=inp, timeout=max(args.timeout * 5, 10.0))
        if brc != 0:
            print(color(f"[{i}] Brute failed (rc={brc}): {berr}", C.RED))
            save_fail(i, inp, sout, bout, extra="brute RE/TLE", work_dir=work_dir)
            return False

        nsol = normalize_output(sout)
        nbrute = normalize_output(bout)
        if nsol != nbrute:
            print(color(f"[{i}] WA", C.RED))
            print(color("=== Input ===", C.CYAN))
            print(inp[:2000] + ("..." if len(inp) > 2000 else ""))
            print(color("=== Solution ===", C.CYAN))
            print(nsol[:1500] + ("..." if len(nsol) > 1500 else ""))
            print(color("=== Brute ===", C.CYAN))
            print(nbrute[:1500] + ("..." if len(nbrute) > 1500 else ""))
            save_fail(i, inp, sout, bout, work_dir=work_dir)
            return False

        passed += 1
        if i % 50 == 0 or i == args.tests:
            print(color(f"[{i}/{args.tests}] OK  (sol {stime:.3f}s, brute {btime:.3f}s)", C.GREEN))

    print(color(f"\nAll {passed} tests passed!", C.GREEN + C.BOLD))
    return True


def mode_check(args, bins, work_dir: Path):
    """Custom checker: receives input + sol_out (+ brute_out if exists). Exit 0 = OK."""
    gen_bin, sol_bin, checker_bin = bins["generator"], bins["solution"], bins["checker"]
    brute_bin = bins.get("brute")
    passed = 0
    for i in range(1, args.tests + 1):
        seed = str(args.seed + i) if args.seed is not None else None
        gen_args = [seed] if seed else []
        rc, inp, err, _ = run_binary(gen_bin, timeout=5.0, args=gen_args)
        if rc != 0:
            print(color(f"[{i}] Generator failed: {err}", C.RED))
            return False

        if bins.get("validator"):
            vrc, _, verr, _ = run_binary(bins["validator"], input_data=inp, timeout=2.0)
            if vrc != 0:
                continue

        src, sout, serr, stime = run_binary(sol_bin, input_data=inp, timeout=args.timeout)
        if src == -1:
            print(color(f"[{i}] TLE", C.RED))
            save_fail(i, inp, sout, extra="TLE", work_dir=work_dir)
            return False
        if src != 0:
            print(color(f"[{i}] RE: {serr}", C.RED))
            save_fail(i, inp, sout, extra="RE", work_dir=work_dir)
            return False

        bout = ""
        if brute_bin:
            brc, bout, _, _ = run_binary(brute_bin, input_data=inp, timeout=max(args.timeout * 5, 10))
            if brc != 0:
                bout = ""

        # Checker protocol: we pass files as arguments or via stdin.
        # Simple protocol used here: checker <input_file> <sol_out_file> [brute_out_file]
        # Checker should exit 0 if OK, non-zero otherwise. Can print reason to stderr.
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            (tmp / "in.txt").write_text(inp)
            (tmp / "sol.txt").write_text(sout)
            chk_args = [str(tmp / "in.txt"), str(tmp / "sol.txt")]
            if bout:
                (tmp / "brute.txt").write_text(bout)
                chk_args.append(str(tmp / "brute.txt"))
            crc, cout, cerr, _ = run_binary(checker_bin, args=chk_args, timeout=5.0)
            if crc != 0:
                print(color(f"[{i}] WA (checker)", C.RED))
                print(color("=== Input ===", C.CYAN))
                print(inp[:2000])
                print(color("=== Solution output ===", C.CYAN))
                print(sout[:1500])
                if cerr:
                    print(color("=== Checker message ===", C.CYAN))
                    print(cerr)
                save_fail(i, inp, sout, bout, extra=cerr, work_dir=work_dir)
                return False

        passed += 1
        if i % 50 == 0 or i == args.tests:
            print(color(f"[{i}/{args.tests}] OK  ({stime:.3f}s)", C.GREEN))

    print(color(f"\nAll {passed} tests passed!", C.GREEN + C.BOLD))
    return True


def mode_interactive(args, bins, work_dir: Path):
    """
    Basic interactive support.
    Interactor and solution communicate via pipes.
    Interactor should:
      - generate secret / test
      - interact (read queries from sol, write answers)
      - at the end exit 0 if solution is correct, non-zero otherwise
      - print diagnostic to stderr
    Solution must flush output (endl / cout.flush()).
    """
    sol_bin, inter_bin = bins["solution"], bins["interactor"]
    passed = 0
    for i in range(1, args.tests + 1):
        seed = str(args.seed + i) if args.seed is not None else None
        inter_args = [seed] if seed else []

        try:
            # Start interactor
            inter = subprocess.Popen(
                [str(inter_bin)] + inter_args,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                bufsize=1,
            )
            # Start solution, connect to interactor
            sol = subprocess.Popen(
                [str(sol_bin)],
                stdin=inter.stdout,   # sol reads what inter writes
                stdout=inter.stdin,   # sol writes to inter
                stderr=subprocess.PIPE,
                text=True,
                bufsize=1,
            )

            try:
                # Wait with timeout
                sol_ret = sol.wait(timeout=args.timeout)
                inter_ret = inter.wait(timeout=2.0)
            except subprocess.TimeoutExpired:
                sol.kill()
                inter.kill()
                print(color(f"[{i}] TLE / hang in interaction", C.RED))
                save_fail(i, "", "", extra="interactive TLE", work_dir=work_dir)
                return False

            inter_err = inter.stderr.read() if inter.stderr else ""
            sol_err = sol.stderr.read() if sol.stderr else ""

            if inter_ret != 0:
                print(color(f"[{i}] Interactive FAIL (interactor rc={inter_ret})", C.RED))
                if inter_err:
                    print(inter_err)
                if sol_err:
                    print(color("Solution stderr:", C.YELLOW), sol_err)
                save_fail(i, "", "", extra=inter_err + "\n" + sol_err, work_dir=work_dir)
                return False

            if sol_ret != 0:
                print(color(f"[{i}] Solution RE (rc={sol_ret})", C.RED))
                print(sol_err)
                return False

        except Exception as e:
            print(color(f"[{i}] Interaction error: {e}", C.RED))
            return False

        passed += 1
        if i % 20 == 0 or i == args.tests:
            print(color(f"[{i}/{args.tests}] OK", C.GREEN))

    print(color(f"\nAll {passed} interactive tests passed!", C.GREEN + C.BOLD))
    return True


def main():
    parser = argparse.ArgumentParser(
        description="Local cross-platform stress tester for CP (macOS / Linux / Windows)",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python3 stress.py                     # compare mode, 100 tests
  python3 stress.py -m compare -t 2000 --timeout 1.5
  python3 stress.py -m check -t 500
  python3 stress.py -m interactive --tests 30 --seed 42
  CXX=g++-14 python3 stress.py ...
        """,
    )
    parser.add_argument("-m", "--mode", choices=["compare", "check", "interactive"],
                        default="compare", help="Testing mode (default: compare)")
    parser.add_argument("-t", "--tests", type=int, default=100, help="Number of tests")
    parser.add_argument("--timeout", type=float, default=TIMEOUT_DEFAULT, help="Time limit per test (sec)")
    parser.add_argument("--seed", type=int, default=None, help="Base random seed for generator/interactor")
    parser.add_argument("--solution", default=DEFAULT_FILES["solution"])
    parser.add_argument("--brute", default=DEFAULT_FILES["brute"])
    parser.add_argument("--generator", default=DEFAULT_FILES["generator"])
    parser.add_argument("--checker", default=DEFAULT_FILES["checker"])
    parser.add_argument("--interactor", default=DEFAULT_FILES["interactor"])
    parser.add_argument("--validator", default=DEFAULT_FILES["validator"])
    parser.add_argument("--no-compile", action="store_true", help="Skip compilation (use existing binaries)")
    parser.add_argument("--keep-bins", action="store_true", help="Do not delete compiled binaries after run")
    args = parser.parse_args()

    work_dir = Path.cwd()
    compiler = find_compiler()
    print(color(f"Compiler: {compiler}", C.BLUE))
    print(color(f"Mode: {args.mode} | Tests: {args.tests} | Timeout: {args.timeout}s", C.BLUE))

    # Prepare binaries in /tmp (some mounts like artifacts are noexec)
    bin_dir = Path(tempfile.mkdtemp(prefix="stress_bins_"))

    needed = {
        "compare": ["generator", "solution", "brute"],
        "check": ["generator", "solution", "checker"],
        "interactive": ["solution", "interactor"],
    }[args.mode]

    # Optional files
    optional = ["validator"]
    if args.mode == "check":
        optional.append("brute")

    bins = {}
    sources = {
        "solution": Path(args.solution),
        "brute": Path(args.brute),
        "generator": Path(args.generator),
        "checker": Path(args.checker),
        "interactor": Path(args.interactor),
        "validator": Path(args.validator),
    }

    for name in needed + optional:
        src = sources[name]
        if not src.exists():
            if name in needed:
                print(color(f"Required file missing: {src}", C.RED))
                sys.exit(1)
            continue
        out = bin_dir / name
        if not args.no_compile:
            print(f"Compiling {src.name} ...", end=" ", flush=True)
            if compile_cpp(src, out, compiler):
                print(color("OK", C.GREEN))
            else:
                sys.exit(1)
        else:
            if not out.exists():
                print(color(f"Binary not found: {out}", C.RED))
                sys.exit(1)
        bins[name] = out

    start_time = time.time()
    ok = False
    try:
        if args.mode == "compare":
            ok = mode_compare(args, bins, work_dir)
        elif args.mode == "check":
            ok = mode_check(args, bins, work_dir)
        elif args.mode == "interactive":
            ok = mode_interactive(args, bins, work_dir)
    finally:
        if not args.keep_bins and bin_dir.exists():
            shutil.rmtree(bin_dir, ignore_errors=True)

    elapsed = time.time() - start_time
    print(color(f"Total time: {elapsed:.1f}s", C.BLUE))
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
