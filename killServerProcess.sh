#!/bin/bash

process_name="spaceInvaders_s"

process_id=$(pgrep "$process_name")

if [ -z "$process_id" ]; then
    echo "No server process to kill"
    exit 1
fi

kill "$process_id"

echo "Server process KILLED"
