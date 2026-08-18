# Локальный кроссплатформенный стресс-тестер для олимпиадного программирования

Работает на **macOS**, Linux и Windows.  
Требования: Python 3 + любой C++ компилятор (`g++` / `clang++`).

## Быстрый старт (macOS)

```bash
# 1. Установи компилятор (если ещё нет)
xcode-select --install
# или
brew install gcc

# 2. Скопируй нужные файлы в папку задачи
cp templates/generator.cpp .
cp templates/solution.cpp .
cp templates/brute.cpp .
# при необходимости:
# cp templates/checker.cpp .
# cp templates/interactor.cpp .
# cp templates/validator.cpp .

# 3. Напиши код в solution.cpp, brute.cpp и generator.cpp

# 4. Запусти
python3 stress.py                  # режим compare, 100 тестов
python3 stress.py -t 2000          # 2000 тестов
python3 stress.py --timeout 1.5    # лимит 1.5 сек
```

## Режимы работы

### 1. `compare` (по умолчанию) — сравнение с брутом
```
generator → input
solution  < input → sol.out
brute     < input → brute.out
сравниваем sol.out и brute.out (игнорируя пробелы в конце строк)
```

```bash
python3 stress.py -m compare -t 1000 --timeout 2
```

### 2. `check` — кастомный чекер (несколько правильных ответов)
Используется, когда ответ не единственный (или нужно проверять свойства).

```
generator → input
solution  < input → sol.out
[опционально brute]
checker input.txt sol.out [brute.out]
  → exit 0 = OK, иначе WA
```

```bash
python3 stress.py -m check -t 500
```

Шаблон `checker.cpp` уже есть — просто реализуй свою логику проверки.

### 3. `interactive` — интерактивные задачи
```
solution ↔ interactor (через stdin/stdout)
interactor в конце выходит с кодом 0 (OK) или ≠0 (WA)
```

```bash
python3 stress.py -m interactive -t 50 --seed 42
```

**Важно:** и solution, и interactor должны делать `flush` после каждого вывода (`endl` или `cout.flush()`).

## Полезные флаги

| Флаг | Описание |
|------|----------|
| `-m, --mode` | `compare` / `check` / `interactive` |
| `-t, --tests` | количество тестов (по умолчанию 100) |
| `--timeout` | лимит времени на один тест (сек) |
| `--seed` | базовый seed для генератора (для воспроизводимости) |
| `--solution` | имя файла решения (default: solution.cpp) |
| `--brute` | имя брута |
| `--generator` | имя генератора |
| `--checker` | имя чекера |
| `--interactor` | имя интерактора |
| `--validator` | опциональный валидатор входа |
| `--no-compile` | не компилировать заново |
| `--keep-bins` | не удалять бинарники после запуска |

## Архитектура файлов

```
твоя_задача/
├── solution.cpp      # твоё решение (то, что тестируем)
├── brute.cpp         # правильное (медленное) решение
├── generator.cpp     # генератор случайных тестов
├── checker.cpp       # (опционально) кастомный чекер
├── interactor.cpp    # (опционально) для интерактивных задач
├── validator.cpp     # (опционально) проверка корректности сгенерированного теста
├── stress.py         # сам тестер
└── fails/            # сюда сохраняются упавшие тесты
    ├── fail_42.in
    ├── fail_42.sol
    └── fail_42.brute
```

## Рекомендации по генератору

- Держи ограничения **маленькими**, чтобы брут успевал (n ≤ 10…20, m ≤ 100 и т.д.).
- Используй seed из `argv[1]` — тогда можно воспроизвести упавший тест.
- Хорошая идея: генерировать несколько разных типов тестов (случайные, крайние случаи, почти отсортированные и т.д.).

Пример более продвинутого генератора (массив + несколько тестов):

```cpp
int t = rnd(1, 5);
cout << t << "\n";
while (t--) {
    int n = rnd(1, 8);
    cout << n << "\n";
    for (int i = 0; i < n; i++)
        cout << rnd(-100, 100) << " \n"[i + 1 == n];
}
```

## Что делать при WA

1. Смотри папку `fails/` — там лежит вход, вывод решения и брута.
2. Можно руками прогнать:
   ```bash
   ./solution < fails/fail_42.in
   ./brute < fails/fail_42.in
   ```
3. Минимизируй тест вручную или добавь в генератор режим «генерировать только маленькие тесты».

## Альтернативы (готовые инструменты)

Если не хочется поддерживать свой скрипт:

- **quicktest** (Rust, очень удобный, режимы cmp/check/stress)  
  ```bash
  curl -fsSL https://luchobazz.github.io/quicktest/install/install.sh | sh
  qt cmp -t solution.cpp -c brute.cpp -g generator.cpp --tc 1000
  ```
  (на macOS работает, но официально помечен как «unverified»)

- **stressed** (тоже Rust, очень быстрый)

Этот `stress.py` специально сделан простым, понятным и полностью под твоим контролем.

---

Удачи на контестах! Если нужно что-то доработать (более умный интерактор, поддержка Python-решений, параллельный запуск и т.д.) — просто скажи.
