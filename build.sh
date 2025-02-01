#!/bin/bash
g++ -c palla.cpp main.cpp 
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app
