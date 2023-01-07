#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
extern char* _parse_ip(struct iphdr *ip){
	in_addr_t negr = (in_addr_t)ip->saddr;
	struct in_addr k;
	k.s_addr = negr;
   return (char *)inet_ntoa(k);
}

