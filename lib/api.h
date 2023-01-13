#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include "../lib/api.h"

#define PORT    5005

static struct sockaddr_in serv_addr;
struct send_from_module{
	char *data; 		//Packet
	int verdict;		//ACCEPT or DROP
	int command;		//For api with distribution center
    char *name;         //Name of your module
};
extern int get_ansver_code(int sock){

}
extern int init_module(char* name, int sock){
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Cant create socket\n");
    else
        printf("Socket has been created\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        printf("Cant connect to server\n");
    else
        printf("Connect!\n");
    if (send(sock, name, sizeof(name), 0) < 0){
        printf("Cant send\n");return -1;
    }
    else{
        printf("Can send!!\n");return 1;
    }
}
extern int send_packet(struct send_from_module ps, int sock){
    if (send(sock, ps, sizeof(ps), 0) < 0){
        printf("Cant send\n");return -1;
    }
    else{
        printf("Can send!!\n");return 1;
    } 
}
extern int get_ansver_code