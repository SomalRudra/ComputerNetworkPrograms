#include <iostream>
#include <sys/types.h>
//#include <stdio.h>
#include <unistd.h>
using namespace std;

void createProcess(int processCount){
    if(processCount==5) return;
    cout << "creating new process for process: " << processCount+1 << "\n";
    pid_t id = fork();
    if(id==0){
        cout << "Child created with id "<< getpid() << "\n";
        cout << "Parent for child "<< getpid() << " is: " << getppid() << "\n";
   
    createProcess(processCount+1);
    }else{
        sleep(2);
    }
}

int main(){
    createProcess(0);
}


