/*
** EPITECH PROJECT, 2019
** arpspoof.h
** File description:
** Gautier & Lucas ~ Include file
*/

#ifndef _ARPSPOOF_H_
#define _ARPSPOOF_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <bits/ioctls.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <errno.h>

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

typedef struct infos_s 
{
    int sd;
    char *interface;
    char *target;
    char *src_ip;
    arp_hdr arphdr;
    uint8_t *src_mac;
    uint8_t *dst_mac;
    uint8_t *ether_frame;
    struct addrinfo hints;
    struct addrinfo *res;
    struct sockaddr_in *ipv4;
    struct sockaddr_ll device;
    struct ifreq ifr;
} infos_t;

int parse_args(int, char **, arguments_t *);
void debug_args(arguments_t *);
uint8_t get_mac_addr(infos_t *, arguments_t *);
int get_source_mac_addr(infos_t *, arguments_t *);
int fill_etherframe(infos_t *);
int free_infos(infos_t *);
int fill_arphdr(infos_t *, int);
int spoof_arp(infos_t *);
int send_arp_request(infos_t *);
int create_socket(struct sockaddr_in *, int);
struct sockaddr_in create_address(int);
int receive_arp_request(infos_t *);

#endif