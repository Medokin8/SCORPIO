#!/bin/bash

rm tracker.exe

g++ -o tracker.exe -Wall -pedantic tracker.cpp

./tracker.exe &