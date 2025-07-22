# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

all: main

main: main.o
	$(CXX) $(CXXFLAGS) main.o -o main

main.o: main.cpp vec3.h ray.h color.h hittable.h hittable_list.h sphere.h constants.h interval.h camera.h material.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -f main.o main