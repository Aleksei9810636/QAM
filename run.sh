#!/bin/bash

mkdir -p results
g++ main.cpp -o main.o
./main.o
python3 ber.py
python3 drow_distr.py

echo "Done! Check results/"