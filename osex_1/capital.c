#include<stdio.h>
#include<string.h>
#include<unistd.h>
void main(){
    char a[25];
    scanf("%s",a);
    int n=strlen(a);
    for (int i=0;i<n;i++){
        a[i]=a[i]-32;
    }
    
    printf("%s",a);
}