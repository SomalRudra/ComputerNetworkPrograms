#include <iostream>
#include <sys/types.h>
//#include <stdio.h>
#include <unistd.h>
using namespace std;

pid_t createProcess(){
	return fork();
}

int main(){

	for(int i = 0;i<4;++i){
		pid_t child = createProcess();
		if(child == 0){
			cout << "Process id is : " << getpid() << "\n";
		    cout << "Parent Process id is : " << getppid() << '\n';
		    //continue;
		}
		else{
			sleep(2);
			//cout << "Grand Parent -> process id : " << getpid() << '\n';
			break;
		}
	}
	}
