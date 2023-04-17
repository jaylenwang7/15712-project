#include <pcap.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <linux/if_ether.h>

void packet_handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    // Get the Ethernet header
    struct ethhdr* ethernetHeader = (struct ethhdr*)packet;

    // Check if the packet is IP
    if (ntohs(ethernetHeader->h_proto) == ETH_P_IP) {
        // Get the IP header
        struct iphdr* ipHeader = (struct iphdr*)(packet + sizeof(struct ethhdr));
        
        // Process the IP packet
        // ...
    } else {
        // Drop the non-IP packet
        printf("Dropping non-IP packet\n");
    }
}

int main() {
    char errorBuffer[PCAP_ERRBUF_SIZE];
    pcap_t* pcapHandle = pcap_create("eth0", errorBuffer);
    if (pcapHandle == NULL) {
        printf("Error creating pcap handle: %s\n", errorBuffer);
        return 1;
    }

    if (pcap_set_promisc(pcapHandle, 1) != 0) {
        printf("Error setting promiscuous mode\n");
        return 1;
    }

    if (pcap_activate(pcapHandle) != 0) {
        printf("Error activating pcap handle\n");
        return 1;
    }

    pcap_loop(pcapHandle, -1, packet_handler, NULL);

    pcap_close(pcapHandle);

    return 0;
}