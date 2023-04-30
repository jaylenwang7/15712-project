#!/bin/bash

# take the IP address of the target as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <target IP>"
    exit 1
fi

# set the DEVICE variable to the name of your network interface - take first line of grep output
LINES=$(ip route | grep ${1})
# discard lines with "default" in them
LINES=$(echo "$LINES" | grep -v "default")
# take first line of output
DEVICE=$(echo "$LINES" | head -n 1 | awk '{print $3}')
echo $DEVICE

# make scripts
make bpf.o DEVICE=$DEVICE
make qdisc DEVICE=$DEVICE
make run DEVICE=$DEVICE