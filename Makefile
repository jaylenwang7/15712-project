
all: recv-loop ebpf-drop

.PHONY: recv-loop
recv-loop:
	gcc -Wall -Wextra -O2 recv-loop.c -o recv-loop

.PHONY: ebpf-drop
ebpf-drop:
	gcc -Wall -Wextra -O2 ebpf-drop.c -o ebpf-drop

.PHONY:
clean:
	rm recv-loop ebpf-drop