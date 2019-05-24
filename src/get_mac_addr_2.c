/*
** EPITECH PROJECT, 2019
** get_mac_addr.c
** File description:
** Gautier & Lucas ~ File use to get the mac address of the target ip
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


int fill_arphdr(infos_t *infos, int arp_type)
{
    infos->device.sll_halen = 6;
    infos->arphdr.htype = htons(1);
    infos->arphdr.ptype = htons(ETH_P_IP);
    infos->arphdr.hlen = 6;
    infos->arphdr.plen = 4;
    infos->arphdr.opcode = htons(arp_type);
    memcpy(&(infos->arphdr.sender_mac), infos->src_mac, 6 * sizeof (uint8_t));
    memset(&(infos->arphdr.target_mac), 0, 6 * sizeof (uint8_t));
    return (0);
}

int fill_etherframe(infos_t *infos)
{
    memcpy(infos->ether_frame, infos->dst_mac, 6 * sizeof (uint8_t));
    memcpy(infos->ether_frame + 6, infos->src_mac, 6 * sizeof (uint8_t));
    infos->ether_frame[12] = ETH_P_ARP / 256;
    infos->ether_frame[13] = ETH_P_ARP % 256;
    memcpy (infos->ether_frame + ETH_HDRLEN, &(infos->arphdr), ARP_HDRLEN * sizeof (uint8_t));
    return (0);
}

int free_infos(infos_t *infos)
{
    free(infos->src_mac);
    free(infos->dst_mac);
    free(infos->ether_frame);
    free(infos->interface);
    free(infos->target);
    free(infos->src_ip);
    return (0);
}

int get_source_mac_addr(infos_t *infos, arguments_t *args)
{
    strcpy(infos->interface, args->iface);
    if ((infos->sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
        perror ("[Error] socket() failed");
        exit (EXIT_ERROR);
    }
    snprintf(infos->ifr.ifr_name, sizeof (infos->ifr.ifr_name), "%s", infos->interface);
    if (ioctl (infos->sd, SIOCGIFHWADDR, &(infos->ifr)) < 0) {
        perror ("ioctl() failed");
        return (EXIT_ERROR);
    }
    close (infos->sd);
    memcpy(infos->src_mac, infos->ifr.ifr_hwaddr.sa_data, 6 * sizeof (uint8_t));
    if ((infos->device.sll_ifindex = if_nametoindex (infos->interface)) == 0) {
        perror("if_nametoindex() failed");
        exit(EXIT_ERROR);
    }
    return (0);
}