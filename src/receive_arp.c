/*
** EPITECH PROJECT, 2019
** receive_arp.c
** File description:
** Gautier & Lucas ~ myARPspoof => receive_arp.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <errno.h>
#include "arpspoof.h"

uint8_t *allocate_ustrmem (int);

int print_hdr(infos_t *infos)
{
    printf ("\nEthernet frame header:\n");
    printf ("Destination MAC (this node): ");
    for (int i = 0; i < 5; i++)
        printf ("%02x:", infos->ether_frame[i]);
    printf ("%02x\n", infos->ether_frame[5]);
    printf ("Source MAC: ");
    for (int i = 0; i < 5; i++)
        printf ("%02x:", infos->ether_frame[i+6]);
    printf ("%02x\n", infos->ether_frame[11]);
    printf ("Ethernet type code (2054 = ARP): %u\n", ((infos->ether_frame[12]) << 8) + infos->ether_frame[13]);
    printf ("\nEthernet data (ARP header):\n");
    printf ("Hardware type (1 = ethernet (10 Mb)): %u\n", ntohs(infos->arphdr.htype));
    printf ("Protocol type (2048 for IPv4 addresses): %u\n", ntohs(infos->arphdr.ptype));
    printf ("Hardware (MAC) address length (bytes): %u\n", infos->arphdr.hlen);
    printf ("Protocol (IPv4) address length (bytes): %u\n", infos->arphdr.plen);
    printf ("Opcode (2 = ARP reply): %u\n", ntohs(infos->arphdr.opcode));
    printf ("Sender hardware (MAC) address: ");
    for (int i = 0; i < 5; i++)
        printf ("%02x:", infos->arphdr.sender_mac[i]);
    printf ("%02x\n", infos->arphdr.sender_mac[5]);
    printf ("Sender protocol (IPv4) address: %u.%u.%u.%u\n",
        infos->arphdr.sender_ip[0], infos->arphdr.sender_ip[1], infos->arphdr.sender_ip[2], infos->arphdr.sender_ip[3]);
    printf ("Target (this node) hardware (MAC) address: ");
    for (int i = 0; i < 5; i++)
        printf ("%02x:", infos->arphdr.target_mac[i]);
    printf ("%02x\n", infos->arphdr.target_mac[5]);
    printf ("Target (this node) protocol (IPv4) address: %u.%u.%u.%u\n",
        infos->arphdr.target_ip[0], infos->arphdr.target_ip[1], infos->arphdr.target_ip[2], infos->arphdr.target_ip[3]);
    return (0);
}

int receive_arp_request(infos_t *infos)
{
    arp_hdr *arphdr_tmp = (arp_hdr *)(infos->ether_frame + 6 + 6 + 2);

    while (((((infos->ether_frame[12]) << 8) + infos->ether_frame[13]) != ETH_P_ARP) || (ntohs(arphdr_tmp->opcode) != ARPOP_REPLY)) {
        if (recv(infos->sd, infos->ether_frame, IP_MAXPACKET, 0) < 0) {
            if (errno == EINTR) {
                memset(infos->ether_frame, 0, IP_MAXPACKET * sizeof (uint8_t));
                continue;  // Something weird happened, but let's try again.
            } else {
                perror("recv() failed:");
                exit(EXIT_ERROR);
            }
        }
    }
    memcpy(&(infos->arphdr), arphdr_tmp, sizeof(arphdr_tmp));
    print_hdr(infos);
    return (EXIT_SUCCESS);
}