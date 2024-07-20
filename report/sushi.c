#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#define num 5
sem_t available;
pthread_mutex_t mutex;
void *arrival(void *arg){
    int cid=*((int*)arg);
    printf("customer %d arrives at sushi bar\n",cid);
   // pthread_mutex_lock(&mutex);
    if(sem_trywait(&available)==0){
        printf("customed %d is seated \n\n",cid);
        sleep(1);
        sem_post(&available);
        printf("customer %d leaves sushi bar\n\n",cid);
    }
    else{
        printf(".customer %d waits\n",cid);
    }
   // pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
void *kitchen(void *arg){
    while(1){
        int avail;
        sleep(1);
        sem_getvalue(&available,&avail);
        printf("sushi prpares for %d customers\n ",num-avail);
    }
}

int main(){
    pthread_t customer[10];
    pthread_t chef;
    sem_init(&available,0,num);
    pthread_mutex_init(&mutex,NULL);
    int ids[10];
    for(int i=0;i<10;i++){
        ids[i]=i;
        pthread_create(&customer[i],NULL,arrival,&ids[i]);
    }
    pthread_create(&chef,NULL,kitchen,NULL);

    for(int i=0;i<10;i++){
        pthread_join(customer[i],NULL);
    }
    pthread_cancel(chef);
    sem_destroy(&available);
    pthread_mutex_destroy(&mutex);
    printf("sushi closed\n");
    return 0;
 }

// gcc sushi.c -o sus -pthread
// ./sus
