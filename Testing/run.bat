@echo off
if not exist generator.exe (
    echo file generator.exe not found compile generator.cpp
) else if not exist solution.exe (
	echo file solution.exe not found compile solution.cpp
) else if not exist brute.exe (
	echo file brute.exe not found compile brute.cpp
) else if not exist check.exe (
	echo file check.exe not found compile check.cpp
) else (
	for /l %%x in (1, 1, 100) do (
		echo %%x
		generator.exe > output.txt
		solution.exe  < output.txt > solution_output.txt
		brute.exe     < output.txt > brute_output.txt
		check.exe     
	)
)
pause