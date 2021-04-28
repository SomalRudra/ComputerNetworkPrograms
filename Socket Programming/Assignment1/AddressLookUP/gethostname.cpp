#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    hostent *host;
    host = gethostent();
    printf("host name %s", host->h_name);
    endhostent();
}