import os
import subprocess
import time
from bcc import BPF
import socket

# define eBPF program
prog = """
#include <uapi/linux/ptrace.h>
#include <linux/netdevice.h>
#include <bcc/proto.h>

int kprobe__ping_recvmsg(struct pt_regs *ctx, struct msghdr *msg,
				struct sk_buff *skb)
{
    struct nlmsghdr *nlh = nlmsg_hdr(skb);
    struct icmphdr *icmph;

    if (nlh->nlmsg_type != NLMSG_DONE)
        return 0;

    icmph = (struct icmphdr *) skb_network_header(skb);
    if (icmph->type == ICMP_ECHO) {
        bpf_trace_printk("Ping reply received\\n");
    }
    return 0;
}
"""

# normal ping
start_time = time.time()
subprocess.run(["ping", "-c", "10", "google.com"], stdout=subprocess.PIPE)
end_time = time.time()
normal_ping_time = end_time - start_time

# eBPF ping
b = BPF(text=prog)
b.attach_kprobe(event="ping_recvmsg", fn_name="kprobe__ping_recvmsg")
s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
s.setsockopt(socket.SOL_IP, socket.IP_TTL, 1)
start_time = time.time()
for i in range(10):
    s.sendto(b"ping", ("google.com", 0))
    b.trace_print()
end_time = time.time()
ebpf_ping_time = end_time - start_time

# print results
print(f"Normal ping time: {normal_ping_time:.6f}s")
print(f"eBPF ping time: {ebpf_ping_time:.6f}s")