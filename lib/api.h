#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define PORT    5005
#define SUCCESS 200
#define FAILURE 201

static struct sockaddr_in serv_addr;
struct module_struct{
    int sock;
    char *name;
};
struct send_from_module{
	char *data; 		//Packet
	int verdict;		//ACCEPT = 1 or DROP = 0 other = 3
	int command;		//For api with distribution center
    struct module_struct module_name;         //Struct of your module
};
extern int _get_answer_code(int sock){
    char buf[5000];
    while(read(sock, buf, 5000) == 0);
    return (int)buf;
}
extern int _send_answer_code(int sock, int *code){
    send(sock, code, sizeof(code), 0);
    if (_get_answer_code(sock) == SUCCESS){
        return SUCCESS;
    }
    else{
        return FAILURE;
    }
}
extern int send_packet(struct send_from_module *ps){
    if (send(ps->module_name.sock, ps, sizeof(ps), 0) < 0){
        printf("Cant send\n");return -1;
    }
    else{
        printf("Can send!!\n");return 1;
    } 
}
extern int init_module(struct module_struct *nn){
	if ((nn->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Cant create socket\n");
    else
        printf("Socket has been created\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if (connect(nn->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        printf("Cant connect to server\n");
    else
        printf("Connect!\n");
    struct send_from_module *init;
    init->command = 1;
    init->data = NULL;
    init->module_name = *nn;
    init->verdict = 3;
    send_packet(init);
    if (_get_answer_code(nn->sock) == SUCCESS){
        printf("Module has been initialized");
        return 1;
    }
    else{
        printf("Problem with init module");
        return -1;
    }
    
}

