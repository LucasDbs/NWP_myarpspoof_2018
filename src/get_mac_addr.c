/*
** EPITECH PROJECT, 2019
** get_mac_addr.c
** File description:
** Gautier & Lucas ~ File use to get the mac address of the target ip
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/ethernet.h>
#include "arpspoof.h"
#include "color.h"

int allocate_infos(infos_t *infos)
{
    infos->src_mac = calloc(6, sizeof(uint8_t));
    infos->dst_mac = calloc(6, sizeof(uint8_t));
    infos->ether_frame = calloc(IP_MAXPACKET, sizeof(uint8_t));
    infos->interface = calloc(40, sizeof(char));
    infos->target = calloc(40, sizeof(char));
    infos->src_ip = calloc(INET_ADDRSTRLEN, sizeof(char));
    memset(&(infos->ifr), 0, sizeof(infos->ifr));
    memset(&(infos->device), 0, sizeof(infos->device));
    memset(infos->dst_mac, 0xff, 6 * sizeof(uint8_t));
    memset(&(infos->hints), 0, sizeof(struct addrinfo));

    if (!infos->src_mac || !infos->dst_mac || !infos->ether_frame ||
    !infos->interface || !infos->target || !infos->src_ip) {
        perror("[Error] When allocate infos");
        exit(EXIT_ERROR);
    }
    return (1);
}

int send_arp_request(infos_t *infos)
{
    if ((infos->sd = socket(PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 0) {
        perror("socket() failed ");
        exit(EXIT_ERROR);
    }
    if ((sendto(infos->sd, infos->ether_frame, FRAME_LENGTH, 0,
        (struct sockaddr *)&(infos->device), sizeof(infos->device))) <= 0) {
        perror("sendto() failed");
        exit(EXIT_ERROR);
    }
    return (0);
}

int init_infos(infos_t *infos, arguments_t *args)
{
    get_source_mac_addr(infos, args);
    infos->hints.ai_family = AF_INET;
    infos->hints.ai_socktype = SOCK_STREAM;
    infos->hints.ai_flags = infos->hints.ai_flags | AI_CANONNAME;
    if ((inet_pton(AF_INET, infos->src_ip, &(infos->arphdr.sender_ip))) != 1) {
        perror("inet_pton() failed\n");
        exit(EXIT_ERROR);
    }
    if ((getaddrinfo(infos->target, NULL, &(infos->hints),
        &(infos->res))) != 0) {
        perror("getaddrinfo() failed\n");
        exit(EXIT_ERROR);
    }
    infos->ipv4 = (struct sockaddr_in *)infos->res->ai_addr;
    memcpy(&(infos->arphdr.target_ip), &(infos->ipv4->sin_addr),
    4 * sizeof(uint8_t));
    freeaddrinfo(infos->res);
    infos->device.sll_family = AF_PACKET;
    memcpy(infos->device.sll_addr, infos->src_mac, 6 * sizeof (uint8_t));
    return (1);
}

uint8_t get_mac_addr(infos_t *infos, arguments_t *args)
{
    int i = 0;

    allocate_infos(infos);
    init_infos(infos, args);
    fill_arphdr(infos, ARPOP_REQUEST);
    fill_etherframe(infos);
    if (args->printBroadcast) {
        for (i = 0; i < 41; i++)
            printf ("%02x ", infos->ether_frame[i]);
        printf ("%02x\n", infos->ether_frame[i]);
        return (0);
    } else if (args->printSpoof)
        return (printSpoof(infos, args));
    send_arp_request(infos);
    return (1);
}