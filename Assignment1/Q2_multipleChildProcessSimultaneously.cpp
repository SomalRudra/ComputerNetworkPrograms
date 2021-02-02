#include<stdio.h> 
#include<bits/stdc++.h>
#include <unistd.h> //for fork system call
#include <sys/types.h>
#include <stdlib.h> //for exit system call
#include <sys/wait.h> //for wait system call
using namespace std;
int main() 
{ 
    
	for(int i=0;i<2;i++) // loop will run n times (n=5) 
	{ 
		if(fork() == 0) 
		{ 
			cout << "Child-> "<< getpid() << "from Parent->" << getppid();
			exit(0); 
		} 
	} 
    cout << "waiting ";
	for(int i=0;i<2;i++) // loop will run n times (n=5) 
	wait(NULL); 
	
} 

