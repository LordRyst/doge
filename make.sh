#!/bin/bash

ccache g++ -Og -march=native -Wall -Werror -Wshadow -o server.out messages.cpp mongoose.c websocket_chat.c players.cpp amap.cpp game.cpp

if [ $? = 0 ]; then
    cppcheck .
fi

if [ $? = 0 ]; then
    valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./server.out
fi

if [ $? = 0 ]; then
    git status
fi
