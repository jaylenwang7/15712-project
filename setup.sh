#!/bin/bash

# Install dependencies for traditional program
sudo apt-get update
sudo apt-get install -y g++

# Install dependencies for eBPF program
sudo apt-get install -y llvm clang libclang-dev

# Install dependencies for eBPF program
sudo apt-get install bpfcc-tools linux-headers-$(uname -r)