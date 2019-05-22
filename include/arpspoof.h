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

#define ETH_HDRLEN 14
#define IP4_HDRLEN 20
#define ARP_HDRLEN 28
#define ARPOP_REQUEST 1
#define ARPOP_REPLY 2
#define FRAME_LENGTH (6 + 6 + 2 + ARP_HDRLEN)

typedef struct arguments_s
{
    char *source_ip;
    char *dest_ip;
    char *iface;
    int printBroadcast;
    int printSpoof;
    char *mac_addr;
} arguments_t;

typedef struct _arp_hdr {
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t opcode;
    uint8_t sender_mac[6];
    uint8_t sender_ip[4];
    uint8_t target_mac[6];
    uint8_t target_ip[4];
} arp_hdr;

static arguments_t args = {NULL, NULL, NULL, FALSE, FALSE, NULL};

int parse_args(int, char **);
void debug_args(void);
uint8_t get_mac_addr(void);
int create_socket(struct sockaddr_in *, int);
struct sockaddr_in create_address(int);

#endif