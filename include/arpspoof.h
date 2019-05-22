/*
** EPITECH PROJECT, 2019
** arpspoof.h
** File description:
** Gautier & Lucas ~ Include file
*/

#ifndef _ARPSPOOF_H_
#define _ARPSPOOF_H_

#include <stdlib.h>
#include <arpa/inet.h>

#define EXIT_ERROR 84
#define EXIT_SUCCESS 0
#define TRUE 1
#define FALSE 0

typedef struct arguments_s
{
    char *source_ip;
    char *dest_ip;
    char *iface;
    int printBroadcast;
    int printSpoof;
    char *mac_addr;
} arguments_t;

static arguments_t args = {NULL, NULL, NULL, FALSE, FALSE, NULL};

int parse_args(int, char **);
void debug_args(void);
int create_socket(struct sockaddr_in *, int);
struct sockaddr_in create_address(int);

#endif