/*
** EPITECH PROJECT, 2019
** receive_arp.c
** File description:
** Gautier & Lucas ~ myARPspoof => receive_arp.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <errno.h>
#include "arpspoof.h"

int print_found(infos_t *infos)
{
    printf("Found victim's MAC address: '");
    for (int i = 0; i < 5; i++)
        printf ("%02x:", infos->arphdr.sender_mac[i]);
    printf ("%02x'\n", infos->arphdr.sender_mac[5]);
    return (0); 
}

int receive_request(infos_t *infos)
{
    if (recv(infos->sd, infos->ether_frame, IP_MAXPACKET, 0) < 0) {
        if (errno == EINTR) {
            memset(infos->ether_frame, 0, IP_MAXPACKET * sizeof (uint8_t));
        } else {
            perror("recv() failed:");
            exit(EXIT_ERROR);
        }
    }
    return (0);
}

int receive_arp_request(infos_t *infos)
{
    arp_hdr *arphdr_tmp = (arp_hdr *)(infos->ether_frame + 6 + 6 + 2);

    while (((((infos->ether_frame[12]) << 8) + infos->ether_frame[13])
        != ETH_P_ARP) || (ntohs(arphdr_tmp->opcode) != ARPOP_REPLY))
        receive_request(infos);
    memcpy(&(infos->arphdr), arphdr_tmp, sizeof(infos->arphdr));
    print_found(infos);
    return (EXIT_SUCCESS);
}