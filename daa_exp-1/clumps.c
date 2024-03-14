#include<stdio.h>
#include<stdlib.h>
void main(){
    FILE *fr;
    fr=fopen("random.txt","r");
    FILE *fs;
    fs=fopen("sorted.txt","r");
    FILE *fc;
    fc=fopen("clumps.txt","w");
    int i=0;
    int num;
    int sum=10000;
    while(i<=sum){
        if(i<2000){
            fscanf(fs,"%d",&num);
        }
        else if(i>4000 && i<=6000){
            fscanf(fs,"%d",&num);
        }
        else if(i>8001 && i<=sum){
            fscanf(fs,"%d",&num);
        }
        else{
            fscanf(fr,"%d",&num);
        }
        i++;
        fprintf(fc,"%d\t",num);

    }
}