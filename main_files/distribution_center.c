#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "lib/tools.h"

static int sock = 0, neg = 0;

int main(){
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Cant create socket");
    else
        printf("Socket has been created");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5005);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((bind(sock, (struct sockaddr *)&addr, sizeof(addr))) < 0)
        printf("Cant bind socket");
    else
        printf("Socket has been binded");
    if ((listen(sock, 10)) < 0)
        printf("Socket cant listen");
    else
        printf("Socket listen");
    while(1){

    }
    

}