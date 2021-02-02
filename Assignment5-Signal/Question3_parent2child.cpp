/* Parent sends sigusr1 to child
   child sends sigusr2 to parent
*/
#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void p2c(int signum){
    cout << "Received Signal From Parent\n\n";
}
void c2p(int signum){
    cout << "Received Signal From Child\n\n";
}

int main(){
    signal(SIGUSR1,p2c);
    signal(SIGUSR2,c2p);
    pid_t c= fork();
    if(c>0){
        //parent process
        raise(SIGUSR1);
        sleep(2);

    }else{
        raise(SIGUSR2);
        sleep(2);
    }
    return 0;
}