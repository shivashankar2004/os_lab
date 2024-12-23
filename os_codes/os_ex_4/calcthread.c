#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// change void *calcAvg(int *nums[]) to void *calcAvg(void* thread_args). Then in 'calcAvg' write int *nums = (int*)thread_args. Now you can use nums in that function just as if you had called calcAvg(nums), which in in essence you have done.

int s=0;//size
void *avg(void * av){
    int *nums=(int*)av;
    int sum=0;
    for(int i=0;i<s;i++){
        sum+=nums[i];
    }
    printf("avg is %d\n",sum/s);
    return NULL;
}
void *minmax(void *av){
    int *nums=(int *)av;
    int min=nums[0];
    int max=nums[s-1];
    for(int i=0;i<s;i++){
        if(nums[i]<min){
            min=nums[i];
        }
        if(nums[i]>max){
            max=nums[i];
        }
    }
    printf("minimum is %d\n",min);
    printf("maximum is %d\n",max);
    return NULL;
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "enter array of inregers");
        return EXIT_FAILURE;
    }
    int *arr=(int*)malloc((argc-1)*sizeof(int));
    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
        s++;
    }
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1,NULL,avg,(void*)arr);
    pthread_create(&t2,NULL,minmax,(void*)arr);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    return EXIT_SUCCESS;
}
//gcc -o calcthread calcthread.c -pthread
// ./calcthread 20 23 67 54 11 o/p is
// avg is 35
// minimum is 11
// maximum is 67