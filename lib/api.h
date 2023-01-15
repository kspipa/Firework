#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>


#define PORT    5005

static struct sockaddr_in serv_addr;
struct send_from_module{
	char *data; 		//Packet
	int verdict;		//ACCEPT = 1 or DROP = 0 other = 3
	int command;		//For api with distribution center
    char *name;         //Name of your module
};
extern int _get_ansver_code(int sock){
    char buf[5000];
    while(read(sock, buf, 5000) == 0);
    return (int *)buf;
}
extern int send_packet(struct send_from_module *ps, int sock){
    if (send(sock, ps, sizeof(ps), 0) < 0){
        printf("Cant send\n");return -1;
    }
    else{
        printf("Can send!!\n");return 1;
    } 
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
    struct send_from_module *init;
    init->command = 1;
    init->data = NULL;
    init->name = name;
    init->verdict = 3;
    send_packet(init, sock);
    _get_ansver_code(sock);
    
}

