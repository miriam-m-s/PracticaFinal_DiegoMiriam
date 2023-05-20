#!/bin/bash

# make binaries
make clean
make game

# open server
./SpaceInvaders_server.out 0.0.0.0 2200 &
sleep 1.5

# open clients
./client_SpaceInvaders.out 127.0.0.1 2200 miri &
./client_SpaceInvaders.out 127.0.0.1 2200 miram&