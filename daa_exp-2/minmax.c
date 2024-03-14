#include<stdio.h>
#include<string.h>
void maxmin(int arr[],int l,int h,int *min, int *max){
    if(l==h){
        *max=arr[l];
        *min=arr[h];
        return ;
    }
    else if(l==h-1){
        if(arr[l]>=arr[h]){
            *max=arr[l];
            *min=arr[h];
        }
        else{
            *max=arr[h];
            *min=arr[l];
        }
    }
    else{
        int mid,max1,min1;
        mid=(l+h)/2;
        maxmin(arr,l,mid,min,max);
        maxmin(arr,mid+1,h,&min1,&max1);
        if(*min>min1){
            *min=min1;
        }
        if(*max<max1){
            *max=max1;
        }
    }
}

void main(){
    int low,high;
    int arr[]={7,1,2,6,8,4,5,3};
    int n=sizeof(arr)/sizeof(arr[0]);
    maxmin(arr,0,n-1,&low,&high);
    printf("%d %d",low,high);
}