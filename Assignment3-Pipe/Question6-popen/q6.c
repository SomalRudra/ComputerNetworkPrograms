#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	printf("From P1: Hello World!!!\n");
	//on success, popen returns a pointer to an open stream that can  be used to read or write to the pipe
	FILE* fd=popen("./q6_p2.out","r");
	char buf[1024];
	read(fileno(fd),buf,1024);
	printf("From pipe: %s\n",buf);
	return 0;
}
