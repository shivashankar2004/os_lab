#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int N=50,p=1;
int numbergenerator(int n1,int n2){
    int v= n1 + rand() % (n1 - n2 +1);
    return v;
}

int main(){
    int num;
    while(p<N){
        pid_t pid=fork();
        if(pid<0){
            printf("failed to create process");
        }
        else if(pid==0){
            if(p>N){
                printf("micheal wins");
            }
            num=numbergenerator(2,9);
            p=p*num;
            return p;
        }
        else{
            if(p>N){
                printf("john wins");
            }
            int nu;
            nu=numbergenerator(2,9);
            p=p*nu;
            return p;
        }
    }
    return 0;
}