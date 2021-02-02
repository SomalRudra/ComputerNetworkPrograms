#include <stdio.h>
#include <unistd.h>
#include <string.h> 
int main()
{
    printf("p1");
    FILE* file=popen("./q72.out","r");
	char buf[1024];
	read(fileno(file),buf,1024);
	printf("From pipe2: %s",buf);
	pclose(file);
    return 0;
}
