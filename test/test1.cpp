#include <semaphore.h>
#include <iostream>
#include <fcntl.h> 
#include<unistd.h>
using namespace std;

char* s11 = "s11";
char* s22 = "s22";
int main(){

	sem_t *mutex1 = sem_open(s11,O_CREAT,0666,0);
    sem_t *mutex2 = sem_open(s22,O_CREAT,0666,0);

    cout << "in p1 sending to p2";
    sem_wait(mutex1);
    sem_post(mutex2);
    cout << "in p1 after p2 asked me to continue";

	sem_unlink(s11);
    sem_unlink(s22); 

}