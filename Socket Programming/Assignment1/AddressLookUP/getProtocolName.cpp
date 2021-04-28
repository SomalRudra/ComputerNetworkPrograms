#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    protoent *proto;
    proto = getprotoent();
    printf("Protocol name %s, Proto-> %d, Aliases-> %s", proto->p_name,proto->p_proto,proto->p_aliases);
    endhostent();
}