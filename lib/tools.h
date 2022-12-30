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
extern char *_read_rules(char filename[]){
   FILE *textfile;
   char *text;
   long numbytes;
   textfile = fopen(filename, "r");
   fseek(textfile, 0L, SEEK_END);
   numbytes = ftell(textfile);
   fseek(textfile, 0L, SEEK_SET);  
   text = (char*)calloc(numbytes, sizeof(char));   
   fread(text, sizeof(char), numbytes, textfile);
   fclose(textfile);
   return text;
}
extern char *_get_type_from_rules(char rules[]){
   
}