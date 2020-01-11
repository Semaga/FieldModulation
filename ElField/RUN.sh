#!/bin/bash

g++ FUNC.cpp CHR_PRP.cpp SUB_PRP.cpp main.cpp -c -std=c++14
g++ FUNC.o CHR_PRP.o SUB_PRP.o main.o -o DoIt

if [[ $1 == run ]] 
then
./DoIt
fi

if [[ $2 == plot ]]
then
python Untitled.py
fi
