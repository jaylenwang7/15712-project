#!/bin/bash

# take the IP address of the target as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <target IP>"
    exit 1
fi

# set the DEVICE variable to the name of your network interface
DEVICE=$(ip route | grep ${1} | awk '{print $3}')
echo "DEVICE: $DEVICE"

# set environment variable of the device name
export DEVICE=$DEVICE

# make scripts
make bpf.o DEVICE=$DEVICE
make qdisc DEVICE=$DEVICE
make run DEVICE=$DEVICE