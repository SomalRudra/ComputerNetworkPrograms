// Ctrl+C should terminate the program once
#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void signalHandler(int signum){
    cout << "\n I will not be terminating :)";
    
    
}
int main(){
    int x;
    signal(SIGINT,signalHandler);
    int count = 0;
    cout << "Every 5th time Abort will be called";
    while(1){
        count++;
        if(count%5!=0)
            cout << "\nLooped for " << count << " times";
        else{
            // kill(getpid(),SIGINT);
             raise(SIGINT);
        }
        sleep(1);        
    }

}