#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    printf( "in part2 ");
    char buf1[128];
    read(1,buf1,128);
    printf("%s\n",buf1);
    
}