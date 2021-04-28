#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <poll.h>
#define PORT1 7001
#define PORT2 8001
#define PORT3 9001

struct pollfd poll_fds[3];

int main(){
    sockaddr_in socket_address1,socket_address2,socket_address3;
    
    int sfd1 = socket(AF_INET,SOCK_STREAM,0);
    int sfd2 = socket(AF_INET,SOCK_STREAM,0);
    int sfd3 = socket(AF_INET,SOCK_STREAM,0);
    printf("\nSocket fd-> %d",sfd1);
    printf("\nSocket fd-> %d",sfd2);
    printf("\nSocket fd-> %d",sfd3);
    
    socket_address1.sin_family = AF_INET;
    socket_address1.sin_addr.s_addr = INADDR_ANY; //accept any incoming msg in this
    socket_address1.sin_port = htons(PORT1);

    socket_address2.sin_family = AF_INET;
    socket_address2.sin_addr.s_addr = INADDR_ANY; //accept any incoming msg in this
    socket_address2.sin_port = htons(PORT2);

    socket_address3.sin_family = AF_INET;
    socket_address3.sin_addr.s_addr = INADDR_ANY; //accept any incoming msg in this
    socket_address3.sin_port = htons(PORT3);
    
    
    int len_addr1 = sizeof(socket_address1);
    int len_addr2 = sizeof(socket_address2);
    int len_addr3 = sizeof(socket_address3);

    int bindValue1 = bind(sfd1,(struct sockaddr *)&socket_address1,len_addr1);
    printf("\nBind1 returns-> %d\n",bindValue1);

    int bindValue2 = bind(sfd2,(struct sockaddr *)&socket_address2,len_addr2);
    printf("\nBind2 returns-> %d\n",bindValue2);

    int bindValue3 = bind(sfd3,(struct sockaddr *)&socket_address3,len_addr3);
    printf("\nBind3 returns-> %d\n",bindValue3);

    int listenValue1 = listen(sfd1,3);
    printf("\nListen1 returns->%d\n",listenValue1);

    int listenValue2 = listen(sfd2,3);
    printf("\nListen2 returns->%d\n",listenValue2);

    int listenValue3 = listen(sfd3,3);
    printf("\nListen3 returns->%d\n",listenValue3);

  	char buf[1024];
  	
    
        poll_fds[0].fd = sfd1;
        poll_fds[1].fd = sfd2;
        poll_fds[2].fd = sfd3; 
        
        printf("\n 1st poll fd %d, 2nd poll fd %d,3rd poll fd %d",poll_fds[0].fd,poll_fds[1].fd,poll_fds[2].fd);

        // int pollReturnValue=poll(poll_fds,3,-1);
  		
  		// if (pollReturnValue<=0) 
  		// {
		// 	printf ("%d seconds elapsed.\n", 0);
		// 	return 0;
		// }
    	// for(int j=0;j<3;j++)
    	// {
        //     printf("\nnow j is %d\n",j);
      	// 	if(poll_fds[j].revents & POLLIN)
      	// 	{
        //           if(j==0){
        //               int nsfd1 = accept(sfd1,(struct sockaddr *)&socket_address1,(socklen_t*)&len_addr1);
        //               printf("\n NSFD1 -> %d",nsfd1);
        //               int c1 = fork();
        //               if(c1==0){
        //                   close(sfd1);
        //                   int readValue = read(nsfd1,buf,1024);
        //                   dup2(nsfd1,STDIN_FILENO);
        //                   execv("./C1.out",NULL);
        //               }else{
        //                   close(nsfd1);
        //               }
        //           }else if(j==1){
        //               int nsfd2 = accept(sfd2,(struct sockaddr *)&socket_address2,(socklen_t*)&len_addr2);
        //               printf("\n nsfd2->%d",nsfd2);
        //               int i=read(poll_fds[j].fd,buf,1024);
        // 		      write(1,buf,i);
        //           }else{
        //               int nsfd3 = accept(sfd3,(struct sockaddr *)&socket_address3,(socklen_t *)&len_addr3);
        //               printf("\n nsfd3->%d",nsfd3);
        //               int i=read(poll_fds[j].fd,buf,1024);
        // 		      write(1,buf,i);
        //           }
        //         //printf("  ----->from P%d\n",j+2);
      	
    	// }
    // }
    

   


    //new socket fd
    // int nsfd = accept(sfd1,(struct sockaddr *)&socket_address1,(socklen_t*)&len_addr);
    // printf("\naccept returns->%d\n",nsfd);

    // int c = fork();
    // if(c==0){
    //     printf("\n--------------- In child1---------------\n");
    //     close(sfd1);
    //     char* buffer1[1024];
    //     read( nsfd , buffer1, 1024); 
    //     printf("%s\n",buffer1 ); 
    //     send(nsfd , "Message From Server" , strlen("Message From Server") , 0 ); 
    // }else{
    //     sleep(10);
    //     printf("\n  ------------In Parent after Child1---------- \n");
    //     close(nsfd);
    //      int nsfd2 = accept(sfd1,(struct sockaddr *)&socket_address1,(socklen_t*)&len_addr);
    //     int child2 = fork();
    //     if(child2==0){
    //         close(sfd1);
    //          char* buffer2[1024];
    //         read( nsfd2 , buffer2, 1024); 
    //         printf("%s\n",buffer2 ); 
    //         send(nsfd2 , "Message From Server" , strlen("Message From Server") , 0 ); 
    //     }else{
    //         sleep(5);
    //         close(nsfd2);
    //         printf("\n  ------------In Parent after Child2---------- \n");
    //     }
    // }
    
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