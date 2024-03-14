#include<stdio.h>
#include<stdlib.h>
#define s 10001
void main(){
    int arr[s];
    FILE *fs;
    fs=fopen("sorted.txt","w");
    if(fs==NULL){
        printf("not opened");
    }
    int j,num;
    for (int i=1,j=0;i<10000;i++){
         num = (rand() % 
        (10000000001 - 10 + 1)) + 10; 
        arr[j++]=num;   
    }
    int t;
    int n=sizeof(arr)/sizeof(arr[0]);
    //mistake in bubble sort..
    for(int i=0;i<n-1;i++){
        for(int k=0;k<n-i-1;k++){
            if(arr[k]>arr[k+1]){
                t=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=t;
            }
        }
    }
    int b=0;
    while(b<=n){
        num=arr[b];
        fprintf(fs,"%d \t",num);
        b++;
    }
    fclose(fs);
}