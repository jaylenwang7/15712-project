#!/bin/bash

# Compile the traditional program
gcc -o traditional_program traditional_program.c -lpcap

# Build the eBPF program
clang -O2 -target bpf -c filter_program.c -o filter_program.o

# Start the eBPF program as a packet filter on eth0
sudo tc qdisc add dev eth0 ingress
sudo tc filter add dev eth0 ingress bpf da obj filter_program.o sec classifier

# Run the eBPF program benchmark
echo "Running eBPF program benchmark..."
for i in {1..10}; do
    echo "Iteration $i"
    # Measure the time taken by the eBPF program
    ebpf_start=$(date +%s.%N)
    wget -q -O /dev/null http://example.com
    ebpf_end=$(date +%s.%N)
    ebpf_time=$(echo "$ebpf_end - $ebpf_start" | bc)

    # Print the results
    echo "eBPF program took $ebpf_time seconds"
done

# Remove the eBPF program as a packet filter
sudo tc qdisc del dev eth0 ingress

############################################

# Start the traditional program as a packet filter on eth0
sudo ./traditional_program &

# Run the traditional program benchmark
echo "Running traditional program benchmark..."
for i in {1..10}; do
    echo "Iteration $i"
    # Measure the time taken by the traditional program
    traditional_start=$(date +%s.%N)
    wget -q -O /dev/null http://example.com
    traditional_end=$(date +%s.%N)
    traditional_time=$(echo "$traditional_end - $traditional_start" | bc)

    # Print the results
    echo "Traditional program took $traditional_time seconds"
done

# Kill the traditional program
sudo pkill traditional_program