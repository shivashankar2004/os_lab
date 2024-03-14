#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define s 10001
void main(){
    clock_t ti;
    ti=clock();
    FILE *fr;
    FILE *fc;
    fr=fopen("random.txt","r");
    fc=fopen("out.txt","w");
    int num;
    int arr[s];
    int l=0;
    while(fscanf(fr,"%d",&num)!=EOF){
        arr[l++]=num;
    }
    int n=sizeof(arr)/sizeof(arr[0]);
    int j=0;int t;
     for(int i=0;i<n-1;i++){
        for(int k=0;k<n-i-1;k++){
            if(arr[k]>arr[k+1]){
                t=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=t;
            }
        }
    }

    //implementation using pointers

    while(j<=n){
        num=*(arr+j);
        fprintf(fc,"%d\t",num);
        j++;
    }

    //to check numbers are sorted...

    
    ti=clock()-ti;
    double timetaken=((double)ti)/CLOCKS_PER_SEC;
    printf(" time taken to complete  is %f",timetaken);

}