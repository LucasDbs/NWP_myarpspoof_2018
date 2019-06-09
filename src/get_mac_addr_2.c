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
#include <sys/ioctl.h>
#include <ifaddrs.h>
#include <net/ethernet.h>
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
    memcpy(&(infos->arphdr.sender_mac), infos->src_mac, 6 * sizeof(uint8_t));
    memset(&(infos->arphdr.target_mac), 0, 6 * sizeof(uint8_t));
    return (0);
}

int fill_etherframe(infos_t *infos)
{
    memcpy(infos->ether_frame, infos->dst_mac, 6 * sizeof(uint8_t));
    memcpy(infos->ether_frame + 6, infos->src_mac, 6 * sizeof(uint8_t));
    infos->ether_frame[12] = ETH_P_ARP / 256;
    infos->ether_frame[13] = ETH_P_ARP % 256;
    memcpy(infos->ether_frame + ETH_HDRLEN, &(infos->arphdr),
        ARP_HDRLEN * sizeof(uint8_t));
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
    struct sockaddr_ll *src_interface;

    strcpy(infos->interface, args->iface);
    src_interface = get_my_mac_addr(args);
    if (!src_interface) {
        perror("get_my_mac_addr() failed");
        return (EXIT_ERROR);
    }
    memcpy(infos->src_mac, src_interface->sll_addr, 6 * sizeof(uint8_t));
    if ((infos->device.sll_ifindex = if_nametoindex(infos->interface)) == 0) {
        perror("if_nametoindex() failed");
        exit(EXIT_ERROR);
    }
    strcpy(infos->src_ip, args->source_ip);
    strcpy(infos->target, args->dest_ip);
    return (0);
}

struct sockaddr_ll *get_my_mac_addr(arguments_t *args)
{
    struct ifaddrs *ifaddr=NULL;
    struct ifaddrs *ifa = NULL;
    struct sockaddr_ll *s;

    if (getifaddrs(&ifaddr) == -1) {
            perror("getifaddrs");
            exit(84);
    } else {
        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
            s = (struct sockaddr_ll*)ifa->ifa_addr;
            if ((ifa->ifa_addr) && (ifa->ifa_addr->sa_family == AF_PACKET) &&
                !strcmp(ifa->ifa_name, args->iface)) {
                return (s);
            }
        }
        freeifaddrs(ifaddr);
    }
    return 0;
}