//Services are represnted by the port number portion of each address. Each Service is offered on a unique, well known port number
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    servent *service = getservent();
    printf("service->name %s, port number->%d",service->s_name,service->s_port);
    endservent();
}