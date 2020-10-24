#!/bin/zsh

c++ -O2 -Wall -std=c++17 EulerSieve.cpp EulerSieveInvoker.cpp -o EulerSieve.exe
c++ -O2 -Wall -std=c++17 EulerSieve.cpp SegmentedSieve.cpp SegmentedSieveInvoker.cpp -o SegmentedSieve.exe
