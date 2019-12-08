#!/bin/bash
rm pgen;
rm tgen;
rm hashmap;
g++ Probabilitygen.cpp -opgen -Wall -std=c++11;
g++ textgen.cpp -otgen -Wall -std=c++11;
g++ HashMap.cpp HashMap.h -ohashmap -Wall -std=c++11;
