/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Gautier & Lucas ~ myARPspoof => main.c
*/

#include "arpspoof.h"

int main(int ac, char **av)
{
    if (parse_args(ac, av) == FALSE)
        return (EXIT_ERROR);
    debug_args();
    get_mac_addr();
    return (EXIT_SUCCESS);
}