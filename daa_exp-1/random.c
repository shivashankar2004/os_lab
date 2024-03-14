//creating a file.
#include<stdio.h>
#include<stdlib.h>
void main(){
    FILE *fp;
    fp=fopen("random.txt","w");
    if(fp==NULL){
        printf("not opened");
    }
    int i;
    int num;
    for (i=1;i<10000;i++){
        int num = (rand() % 
        (10000000001 - 10 + 1)) + 10; 
        fprintf(fp,"%d\t",num);
    }
    printf("file is created");
    fclose(fp);

}