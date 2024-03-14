#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void merrge(int arr[],int i,int j,int m){
    //i is low,j is high ,m is middle one
    int b[25];
    int k=m+1;
    int start=i;
    int index=i;
    int low=i;
    while(start<=m && k<=j){
        if(arr[start]>=arr[k]){
            b[index++]=arr[k++];
        }
        else{
            b[index++]=arr[start++];
        }
    }
    if(k>j){
        //start is already initialised...
        for(;start<=m;){
            b[index++]=arr[start++];
        }
    }
    else if(start>m){
        for(;k<=j;){
            b[index++]=arr[k++];
        }
    }

    //don't need iterate forloop p++ like while loop; 
    for(int p=low;p<=j;p++){
        arr[p]=b[p];
    }
}


void mergsort(int arr[],int l,int h){
    if(l>=h){
        return;
    }
    else{
        int mid=(l+h)/2;
        mergsort(arr,l,mid);
        mergsort(arr,mid+1,h);
        merrge(arr,l,h,mid);
    }
}

void print(int ar[],int h){
    for(int i=0;i<=h;i++){
        printf("%d\t",ar[i]);
    }
    printf("\n");
}


void main(){
    int arr[]={3,4,1,8,5,9,2,999,782,1000,543,111};
    int n=sizeof(arr)/sizeof(arr[0]);
    printf("\nbefore merge sort\n");
    print(arr,n-1);
    mergsort(arr,0,n-1);
    printf("\nafter merge sort\n");
    print(arr,n-1);
}