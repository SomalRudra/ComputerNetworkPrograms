#include <bits/stdc++.h>
#include <unistd.h> 
using namespace std;

int main(){
    int x = dup(STDIN_FILENO);
    printf("x->%d",x);
}