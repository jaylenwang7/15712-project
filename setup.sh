#!/bin/bash

# Install dependencies for traditional program
sudo apt-get update
sudo apt-get install -y g++

# Install dependencies for eBPF program
sudo apt-get install -y llvm clang libclang-dev

# Install dependencies for eBPF program
sudo apt-get install -y bpfcc-tools linux-headers-$(uname -r) libbpfcc-dev gcc-multilib

sudo apt-get install -y linux-tools-common linux-tools-generic linux-tools-$(uname -r)