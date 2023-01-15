#include "../../lib/api.h"
int main()
{
    printf("first_module has been started\n");
    char* name = "first module";
    int sock;
    init_module(name, sock);
}
