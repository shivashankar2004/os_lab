#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define s 10001
void main(){
    
    FILE *fc;
    fc=fopen("out.txt","r");
    int num;
    int arr[s];
    int l=0;
    while(fscanf(fc,"%d",&num)!=EOF){
        arr[l++]=num;
    }

    //to check if arrays are sorted..
    
    int flag=0;
    for (int a=0;a<s;a++){
        if(arr[a+1]>arr[a]){
            flag=1;
        }
        else{
            flag=0;
        }
    }
    if(flag==1){
        printf("array is sorted");
    }
    else{
        printf("array is not sorted");
    }
}