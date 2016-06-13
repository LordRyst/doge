#!/bin/bash

ccache g++ -Og -march=native -Wall -Werror -o server.out messages.cpp mongoose.c websocket_chat.c players.cpp amap.cpp game.cpp

if [ $? = 0 ]; then
    cppcheck .
    if [ $? = 0 ]; then
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./server.out
	if [ $? = 0 ]; then
	    git status
	fi
    fi
fi
