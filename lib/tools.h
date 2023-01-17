#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"

extern char* _parse_ip(struct iphdr *ip){		//Get ip from iphdr
	in_addr_t negr = (in_addr_t)ip->saddr;
	struct in_addr k;
	k.s_addr = negr;
   	return (char *)inet_ntoa(k);
}
extern int _get_len_of_list(struct module_struct mas[]){
	return sizeof(mas) / sizeof(struct module_struct);
}


