#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int max;

int isprime(int n){
    for(int i=2;i*i<n;i++){
        if(n%i==0){
            return 0;
        }
        printf("\t");
    }
    return 1;
}
//it should return null poniter;
void *printprimes(void *n){
    int s=*((int *)n);
    //2 is start for t1,3 is start for t2..
    for(int i=s;i<max;i=i+4){
        if(isprime(i)){
            printf("%d",i);
        }
    }
    return NULL;
}
int main(int argc,char *argv[]){
    if(argc!=2){
        fprintf(stderr,"number not entered correctly");
        return EXIT_FAILURE;
    }
    max=atoi(argv[1]);
    pthread_t tid[4];
    int start[]={2,3,4,5};
    for(int i=0;i<4;i++){
        pthread_create(&tid[i],NULL,printprimes,&start[i]);
    }
    for(int i=0;i<4;i++){
        pthread_join(tid[i],NULL);
    }

    return EXIT_SUCCESS;
}
//to compile and run this code
//gcc -o primethread primethread.c -pthread
//./primethread any_number
//500
// 243711192331434759677179831031071271311391511631671791911992112232272392512632712833073113313473593673793834194314394434634674794874914995913172529374149536173899710110911312113714915716917318119319722923324125726927728128929331331733