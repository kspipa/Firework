#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* _parse_ip(struct iphdr *ip){		//Get ip from iphdr
	in_addr_t negr = (in_addr_t)ip->saddr;
	struct in_addr k;
	k.s_addr = negr;
   	return (char *)inet_ntoa(k);
}
struct send{
	char *data; 		//packet
	int verdict;		//ACCEPT or DROP
	int command;		//For api with distribution center
};

