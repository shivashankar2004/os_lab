#include<stdio.h>
#include<stdlib.h>

int ran(){
    int n;
    n=rand()%50+1;
    return n;
}
void main(){
    int p=1,i=0;
    printf("enter number\t");
    int n,a,b;
    scanf("%d",&n);
    while(1){
        if(p>=n){
            printf("\njohn wins : %d\n",p);
            break;
        }
        else{
            p=p*ran();
            printf("\njohn total: %d",p);
            if(p>=n){
                printf("\njohn wins %d",p);
                break;
                
            }
           
        }
        if(p>=n){
            printf("\nmicheal wins: %d\n",p);
            break;
        }
        else{
            p=p*ran();
            printf("\nmicheal total is %d",p);
            if(p>=n){
                printf("micheal wins");
                break;
            }
        }
        i++;
        printf("\nend of round %d\t",i);
        printf("\n");

    }
}