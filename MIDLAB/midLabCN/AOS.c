#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/select.h>
#include <sys/un.h>
#define CONTROLLEN CMSG_LEN(sizeof(int))


static struct cmsghdr *cmptr = NULL;
char* unixsocket_paths[4] = {"/tmp/usfd1.socket","/tmp/usfd2.socket","/tmp/usfd3.socket","/tmp/usfd4.socket"};


int send_fd(int usfd, int fd_to_send) {
    
    struct iovec iov[1];
    struct msghdr msg;
    
    char buf[2] = {0, 0};

    iov[0].iov_base = buf;
    iov[0].iov_len = 2;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    
    cmptr = malloc(CONTROLLEN);
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    cmptr->cmsg_len = CONTROLLEN;
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;
    *(int *)CMSG_DATA(cmptr) = fd_to_send;

    if(sendmsg(usfd, &msg, 0) < 0) {
        perror("sendmsg");
        return -1;
    }

    return 0;
}
int max(int x, int y) 
{ 
    if (x > y) 
        return x; 
    else
        return y; 
} 
int main()
{
    int sfd1,sfd2,sfd3, sfd4;
    int nusfd[4];
    int unix_sfds[4];
	
    struct sockaddr_in adr1,adr2,adr3,adr4;
    
    sfd1=socket(AF_INET,SOCK_STREAM,0); 
    adr1.sin_family=AF_INET;
    adr1.sin_port=htons(5001);
    adr1.sin_addr.s_addr=inet_addr("127.0.0.1");
    socklen_t adrlen1=sizeof(adr1);
    bind(sfd1,(struct sockaddr*)&adr1,adrlen1);
    listen(sfd1,3);


    sfd2=socket(AF_INET,SOCK_STREAM,0); 
    adr2.sin_family=AF_INET;
    adr2.sin_port=htons(5002);
    adr2.sin_addr.s_addr=inet_addr("127.0.0.1");
    socklen_t adrlen2=sizeof(adr2);
    bind(sfd2,(struct sockaddr*)&adr2,adrlen2);
    listen(sfd2,3);

    

    sfd3=socket(AF_INET,SOCK_STREAM,0); 
    adr3.sin_family=AF_INET;
    adr3.sin_port=htons(5003);
    adr3.sin_addr.s_addr=inet_addr("127.0.0.1");
    socklen_t adrlen3=sizeof(adr3);
    bind(sfd3,(struct sockaddr*)&adr3,adrlen3);
    listen(sfd3,3);
    

    sfd4=socket(AF_INET,SOCK_STREAM,0);
    adr4.sin_family=AF_INET;
    adr4.sin_port=htons(5004);
    adr4.sin_addr.s_addr=inet_addr("127.0.0.1");
    socklen_t adrlen4=sizeof(adr4);
    bind(sfd4,(struct sockaddr*)&adr4,adrlen4);
    listen(sfd4,3);

    
	for(int i=0;i<4;i++)
	{
			unix_sfds[i] = socket(AF_UNIX,SOCK_STREAM,0);
			if(unix_sfds[i]<0)
			{
				perror("Could not create Unix socket");
			}
			struct sockaddr_un adr;
			adr.sun_family = AF_UNIX;
			strcpy(adr.sun_path,unixsocket_paths[i]);
			unlink(unixsocket_paths[i]);
            socklen_t l=sizeof(adr);
            bind(unix_sfds[i],(struct sockaddr*)&adr,l);
            listen(unix_sfds[i],3);
            struct sockaddr cliadr;
            socklen_t len=sizeof(cliadr);
            nusfd[i] = accept(unix_sfds[i], (struct sockaddr*)&cliadr, &len);
	}

    fd_set fds_select;
    FD_ZERO(&fds_select); 

    int mxfd=max(max(sfd1,sfd4),max(sfd2,sfd3))+1;

	while(1)
    {
        FD_SET(sfd1,&fds_select);
        FD_SET(sfd2,&fds_select);
        FD_SET(sfd3,&fds_select);
        FD_SET(sfd4,&fds_select);

        int r=select(mxfd,&fds_select,NULL,NULL,NULL);
        if(r>0)
        {
           int nsfd;
                if(FD_ISSET(sfd1,&fds_select))
                {
                   nsfd=accept(sfd1,(struct sockaddr*)&adr1,&adrlen1);
                   send_fd(nusfd[0],nsfd); 
                }
                else if(FD_ISSET(sfd2,&fds_select))
                {
                   nsfd=accept(sfd2,(struct sockaddr*)&adr2,&adrlen2);
                   send_fd(nusfd[1],nsfd); 
                }
                else if(FD_ISSET(sfd3,&fds_select))
                {
                   nsfd=accept(sfd3,(struct sockaddr*)&adr3,&adrlen3);  
                   send_fd(nusfd[2],nsfd); 
                }
                else
                {
                   nsfd=accept(sfd4,(struct sockaddr*)&adr4,&adrlen4);  
                   send_fd(nusfd[3],nsfd); 
                   close(sfd4); //so that no more client requests can come here.
                }  
        }

    }

return 0;
}