
all: userspace-drop bpf-drop ebpf-drop

.PHONY: userspace-drop
userspace-drop:
	gcc -Wall -Wextra -O2 userspace-drop.c -o userspace-drop

.PHONY: bpf-drop
bpf-drop:
	gcc -Wall -Wextra -O2 bpf-drop.c -o bpf-drop

.PHONY: ebpf-drop
ebpf-drop:
	gcc -Wall -Wextra -O2 ebpf-drop.c -o ebpf-drop

.PHONY:
clean:
	rm userspace-drop bpf-drop ebpf-drop