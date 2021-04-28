#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#define CONTROLLEN CMSG_LEN(sizeof(int))
#define PORT 10000

static struct cmsghdr *cmptr = NULL;

char *unixsocket_paths = "/tmp/usfd4.socket";

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

    cmptr = (struct cmsghdr*)malloc(CONTROLLEN);
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;

    if(recvmsg(usfd, &msg, 0) < 0) {
        perror("recvmsg");
        return -1;
    }
    printf("%d %d\n",buf[0],buf[1]);
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
	int rfd;
	if((rfd = recv_fd(usfd)) < 0) {
        perror("recv_fd");
        exit(1);
    }
    
    
    int sfd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(sfd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sfd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(sfd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

   

}