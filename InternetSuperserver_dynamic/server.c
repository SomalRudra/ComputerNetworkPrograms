#include "../cn.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define NO_OF_REQUEST 10
#define MAXSERVICES 255

void encrypt(char* s)
{
	for(int i=0;i<strlen(s);i++)
	{
		s[i] = s[i]-'a'+'1';
	}
}



int ports[MAXSERVICES] = {0};
char* operations[MAXSERVICES] = {NULL};
char* type[MAXSERVICES] = {NULL};
struct sockaddr_in addr[MAXSERVICES];
int ind = 0;
int sfd[MAXSERVICES];
FILE* fp;
fd_set readset;int m = -1;

void sig_handler(int alrm)
{
	char buffer[255];
	while(fscanf(fp,"%[^\n]s",buffer)==1)
	{
		while(fgetc(fp)!='\n'&&fgetc(fp)!=EOF);
		printf("reading: %s\n",buffer);
		char* tok = strtok(buffer," ");
		tok = strtok(NULL," ");
		type[ind] = strdup(tok);
		printf("Type: %s\n",type[ind]);
		if(strcmp(type[ind],"tcp")==0)
		{
			sfd[ind] = socket(AF_INET,SOCK_STREAM,0);
			if(sfd[ind]<0)
			{
				perror("socket not created");
				exit(0);
			}
		}
		else
		{
			sfd[ind] = socket(AF_INET,SOCK_DGRAM,0);
			if(sfd[ind]<0)
			{
				perror("socket not created");
				exit(0);
			}
		}
        //The first call to strtok must pass the C string to tokenize, and subsequent calls must specify NULL as the first argument, 
        //which tells the function to continue tokenizing the string you passed in first. 
		tok = strtok(NULL," ");
		tok = strtok(NULL," ");
		printf("Port No: %s\n",tok);
		addr[ind].sin_family = AF_INET;
		addr[ind].sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		addr[ind].sin_port = htons(atoi(tok));
		if(bind(sfd[ind],(struct sockaddr*)&addr[ind],sizeof(addr[ind]))<0)
		{
			perror("Could not bind!");
			exit(0);
		}
		if(strcmp(type[ind],"tcp")==0)
		{
			listen(sfd[ind],NO_OF_REQUEST);
		}
		m = (m<sfd[ind])?sfd[ind]:m;
		FD_SET(sfd[ind],&readset);
		tok = strtok(NULL," ");
		operations[ind] = strdup(tok);
		ind++;
	}
	signal(SIGUSR1,sig_handler);
	printf("Updated successfully..\nm = %d\n",m);
}

int main(int argc, char const *argv[])
{
	signal(SIGUSR1,sig_handler);
	char buffer[255];
	FD_ZERO(&readset);
    //open() is a system call and specific to Unix-based systems and 
    //it returns a file descriptor. You can write to a file descriptor using write() which is another system call. 
    //fopen() is an ANSI C function call which returns a file pointer and it is portable to other OSes.
    
	fp = fopen("config.txt","r");
	if(fp==NULL)
	{
		perror("Configuration file not opened");
		exit(0);
	}
    // The fscanf() function is used to read formatted input from the file. 
    // It works just like scanf() function but instead of reading data from the standard input it reads the data from the file.
    
    fscanf(fp,"%[^\n]s",buffer);
    //fscanf("%[^\n]", buffer); will read all characters until you reach \n (or EOF) and put them in s. It is a common idiom to read a whole line in C.
    // buffer takes the list of column names from the config file
    
	while(fgetc(fp)!='\n'&&fgetc(fp)!=EOF);
	    sig_handler(10);
	printf("m = %d\n",m);
	int r,nsfd;
	pid_t p;
    for(int i=0; i<ind; i++){
        printf("\noperation here is->%s",operations[i]);
    }
	while(1)
	{
		printf("\nWaiting...\n");
		r = select(m+1,&readset,NULL,NULL,NULL);
		if(r>0)
		{
			for(int i=0;i<ind;i++)
			{
                
				if(FD_ISSET(sfd[i],&readset))
				{
					if(strcmp(type[i],"tcp")==0)
					{
                        printf("inside tcp");
						nsfd = accept(sfd[i],NULL,NULL);
						if(nsfd<0)
						{
							perror("Accept failed!");
						}
						else
						{
							p = fork();
							if(p<0)
							{
								perror("Fork failed!");
							}
							else if(p>0)
							{
								close(nsfd);
								printf("Operation: %s\n",operations[i]);
							}
							else
							{
								close(sfd[i]);
								dup2(nsfd,0);
								dup2(nsfd,1);
								char* arg[1]= {NULL};
								execv(operations[i],arg);
							}
						}
					}
					else
					{
						printf("UDP Invoked!\n");
						struct sockaddr_in cl_addr;
						int len = sizeof(cl_addr),sz;
						char mess[50];
						if((sz = recvfrom(sfd[i],mess,50,0,(struct sockaddr*)&cl_addr,&len))<0)
						{
							perror("Could not receive");
						}
						else
						{
							mess[sz] = '\0';
							printf("Received: %s\nProcessing...\n",mess);
							encrypt(mess);
							printf("Sending...\n");
							if(sendto(sfd[i],mess,strlen(mess),0,(struct sockaddr*)&cl_addr,len)<0)
							{
								perror("Could not send");
							}
							else
							{
								printf("Sent successfully..\n");
							}
						}
					}
				}
				else
				{
					FD_SET(sfd[i],&readset);
				}
			}
		}
	}
	return 0;
}
