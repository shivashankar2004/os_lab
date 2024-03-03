#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

 typedef struct block{
    int pid;
    int cpuburst;
    int waittime;
    struct block*next;
    struct block*prev;
} block;
struct block *head,*tail;

int avgtime(int arr[],int n){
    int s=0;
    for(int i=0;i<n;i++){
        
        s+=arr[i];
    }
    return (s/n);
}

void newnode(int id,int bt,int wt){
    block *node;
    node=(block*)malloc(sizeof(block));
    node->pid=id;
    node->cpuburst=bt;
    node->waittime=wt;
    node->next=NULL;
    node->prev=NULL;
    if(head==NULL){
        head=tail=node;
    }
    else{
        tail->next=node;
        node->prev=tail;
        tail=node;
    }
  
}
void print(int arr[],int n){
    block *temp=head;
     printf("process:\tburst time\twaiting time\ttat time is \n");
        // printf("burst time\t");
        // printf("waiting time\t");
        // printf("tat time is \n");
    for(int i=0;i<n;i++){
        printf("%d\t %d\t %d\t %d",temp->pid,temp->cpuburst,temp->waittime,arr[i]);
        printf("\n");
       
        temp=temp->next;
        
    }
}
    void tattime(int tat[],int n){
        block *temp=head;
        int i=0;
        while(temp!=NULL){
            tat[i]=temp->cpuburst + temp->waittime;
            temp=temp->next;
            i++;
        }
        int avg=avgtime(tat,n);
    }
void beginsert(){
    block *node;
    printf("enter no of process");
    int n,a,b,p;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("enter arrival time for process %d",i+1);
        scanf("%d",&a);
        printf("enter burst time for process %d",i+1);
        scanf("%d",&b);
        printf("enter process id for process %d",i+1);
        scanf("%d",&p);
        newnode(p,b,a);
        
    }
    int tat[n];
    tattime(tat,n);
    print(tat,n);
    
}

void main(){
    beginsert();

    
}