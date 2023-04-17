#include <linux/bpf.h>
#include <linux/filter.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/in.h>

struct sock_filter bpf_filter[] = {
    BPF_STMT(BPF_LD + BPF_H + BPF_ABS, 12),
    BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, ETH_P_IP, 0, 1),
    BPF_STMT(BPF_RET + BPF_K, SECBPF_DROP),
    BPF_STMT(BPF_RET + BPF_K, SECBPF_ALLOW),
};

struct sock_fprog bpf_program = {
    .len = sizeof(bpf_filter) / sizeof(struct sock_filter),
    .filter = bpf_filter,
};

int main(int argc, char **argv)
{
    // Open a socket to attach the eBPF program to
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    // Attach the eBPF program to the socket
    setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf_program, sizeof(bpf_program));

    // Receive packets and filter them using eBPF
    while (true) {
        char buf[2048];
        ssize_t len = recv(sock, buf, sizeof(buf), 0);
        if (len < 0) {
            perror("recv");
            break;
        }
    }

    return 0;
}