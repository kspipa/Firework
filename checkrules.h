#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

extern char* parse_ip(struct iphdr *ip){
	in_addr_t negr = (in_addr_t)ip->saddr;
	struct in_addr k;
	k.s_addr = negr;
   return (char *)inet_ntoa(k);
}
extern char read_rules(char filename[]){
   FILE *textfile;
   char *text;
   long numbytes;
   textfile = fopen("rules.firerules", "r");
   if(textfile == NULL)
      return 1;
   fseek(textfile, 0L, SEEK_END);
   numbytes = ftell(textfile);
   fseek(textfile, 0L, SEEK_SET);  
   text = (char*)calloc(numbytes, sizeof(char));   
   if(text == NULL)
      return 1;
   fread(text, sizeof(char), numbytes, textfile);
   fclose(textfile);
   return text;
}
extern get_type_from_rules(char rules){
}
extern int check_rules(char rules){

}