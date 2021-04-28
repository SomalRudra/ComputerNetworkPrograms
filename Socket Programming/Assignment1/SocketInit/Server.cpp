#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#define PORT 8080
int main(){
    sockaddr_in socket_address;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    printf("\nSocket fd-> %d",sockfd);

    // if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
    //                                               &opt, sizeof(opt))) 
    // { 
    //     perror("setsockopt"); 
    //     exit(EXIT_FAILURE); 
    // } 
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY; //accept any incoming msg in this
    socket_address.sin_port = htons(PORT);
    int len_addr = sizeof(socket_address);

    int bindValue = bind(sockfd,(struct sockaddr *)&socket_address,sizeof(socket_address));
    printf("\nBind returns-> %d\n",bindValue);

    int listenValue = listen(sockfd,3);
    printf("\nlisten returns->%d\n",listenValue);

    //new socket fd
    int nsfd = accept(sockfd,(struct sockaddr *)&socket_address,(socklen_t*)&len_addr);
    printf("\naccept returns->%d\n",nsfd);
    
    char* buffer[1024];
    read( nsfd , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(nsfd , "Message From Server" , strlen("Message From Server") , 0 ); 
    
    return 0; 


}
/*
Socket creation:
    int sockfd = socket(domain, type, protocol)
    sockfd: socket descriptor, an integer (like a file-handle)
    domain: integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
    type: communication type
    SOCK_STREAM: TCP(reliable, connection oriented)
    SOCK_DGRAM: UDP(unreliable, connectionless)
    protocol: Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.(man protocols for more details)
*/

/* Bind: 
        int bind(int sockfd, const struct sockaddr *addr, 
                          socklen_t addrlen);
        After creation of the socket, bind function binds the socket to the address
        and port number specified in addr(custom data structure). In the example code,
        we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address.
*/

/* Listen:
        int listen(int sockfd, int backlog);
    
    It puts the server socket in a passive mode, where it waits for the
    client to approach the server to make a connection. 
    The backlog, defines the maximum length to which the queue of pending connections 
    for sockfd may grow. If a connection request arrives when the queue is full, 
    the client may receive an error with an indication of ECONNREFUSED.
*/

/*
Accept:
    int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    It extracts the first connection request on the queue of pending connections 
    for the listening socket, sockfd, creates a new connected socket, 
    and returns a new file descriptor referring to that socket.
     At this point, connection is established between client and server,
     and they are ready to transfer data.

*/