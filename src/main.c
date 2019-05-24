/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Gautier & Lucas ~ myARPspoof => main.c
*/

#include "arpspoof.h"

int main(int ac, char **av)
{
    arguments_t args;

    if (parse_args(ac, av, &args) == FALSE)
        return (EXIT_ERROR);
//    debug_args(&args);
    get_mac_addr(&args);
    return (EXIT_SUCCESS);
}