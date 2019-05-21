/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Gautier & Lucas ~ myARPspoof => main.c
*/

#include "arpspoof.h"

// int create_socket(struct sockaddr_in *addr, int backlog)
// {
// 	int sock = socket(PF_INET, SOCK_STREAM, 0);

// 	if (sock == -1) {
// 		perror("socket failed");
// 		return (-1);
// 	}
// 	if (bind(sock, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
// 		perror("bind failed");
// 		return (-1);
// 	}
// 	if (listen(sock, backlog) < 0) {
// 		perror("listen failed");
// 		return (-1);
// 	}
// 	return (sock);
// }

int get_mac_addr()
{

    return (0);
}

int main(int ac, char **av)
{
    if (parse_args(ac, av) == FALSE)
        return (EXIT_ERROR);
    debug_args();
    get_mac_addr();
    return (EXIT_SUCCESS);
}