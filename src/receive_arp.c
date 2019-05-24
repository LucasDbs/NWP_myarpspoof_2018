/*
** EPITECH PROJECT, 2019
** receive_arp.c
** File description:
** Gautier & Lucas ~ myARPspoof => receive_arp.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <errno.h>
#include "arpspoof.h"

uint8_t *allocate_ustrmem (int);
  
int receive_arp_request(infos_t *infos)
{
//   int i, sd, status;
//   uint8_t *ether_frame;
//   arp_hdr *arphdr;
  
  // Allocate memory for various arrays.
//   ether_frame = allocate_ustrmem (IP_MAXPACKET);
  
  // Submit request for a raw socket descriptor.
//   if ((sd = socket (PF_PACKET, SOCK_RAW, htons (ETH_P_ALL))) < 0) {
//     perror ("socket() failed ");
//     exit (EXIT_FAILURE);
//   }
  
  // Listen for incoming ethernet frame from socket sd.
  // We expect an ARP ethernet frame of the form:
  //     MAC (6 bytes) + MAC (6 bytes) + ethernet type (2 bytes)
  //     + ethernet data (ARP header) (28 bytes)
  // Keep at it until we get an ARP reply.
//   arphdr = (arp_hdr *) (ether_frame + 6 + 6 + 2);
  while (((((infos->ether_frame[12]) << 8) + infos->ether_frame[13]) != ETH_P_ARP) || (ntohs(infos->arphdr.opcode) != ARPOP_REPLY)) {
    if (recv(infos->sd, infos->ether_frame, IP_MAXPACKET, 0) < 0) {
      if (errno == EINTR) {
        memset(infos->ether_frame, 0, IP_MAXPACKET * sizeof (uint8_t));
        continue;  // Something weird happened, but let's try again.
      } else {
        perror("recv() failed:");
        exit(EXIT_ERROR);
      }
    }
  }
//   close (infos->sd);
  
  // Print out contents of received ethernet frame.
  printf ("\nEthernet frame header:\n");
  printf ("Destination MAC (this node): ");
  for (int i = 0; i < 5; i++) {
    printf ("%02x:", infos->ether_frame[i]);
  }
  printf ("%02x\n", infos->ether_frame[5]);
  printf ("Source MAC: ");
  for (int i = 0; i < 5; i++) {
    printf ("%02x:", infos->ether_frame[i+6]);
  }
  printf ("%02x\n", infos->ether_frame[11]);
  // Next is ethernet type code (ETH_P_ARP for ARP).
  // http://www.iana.org/assignments/ethernet-numbers
  printf ("Ethernet type code (2054 = ARP): %u\n", ((infos->ether_frame[12]) << 8) + infos->ether_frame[13]);
  printf ("\nEthernet data (ARP header):\n");
  printf ("Hardware type (1 = ethernet (10 Mb)): %u\n", ntohs(infos->arphdr.htype));
  printf ("Protocol type (2048 for IPv4 addresses): %u\n", ntohs(infos->arphdr.ptype));
  printf ("Hardware (MAC) address length (bytes): %u\n", infos->arphdr.hlen);
  printf ("Protocol (IPv4) address length (bytes): %u\n", infos->arphdr.plen);
  printf ("Opcode (2 = ARP reply): %u\n", ntohs(infos->arphdr.opcode));
  printf ("Sender hardware (MAC) address: ");
  for (int i = 0; i < 5; i++) {
    printf ("%02x:", infos->arphdr.sender_mac[i]);
  }
  printf ("%02x\n", infos->arphdr.sender_mac[5]);
  printf ("Sender protocol (IPv4) address: %u.%u.%u.%u\n",
    infos->arphdr.sender_ip[0], infos->arphdr.sender_ip[1], infos->arphdr.sender_ip[2], infos->arphdr.sender_ip[3]);
  printf ("Target (this node) hardware (MAC) address: ");
  for (int i = 0; i < 5; i++) {
    printf ("%02x:", infos->arphdr.target_mac[i]);
  }
  printf ("%02x\n", infos->arphdr.target_mac[5]);
  printf ("Target (this node) protocol (IPv4) address: %u.%u.%u.%u\n",
    infos->arphdr.target_ip[0], infos->arphdr.target_ip[1], infos->arphdr.target_ip[2], infos->arphdr.target_ip[3]);
//   free(infos->ether_frame);
  return (EXIT_SUCCESS);
}
  
// Allocate memory for an array of unsigned chars.
// uint8_t *
// allocate_ustrmem (int len)
// {
//   void *tmp;
  
//   if (len <= 0) {
//     fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_ustrmem().\n", len);
//     exit (EXIT_FAILURE);
//   }
  
//   tmp = (uint8_t *) malloc (len * sizeof (uint8_t));
//   if (tmp != NULL) {
//     memset (tmp, 0, len * sizeof (uint8_t));
//     return (tmp);
//   } else {
//     fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_ustrmem().\n");
//     exit (EXIT_FAILURE);
//   }
// }