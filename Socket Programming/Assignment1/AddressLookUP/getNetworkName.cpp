#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    netent *net = getnetent();
    printf("\nnetwork name->%s\n",net->n_name);
}