// Ctrl+C should terminate the program once
#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void signalHandler(int signum){
    static int count = 0 ;
    count+=1;
    if(count==5)
        cout << "You've pressed Ctrl+C " << count << " times" << " but I will not be Terminating :) \n";
    else
    {
        cout << " ->You've pressed Ctrl+C " << count << " times\n";
    }
    
    
}
int main(){
    int x;
    signal(SIGINT,signalHandler);
    int count = 0;
    while(1){
        cout << "Ctrl+C Not pressed\n";
        sleep(1);        
    }

}