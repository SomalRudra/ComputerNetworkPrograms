#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
    int a[2];
    //int b[2];
    pipe(a);
    //pipe(b);
    int c=fork();
    if(c>0)
    {
         close(a[0]);
        //close(b[1]);

        char buf1[128];
         cout << "write message to pipeA: ";
         fgets(buf1,128,stdin);
         write(a[1],buf1,128);
        // char buf2[128];
        // read(b[0],buf2,128);
        // printf("%s\n",buf2);
    }
    else
    {
        dup2(a[0],1);
        close(a[1]);
        //close(b[0]);
        cout << "in child";
        execv("./q4_part2.out",NULL); 
    }
    
}