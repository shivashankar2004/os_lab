#include<stdio.h>
void main(){
    int a[20]={0};
    printf("enter no of numbers");
    int n,s=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        s=s+a[i];
    }
    printf("%d",s);
}