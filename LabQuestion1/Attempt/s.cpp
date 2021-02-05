#include <stdio.h> 
#include <unistd.h> //for fork system call
#include <sys/types.h>
#include <stdlib.h> //for exit system call
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <string.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

char* c1fifo = "c1fifo";
char* c2fifo = "c2fifo";
char* s1fifo = "s1fifo";
char* s2fifo = "s2fifo";
char* Afifo = "Afifo";
char* Bfifo = "Bfifo";

char client_buffer[1025];
int clientFifoFds[2];
int child_pids[4];
struct pollfd poll_fds[2];
sigset_t set;

struct shared_memory
{
	int pid;
	int kill_count;
};
typedef shared_memory *shmptr;
shmptr shmptr1;


void server_handler(int signum){
	if(signum==SIGUSR1){
		//group1

		shmptr1->kill_count= shmptr1->kill_count+4;
		killpg(child_pids[2],SIGSTOP);
		killpg(child_pids[0],SIGCONT);
		killpg(child_pids[0],SIGUSR1);

		//writing in s1,s2 er buffer
		int s1_writefd = open(s1fifo,O_WRONLY);
		write(s1_writefd,client_buffer,1024);
		close(s1_writefd);

		int s2_writefd = open(s2fifo,O_WRONLY);
		write(s2_writefd,client_buffer,1024);
		close(s2_writefd);
		
	}else{
		//group2

		shmptr1->kill_count=shmptr1->kill_count+4;

		killpg(child_pids[0],SIGSTOP);
		killpg(child_pids[2],SIGCONT);
		killpg(child_pids[2],SIGUSR1);

		//writing in s1,s2 er buffer
		int A_writefd = open(Afifo,O_WRONLY);
		write(A_writefd,client_buffer,1024);
		close(A_writefd);

		int B_writefd = open(Bfifo,O_WRONLY);
		write(B_writefd,client_buffer,1024);
		close(B_writefd);

	}
}

void s1_handler(int signum){
	int fd = open(s1fifo,O_RDONLY);
	char s1buff[1024];
	read(fd,s1buff,1024);
	cout << "Message read in S1 child via server->" << s1buff << "\n";
	
}

void s2_handler(int signum){
	int fd = open(s2fifo,O_RDONLY);
	char s2buff[1024];
	read(fd,s2buff,1024);
	cout << "Message read in S2 child via server->" << s2buff << "\n";
	killpg(child_pids[0],SIGSTOP);
	
}

void A_handler(int signum){
	int fd = open(Afifo,O_RDONLY);
	char Abuff[1024];
	read(fd,Abuff,1024);
	cout << "Message read in A child via server->" << Abuff << "\n";
	
}

void B_handler(int signum){
	int fd = open(Bfifo,O_RDONLY);
	char Bbuff[1024];
	read(fd,Bbuff,1024);
	cout << "Message read in B child via server->" << Bbuff << "\n";
	killpg(child_pids[2],SIGSTOP);
	
}

void* polling(void *){
	printf("poll\n");
	pthread_sigmask(SIG_BLOCK,&set,NULL);

	
	clientFifoFds[0]=open(c1fifo,O_RDWR|O_NONBLOCK);
	clientFifoFds[1]=open(c2fifo,O_RDWR|O_NONBLOCK);

	poll_fds[0].fd=clientFifoFds[0];
	poll_fds[1].fd=clientFifoFds[1];

	poll_fds[0].events=POLLIN;
	poll_fds[1].events=POLLIN;

	while(1)
	{
		int return_value=poll(poll_fds,2,3000);
		if(return_value!=0)
		{
			if(return_value==-1)
			{	
				perror("Error in polling\n");
				exit(1);
			}
			char buff[1024];
			for(int i=0;i<2;i++)
			{
				if(poll_fds[i].revents & POLLIN)
				{
					if(read(poll_fds[i].fd,client_buffer,1024) > 0)
					{
						cout << "Data sent by client->" << client_buffer << "\n";
						//pthread_sigmask(SIG_UNBLOCK, &set, NULL);
						
					}
				}
			}
		}
	}

}

int main(){
	signal(SIGUSR1,server_handler);
	signal(SIGUSR2,server_handler);

	key_t k_shmptr=ftok("spid",65);
	int shm_spid=shmget(k_shmptr,sizeof(shared_memory),IPC_CREAT|0666);
	shmptr1=(shmptr)shmat(shm_spid,NULL,0);
	shmptr1->pid=getpid();
	shmptr1->kill_count=0;
		
	int pid=fork();
	//child s1
	if(pid==0){
		signal(SIGUSR1,s1_handler);
		
		while(1){
			sleep(1);
		};
	}else{
		child_pids[0]=pid;
		pid = fork();

		//child s2
		if(pid==0){
			signal(SIGUSR1,s2_handler);
			
			while(1){
				sleep(1);
			};


		}else{
			child_pids[1]=pid;
			pid=fork();

			//child A
			if(pid==0){
				signal(SIGUSR1,A_handler);
				
				while(1){
					sleep(1);
				};

			}else{
				child_pids[2]=pid;
				pid=fork();
				
				//child B
				if(pid==0){
					signal(SIGUSR1,B_handler);
					
					
					while(1){
						sleep(1);
					};

				}else{
					child_pids[3]=pid;
					//PARENT Process
					sleep(2);
					//client fifos
					mkfifo(c1fifo,0666);
					mkfifo(c2fifo,0666);

					//children fifos
					mkfifo(s1fifo,0666);
					mkfifo(s2fifo,0666);
					mkfifo(Afifo,0666);
					mkfifo(Bfifo,0666);

					//create group1 and 2

					//set group id of s1,s2 to that of s1
					setpgid(child_pids[0],child_pids[0]);
					setpgid(child_pids[1],child_pids[0]);

					//set group id of A,B to that of A
					setpgid(child_pids[2],child_pids[2]);
					setpgid(child_pids[3],child_pids[2]);

					cout << "\ns1 pid->" << child_pids[0] << " s2 pid->" << child_pids[1] << " A pid->" << child_pids[2] << " B pid->" << child_pids[3] << "\n";
					cout << "\ns1 group pid->" << getpgid(child_pids[0])  << " s2 group pid->" << getpgid(child_pids[1]) << " A group pid->" << getpgid(child_pids[2]) << " B  group pid->" << getpgid(child_pids[3]) << "\n";
					

					killpg(child_pids[0],SIGSTOP);
					killpg(child_pids[2],SIGSTOP);


					//signal set					
					sigemptyset(&set);
					sigaddset(&set,SIGUSR1);
					sigaddset(&set,SIGUSR2);

					pthread_t polling_thread;
					pthread_create(&polling_thread,NULL,polling,NULL);
					pthread_join(polling_thread,NULL);

				}

			}

		}
		
	}
	return 0;
}