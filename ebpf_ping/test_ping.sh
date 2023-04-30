#!/bin/bash

# take two arguments:
# 1. IP address of the target
# 2. seconds to run the test

if [ $# -ne 2 ]; then
    echo "Usage: $0 <target IP> <seconds to run test>"
    exit 1
fi

# run the test
sudo timeout --signal=SIGINT ${2}s ping -s 1000 -f ${1}
