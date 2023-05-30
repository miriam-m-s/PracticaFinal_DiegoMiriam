#!/bin/bash

# make binaries

./killServerProcess.sh

make clean
make game

# open server
 ./spaceInvaders_server 0.0.0.0 2200 &
sleep 1.5

# open clients
./Client_SpaceInvaders 0.0.0.0 2200 miri &
./Client_SpaceInvaders 0.0.0.0 2200 diegui&