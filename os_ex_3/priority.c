#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//logic written in algorith mote.....
typedef struct node{
    int burst;
    int arrival;
    int process;
    int prior;
    int remaintime;
    struct node *next;
}node;
int x=sizeof(node);
node *head=NULL;

void insert(int pr,int ar,int bt,int prior){
    node *newnode;
    newnode=(node*)malloc(x);
    newnode->burst=bt;
    newnode->arrival=ar;
    newnode->process=pr;
    newnode->remaintime=bt;
    newnode->next=NULL;
    newnode->prior=prior;
    if(head==NULL){
        newnode->next=head;
        head=newnode;
    }
    else{
        if(head ==NULL||head->prior > newnode->prior){
            newnode->next=head;
            head=newnode;
        }
        else{
            node*temp=head;
            while(temp!=NULL && temp->prior<=newnode->prior){
                temp=temp->next;
            }
            newnode->next=temp->next;
            temp->next=newnode;
        }
        }
}
int input(){
    printf("enter no of process\t");
    int n,pri;
    scanf("%d",&n);
for(int i=0;i<n;i++){
    printf("enter arrival time and burst time\n");
    int arrival,burst;
    printf("arrival time is \t");
    scanf("%d",&arrival);//also ask enter process idd...
    printf("burst time is \t");
    scanf("%d",&burst);
    printf("enter priority");
    scanf("%d",&pri);
    insert(i+1,arrival,burst,pri);
}
    return n;
}
 void priority(int n){
    node *temp=head;int c;
    while(temp!=NULL){
        c+=temp->burst;
        printf(" pid is %d waiting %d ",temp->process,c-temp->burst);
        temp=temp->next;
    }
    int avgw=c/n;
 }
 void main(){
    int k;
    k=input();
    priority(k);

 }

