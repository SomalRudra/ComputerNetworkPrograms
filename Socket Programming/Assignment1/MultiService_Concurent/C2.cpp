// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
    //open a socket with socketfd, connect to the socket, send data

    int clientSocketfd = socket(AF_INET,SOCK_STREAM,0);
    printf("\nClient socketfd->%d\n",clientSocketfd);

   

    sockaddr_in serverSocketAddress;
    serverSocketAddress.sin_family = AF_INET;
    serverSocketAddress.sin_port = htons(PORT);

    //convert serverSocketAddress to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serverSocketAddress.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    }
    int len = sizeof(serverSocketAddress);
    int connectValue = connect(clientSocketfd,(struct sockaddr *)&serverSocketAddress,len);
    printf("\nconnect() returns %d\n",connectValue);



    char *buff="\nMessage From Client2\n";
    send(clientSocketfd,buff,strlen(buff),0);

    char srverBuff[1024];
    int readReturns = read(clientSocketfd,srverBuff,1024);
    printf("\n read returns->%d",readReturns);
    printf("\n Message received-> %s\n",srverBuff);

} 


