//reading file
#include<stdio.h>
#include<stdlib.h>
#define s 10001
void main(){
    FILE *fp;
    fp=fopen("random.txt","r");
    if(fp==NULL){
        printf("not opened");
    }
    int k=10000;
    int num=0,t;
    int i=0;
    int arr[s];
    //put it in array..
    while(num!=EOF){
        num= getw(fp);
        printf ("%d\n",num);
        arr[i]=num;
        i++;}   
   
    printf(" what is num %d ",arr[3]);
    //sort entire array and put in sorted.txt..
    for(int m=0;m<=10000;m++){
        for(int n=m+1;n<=10000;n++){
            if(arr[m]>arr[n]){
                t=*(arr +m);
                *(arr +m)=*(arr+n);
                *(arr +n)=t;
            }
        }
    }
    rewind(fp); //random numbers pointer..
    FILE *fw;
    fw=fopen("sorted.txt","w");
    if(fw==NULL){
        printf("not opened");
    }
    i=0;
   while(i<=k){
        num=arr[i];
        putw(num,fw);
        i++;
   }
    printf("sorted txt is created..");
    fclose(fw);
    //sorted clumps.txt creation

    FILE *fc;
    fc=fopen("clumps.txt","w");
    i=0;

    if(fc==NULL){
        printf("not opened");
    }

    while(i<2000){//1st in random order
        num=getw(fp);
        putw(num,fc);
        i++;
    }

    while(i<=k){//2st 2000 is in sorted manner 
        num=arr[i];
        putw(num,fc);
        i++;
    }

   fclose(fc);

    //create reverse order txt..
    for(int m=0;m<=10000;m++){//reverse order array is created..
        for(int n=m+1;n<=10000;n++){
            if(arr[m]<arr[n]){
                t=arr[m];
                arr[m]=arr[n];
                arr[n]=t;
            }
        }
    }
    rewind(fp);
    i=0;
    FILE *fr;
    fr=fopen("reverse.txt","w");
    if(fr==NULL){
        printf("not opened");
    }

    while(i<=k){
        num=arr[i];
        putw(num,fr);
    }
    printf(" rev %d %d",arr[k-1],arr[k]);
    fclose(fr);
    fclose(fp);



    
}