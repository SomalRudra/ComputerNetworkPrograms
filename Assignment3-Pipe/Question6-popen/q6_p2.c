#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	char buff[1024];
	fgets(buff,5,stdin);
	write(1,buff,1024);
	return 0;
}
