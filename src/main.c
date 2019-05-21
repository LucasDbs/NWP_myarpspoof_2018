/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Gautier & Lucas ~ myARPspoof => main.c
*/

#include "arpspoof.h"

int get_mac_addr()
{
    struct sockaddr_in addr = create_address(42);
	int master_sock = create_socket(&addr, 1);

    // int master_sock = create_socket();
    return (master_sock);
}

int main(int ac, char **av)
{
    if (parse_args(ac, av) == FALSE)
        return (EXIT_ERROR);
    debug_args();
    get_mac_addr();
    return (EXIT_SUCCESS);
}