#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	printf("From P1: Hello World!!!\n");
	FILE* fd=popen("./q6_p2.out","r");
	char buf[1024];
	read(fileno(fd),buf,1024);
	printf("From pipe: %s\n",buf);
	return 0;
}
