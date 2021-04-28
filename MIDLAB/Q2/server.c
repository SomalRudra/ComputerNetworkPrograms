#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <poll.h>
#include <sys/poll.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/ipc.h>

#include <sys/msg.h>
int nsfd1,nsfd2,nsfd3;
int sfd1,sfd2,sfd3,msgid;
char* candidate1score;
char* candidate2score;
char* candidate3score;

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

void* c1_aptTest(void*args)
{
   printf("Aptitude test started for c1 and Question sent");
    char* msg="What is 2+2?";
    int bytesend=send(nsfd1,msg,strlen(msg),0);
    char buff[1024];
    int reader=recv(nsfd1,&buff,sizeof(buff),0);
    printf("   Candidate answered %s",buff);
    if(buff=="4"){
        candidate1score = "10";
    }else{
        candidate1score = "0";
    }
    message.mesg_type = 1;
    strcpy(message.mesg_text,candidate1score);
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    
    
}
void* c2_aptTest(void*args)
{
  printf("Aptitude test started for c2 and Question sent");
    
    char* msg="What is 210+2?";
    int bytesend=send(nsfd2,msg,strlen(msg),0);
    char buff[1024];
    int reader=recv(nsfd2,&buff,sizeof(buff),0);
    printf("   Candidate answered %s\n",buff);
    if(buff=="212"){
        candidate2score = "10";
    }else{
        candidate2score = "0";
    }
    message.mesg_type = 2;
    strcpy(message.mesg_text,candidate2score);
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    
    
}
void* c3_aptTest(void*args)
{
  printf("Aptitude test started for c3 and Question sent");
     char* msg="What is 100-2?";
    int bytesend=send(nsfd3,msg,strlen(msg),0);
    char buff[1024];
    int reader=recv(nsfd3,&buff,sizeof(buff),0);
    printf("   Candidate answered %s",buff);
    if(buff=="98"){
        candidate3score = "10";
    }else{
        candidate3score = "0";
    }
    message.mesg_type = 1;
    strcpy(message.mesg_text,candidate1score);
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);    
}
  int max(int a,int b){
      if(a<b) return b;
      else return a;
  }

int main()
{
    //msgQ to store candidate scores
    key_t key;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    
    
    if((sfd1=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket 1 failed\n");
        return 0;
    }
    int opt1=1,opt2=1,opt3=1;
    if (setsockopt(sfd1, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt1, sizeof(opt1))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
    if((sfd2=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket 2 failed\n");
        return 0;
    }
    if (setsockopt(sfd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt2, sizeof(opt2))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
    if((sfd3=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket 3 failed\n");
        return 0;
    }
    if (setsockopt(sfd3, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt3, sizeof(opt3))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
    struct sockaddr_in addr1,addr2,addr3;
    addr1.sin_port=htons(7002);
    addr1.sin_family=AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(addr1.sin_addr));
    addr2.sin_port=htons(8002);
    addr2.sin_family=AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(addr2.sin_addr));
    addr3.sin_port=htons(9002);
    addr3.sin_family=AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(addr3.sin_addr));
    if(bind(sfd1,(struct sockaddr*)&addr1,sizeof(addr1))<0)
    {
        perror("bind 1 failed");
        return 0;
    }
    if(bind(sfd2,(struct sockaddr*)&addr2,sizeof(addr2))<0)
    {
        perror("bind 2 failed");
        return 0;
    }
    if(bind(sfd3,(struct sockaddr*)&addr3,sizeof(addr3))<0)
    {
        perror("bind 3 failed");
        return 0;
    }
    if(listen(sfd1,3)<0)
    {
        perror("listen 1 failed");
        return 0;
    }
    if(listen(sfd2,3)<0)
    {
        perror("listen 2 failed");
        return 0;
    }
    if(listen(sfd3,3)<0)
    {
        perror("listen 3 failed");
        return 0;
    }
    
    socklen_t addrlen1=sizeof(addr1);
    socklen_t addrlen2=sizeof(addr2);
    socklen_t addrlen3=sizeof(addr3);

    //select starts from here

    fd_set currentFDsets;
    FD_ZERO(&currentFDsets);
    int maxSize = max(max(sfd1,sfd2),sfd3)+1;

    while (1)
    {
        FD_SET(sfd1,&currentFDsets);
        FD_SET(sfd2,&currentFDsets);
        FD_SET(sfd3,&currentFDsets);
        int ready_fd = select(maxSize,&currentFDsets,NULL,NULL,NULL);

        if(FD_ISSET(sfd1,&currentFDsets)){
            nsfd1=accept(sfd1,(struct sockaddr*)&addr1,&addrlen1);
            int c;
            if((c=fork())==0){
                close(sfd1);
                pthread_t client1_thread;
                pthread_create(&client1_thread,NULL,&c1_aptTest,0);
                pthread_join(&client1_thread,NULL);
                close(nsfd1);
                exit(0);

            }
            close(nsfd1);
        }
        if(FD_ISSET(sfd2,&currentFDsets)){
            nsfd2=accept(sfd2,(struct sockaddr*)&addr2,&addrlen2);
            int c;
            if((c=fork())==0){
                close(sfd2);
                pthread_t client2_thread;
                pthread_create(&client2_thread,NULL,&c2_aptTest,0);
                pthread_join(&client2_thread,NULL);
                close(nsfd2);
                exit(0);

            }
            close(nsfd2);
        }if(FD_ISSET(sfd3,&currentFDsets)){
            nsfd3=accept(sfd3,(struct sockaddr*)&addr3,&addrlen3);
            int c;
            if((c=fork())==0){
                close(sfd3);
                pthread_t client3_thread;
                pthread_create(&client3_thread,NULL,&c3_aptTest,0);
                pthread_join(&client3_thread,NULL);
                close(nsfd3);
                exit(0);

            }
            close(nsfd3);
        }
    
    }  
    
    return 0;
}