/*
** EPITECH PROJECT, 2019
** parsing.c
** File description:
** Gautier & Lucas ~ myARPspoof => parsing.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "color.h"
#include "arpspoof.h"

int parse_args(int ac, char **av)
{
    if (ac < 4 || ac > 6)
        return (FALSE);
    args.source_ip = av[1];
    args.dest_ip = av[2];
    args.iface = av[3];
    if (ac == 5) {
        if (!strcmp(av[4], "--printBroadcast"))
            args.printBroadcast = TRUE;
        else
            return (FALSE);
    }
    if (ac == 6) {
        if (!strcmp(av[4], "--printSpoof")) {
            args.printSpoof = TRUE;
            args.mac_addr = av[5];
        } else
            return (FALSE);
    }
    return (TRUE);
}

void debug_args(void)
{
    printf(ANSI_COLOR_GREEN);
    printf("========================================\n");
    printf("%sArguments :%s\n", ANSI_COLOR_RED, ANSI_COLOR_GREEN);
    printf("Source_ip: %s%s%s\n", ANSI_COLOR_CYAN, args.source_ip, ANSI_COLOR_GREEN);
    printf("Dest_ip: %s%s%s\n", ANSI_COLOR_CYAN, args.dest_ip, ANSI_COLOR_GREEN);
    printf("Iface: %s%s%s\n", ANSI_COLOR_CYAN, args.iface, ANSI_COLOR_GREEN);
    printf("PrintBroadcast (BOOL): %s%i%s\n", ANSI_COLOR_CYAN, args.printBroadcast, ANSI_COLOR_GREEN);
    printf("PrintSpoof (Bool): %s%i%s\n", ANSI_COLOR_CYAN, args.printSpoof, ANSI_COLOR_GREEN);
    printf("Mac_addr (if PrintSpoof is TRUE): %s%s%s\n", ANSI_COLOR_CYAN, args.mac_addr, ANSI_COLOR_GREEN);
    printf("========================================\n");
    printf(ANSI_COLOR_RESET);
}

void affichebin(unsigned n)
{
	unsigned bit = 0 ;
	unsigned mask = 1 ;
	for (int i = 0 ; i < 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}