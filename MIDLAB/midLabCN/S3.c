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
char *unixsocket_paths = "/tmp/usfd3.socket";

int recv_fd(int usfd) {

    struct iovec iov[1];
    char buf[2];
    int newfd;

    struct msghdr msg;

    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf);
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    cmptr = malloc(CONTROLLEN);
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;

    if(recvmsg(usfd, &msg, 0) < 0) {
        perror("recvmsg");
        return -1;
    }

    newfd = *(int *)CMSG_DATA(cmptr);

    return newfd;
}


int main(int argc, char *argv[]) {
	struct sockaddr_un addr;
	char buf[100];
	int usfd,rc;

	if((usfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		exit(1);
	}
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, unixsocket_paths);
	if(connect(usfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("connect error");
		exit(1);
	}

    int ind=-1;
    int client_support[100];
    fd_set fdsets_select;
    int maxm=-1;
    maxm = maxm>usfd ? maxm :usfd;
    maxm+=1;
    
    while(1)
    {
        FD_SET(usfd,&fdsets_select);
        
        for(int i=0;i<=ind;i++)
            FD_SET(client_support[i],&fdsets_select);

        int n=select(maxm,&fdsets_select,NULL,NULL,NULL);
        if(n>0)
        {
            if(FD_ISSET(usfd,&fdsets_select))
            {
                int rfd;
                if((rfd = recv_fd(usfd)) < 0) {
                    perror("recv_fd");
                }
                else
                {
                    client_support[++ind]=rfd;
                    maxm=max(maxm,rfd)+1;
                    continue;
                }
            }

            for(int i=0;i<=ind;i++)
            {
                if(FD_ISSET(client_support[i],&fdsets_select))
                {
                    char buff[1024];
                    int x=read(client_support[i], buff,1024);
                    printf("%s\n",buff);
                }
            }
        }
    }
    
	return 0;
}