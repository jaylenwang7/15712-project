// bpf-drop
//
// Copyright (c) 2018 CloudFlare, Inc.

#include <arpa/inet.h>
#include <errno.h>
#include <linux/filter.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "net.h"

static int net_setup_bpf(int sd)
{
	struct sock_filter code[] = {
		// ret #0
		{0x06, 0, 0, 0x00000000},
	};

	struct sock_fprog bpf = {
		.len = ARRAY_SIZE(code),
		.filter = code,
	};

	int r = setsockopt(sd, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf));
	if (r < 0) {
		PFATAL("setsockopt(SO_ATTACH_FILTER)");
	}

	return sd;
}

#define MTU_SIZE 2048

static uint64_t packets = 0;
static uint64_t bytes = 0;

static void timer_handler()
{
	printf("packets=%lu bytes=%lu\n", packets, bytes);
	packets = 0;
	bytes = 0;
}

int main()
{
	struct sigaction sa = {0};
	sa.sa_handler = &timer_handler;
	sigaction(SIGALRM, &sa, NULL);

	struct itimerval timer = {0};
	timer.it_value.tv_sec = 1;
	timer.it_interval.tv_sec = 1;
	setitimer(ITIMER_REAL, &timer, NULL);

	struct sockaddr_storage listen_addr;
	net_gethostbyname(&listen_addr, "::", 1234);
	int fd = net_bind_udp(&listen_addr);

	net_setup_bpf(fd);

	char buf[MTU_SIZE];

	while (1) {
		int r = read(fd, buf, MTU_SIZE);
		if (r == 0) {
			int err = 0;
			socklen_t err_len = sizeof(err);
			getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &err_len);
			if (err == 0) {
				packets += 1;
				continue;
			}
			return 0;
		}

		if (r < 0) {
			if (errno == EINTR) {
				continue;
			}
			PFATAL("recv()");
		} else {
			packets += 1;
			bytes += r;
		}
	}
	close(fd);

	return 0;
}