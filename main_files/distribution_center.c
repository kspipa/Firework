#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../lib/api.h"
#include "../lib/tools.h"

static int sock = 0, neg = 0;
static char buffer[8192] = { 0 };
static module_struct *list[100];
static int _what_to_do(struct send_from_module *command){
    switch (command->command){
        case 1:
            int gen;
            if ((gen = _get_len_of_list(list)) != 0){
                list[gen + 1] = command->module_name;
            }
            else{
                list[gen] = command->module_name;
            }
            printf("Module has been init %c\n", command->module_name->name);
            return 1;
    }
}
static int start(){
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Cant create socket\n");
    else
        printf("Socket has been created\n");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((bind(sock, (struct sockaddr *)&addr, sizeof(addr))) < 0)
        printf("Cant bind socket\n");
    else
        printf("Socket has been binded\n");
    if ((listen(sock, 10)) < 0)
        printf("Socket cant listen\n");
    else
        printf("Socket listen\n");
    while(1){
        neg = accept(sock,(struct sockaddr*)NULL, NULL);
        read(neg, buffer, 8192);
        printf("Get some packets\n");
        struct send_from_module *get = (struct send_from_module *)buffer;
        printf("buf : %s\n", get->module_name->name);
        if (_what_to_do(get) == 1){
            _send_answer_code(get->module_name->sock, SUCCESS);
        }
        else{
            _send_answer_code(get->module_name->sock, FAILURE);
        }
        printf("%s\n", buffer);
    }
}
int main(){
    start();
}