/*
** EPITECH PROJECT, 2019
** socket.c
** File description:
** Gautier & Lucas ~ myARPspoof => socket.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int create_socket(struct sockaddr_in *addr, int backlog)
{
	int sock = socket(AF_PACKET, SOCK_RAW, 0);

	if (sock == -1) {
		perror("socket failed");
		return (-1);
	}
	if (bind(sock, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
		perror("bind failed");
		return (-1);
	}
	if (listen(sock, backlog) < 0) {
		perror("listen failed");
		return (-1);
	}
	return (sock);
}

struct sockaddr_in create_address(int port)
{
	struct sockaddr_in addr = { 0 };

	addr.sin_family = AF_PACKET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	return (addr);
}