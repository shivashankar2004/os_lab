#include<stdio.h>
int digits(int s){
    int sum=0;
    if (s==0){
        return sum;
    }
    else{
        sum=s%10;
        
        return sum + digits(s/10);  
    }
}
void main(){
    printf("enter number");
    int n;
    scanf("%d",&n);
    int k=digits(n);
    printf("%d",k);
}