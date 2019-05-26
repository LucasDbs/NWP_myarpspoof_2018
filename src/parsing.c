/*
** EPITECH PROJECT, 2019
** parsing.c
** File description:
** Gautier & Lucas ~ myARPspoof => parsing.c
*/

#include <stdio.h>
#include <string.h>
#include "color.h"
#include "arpspoof.h"

int parse_args(int ac, char **av, arguments_t *args)
{
    if (ac < 4 || ac > 6)
        return (FALSE);
    args->source_ip = av[1];
    args->dest_ip = av[2];
    args->iface = av[3];
    if (ac == 5) {
        if (!strcmp(av[4], "--printBroadcast"))
            args->printBroadcast = TRUE;
        else
            return (FALSE);
    }
    if (ac == 6) {
        if (!strcmp(av[4], "--printSpoof")) {
            args->printSpoof = TRUE;
            args->mac_addr = av[5];
        } else
            return (FALSE);
    }
    return (TRUE);
}

void affichebin(unsigned n)
{
	unsigned bit = 0;
	unsigned mask = 1;

	for (int i = 0 ; i < 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}