/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Gautier & Lucas ~ myARPspoof => main.c
*/

#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "arpspoof.h"

int printMacAddr(arguments_t *args) {
    int i = 0;

    if (strlen(args->mac_addr) != 17) {
        fprintf(stderr, "Invalid parameter addr_mac");
        exit(EXIT_ERROR);
    }
    while (args->mac_addr[i] != '\0') {
        if (args->mac_addr[i] == ':') {
            args->mac_addr[i] = ' ';
        }
        i++;
    }
    printf("%s ", args->mac_addr);
    return (0);
}

int printSpoof(infos_t *infos, arguments_t *args)
{
    int i = 0;

    if (args->printSpoof) {
        fill_arphdr(infos, ARPOP_REPLY);
        fill_etherframe(infos);
        memset(infos->arphdr.sender_ip, 42, 4 * sizeof(uint8_t));
        if (inet_pton(AF_INET, "192.168.1.1", infos->arphdr.target_ip) != 1) {
            fprintf(stderr, "inet_ption failed");
            exit(84);
        }
        memcpy(infos->ether_frame + ETH_HDRLEN, &(infos->arphdr),
            ARP_HDRLEN * sizeof (uint8_t));
    }
    printMacAddr(args);
    for (i = 6; i < 32; i++) {
        printf ("%02x ", infos->ether_frame[i]);
    }
    printMacAddr(args);
    for (i = 38; i < 41; i++) {
        printf ("%02x ", infos->ether_frame[i]);
    }
    printf ("%02x\n", infos->ether_frame[i]);
    return (0);
}

int main(int ac, char **av)
{
    infos_t infos;
    arguments_t args;

    if (parse_args(ac, av, &args) == FALSE)
        return (EXIT_ERROR);
    if (!get_mac_addr(&infos, &args))
        return (0);
    receive_arp_request(&infos);
    spoof_arp(&infos);
    free_infos(&infos);
    return (EXIT_SUCCESS);
}