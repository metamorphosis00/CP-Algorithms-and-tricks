#!/bin/sh

if [ ! -f ./generator ]; then
g++ generator.cpp -o generator
fi
if [ ! -f ./solution ]; then
g++ solution.cpp -o solution
fi
if [ ! -f ./brute ]; then
g++ brute.cpp -o brute
fi
if [ ! -f ./check ]; then
g++ check.cpp -o check
fi
i=1
while [ "$i" -le 100 ];
do
    echo $i
    ./generator $i > output.txt
    ./solution  < output.txt > solution_output.txt
	./brute     < output.txt > brute_output.txt    
    ./check output.txt solution_output.txt brute_output.txt
    i=$(( i+1 ))
done
