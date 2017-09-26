#!/bin/bash
sudo rmmod dropicmp 2>/dev/null
make test
if [ $? != 0 ]; then
            printf "Error when executing command: make"
fi
