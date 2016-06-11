#!/bin/bash

ccache gcc -g -Wall -Werror -Wcast-align -pedantic $1

if [ $? = 0 ]; then
    cppcheck .
fi

if [ $? = 0 ]; then
    valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./a.out
fi

if [ $? = 0 ]; then
    git status
fi
