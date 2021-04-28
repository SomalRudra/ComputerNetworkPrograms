#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
int main()
{
    int csfd;
    if((csfd=socket(AF_INET,SOCK_DGRAM,0))==0)
    {
        perror("socket failed\n");
        return 0;
    }
    struct sockaddr_in addr;
    
    addr.sin_port=htons(7001);
    addr.sin_family=AF_INET;

    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));
   
    
    // if(connect(csfd,(struct sockaddr*)&addr,(socklen_t)sizeof(addr))<0)
    // {
    //     perror("connet failed");
    //     return (0);
    // }
    
   
   printf("\n Write to Server From udp->");
                char buffWrite[1024];
                scanf("%s",buffWrite);
                sendto(csfd, (const char*)buffWrite, sizeof(buffWrite), MSG_WAITALL, 
                   (struct sockaddr*)&addr, sizeof(addr)); 
   char buff[1024];
                int n = recvfrom(csfd, buff, sizeof(buff), MSG_WAITALL, 
                         (struct sockaddr*)&addr, sizeof(addr)); 
                //read(nsfd2,buff,sizeof(&buff));
                printf("\n Value from server -> %s",buff);
   
    close(csfd);
    return 0;
}