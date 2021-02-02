#include<stdio.h>  
#include<unistd.h>  
#include<fcntl.h> 
#include<stdlib.h> 
#include <semaphore.h>
const char* name1="s1";
const char* name2="s2";


void p1(int fd)
{
	sem_t* s1=sem_open(name1,O_EXCL);
	sem_t* s2=sem_open(name2,O_EXCL);
	char c;
	printf("p1");
	while(read(fd,&c,1)==1)
	{
		if(c=='\n')
		{
			printf("\n");
			sem_post(s1);
			sem_wait(s2);
			printf("p1");
		}
		else
		{
			printf("%c",c);
		}
	}
	
}
void p2(int fd)
{
	printf("p2");
	sem_t* s1=sem_open(name1,O_EXCL);
	sem_t* s2=sem_open(name2,O_EXCL);
	sem_wait(s1);
	char c;
	while(read(fd,&c,1)==1)
	{
		if(c=='\n')
		{
			printf("\n");
			sem_post(s2);
			sem_wait(s1);
			printf("p2");
		}
		else
		{
			printf("%c",c);
		}
	}
	sem_post(s2);
	
}
int main()
{
	sem_t *mutex1 = sem_open(name1,O_CREAT,0666,0);
    sem_t *mutex2 = sem_open(name2,O_CREAT,0666,0);
	int fd;
   
	fd=open("input.txt",O_RDONLY);
	
	int c=fork();
	if(c>0)
	{
		p1(fd);			
	}
	else
	{
		p2(fd);
	}
	sem_unlink(name1);
    sem_unlink(name2); 
	return 0;
}
/*
     Named semaphores provide access to a resource between multiple processes. 
     Unnamed semaphores provide multiple accesses to a resource within a single process 
     or between related processes.

     so, if a multiple threads of a process is working, use un-named semaphore.
     else, if multiple processes are involved use named semaphore
*/

/* 
	sem_open	-> Initializes an named semaphore
    sem_close 	-> Deallocates the specified named semaphore
	sem_unlink -> Removes a named semaphore
	sem_wait -> for waiting
	sem_post -> for resume after wait
*/

/*


       sem_open() creates a new POSIX semaphore or opens an existing
       semaphore.  The semaphore is identified by name.  For details of
       the construction of name, see sem_overview(7).

       The oflag argument specifies flags that control the operation of
       the call.  (Definitions of the flags values can be obtained by
       including <fcntl.h>.)  If O_CREAT is specified in oflag, then the
       semaphore is created if it does not already exist.


       If both O_CREAT and O_EXCL are specified in oflag, then an error is returned if a
       semaphore with the given name already exists.

       If O_CREAT is specified in oflag, then two additional arguments
       must be supplied.  The mode argument specifies the permissions to
       be placed on the new semaphore, as for open(2).  (Symbolic
       definitions for the permissions bits can be obtained by including
       <sys/stat.h>.)  The permissions settings are masked against the
       process umask.  Both read and write permission should be granted
       to each class of user that will access the semaphore.  The value
       argument specifies the initial value for the new semaphore.  If
       O_CREAT is specified, and a semaphore with the given name already
       exists, then mode and value are ignored.
*/