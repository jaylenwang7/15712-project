
all: recvmmsg-loop bpf-drop ebpf-drop

.PHONY: recvmmsg-loop
recvmmsg-loop:
	gcc -Wall -Wextra -O2 recvmmsg-loop.c -o recvmmsg-loop

.PHONY: bpf-drop
bpf-drop:
	gcc -Wall -Wextra -O2 bpf-drop.c -o bpf-drop

.PHONY: ebpf-drop
ebpf-drop:
	gcc -Wall -Wextra -O2 ebpf-drop.c -o ebpf-drop

.PHONY:
clean:
	rm recvmmsg-loop bpf-drop ebpf-drop