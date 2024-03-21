#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//logic written in algorith mote.....
typedef struct node{
    int burst;
    int arrival;
    int process;
    int remaintime;
    struct node *next;
}node;

int x=sizeof(node);
node *head,*root;

void insert(int pr,int ar,int bt){
    node *newnode;
    newnode=(node*)malloc(x);
    newnode->burst=bt;
    newnode->arrival=ar;
    newnode->process=pr;
    newnode->remaintime=bt;
    newnode->next=NULL;

    if(head==NULL){//in circular..
        newnode->next=head;
        head=newnode;
    }
    else{
        node*temp=head;
        while(temp->next!=NULL ){//in circular linked list..
            temp=temp->next;
        }
        newnode->next=temp->next;
        temp->next=newnode;
    }
}


void input(){
    printf("enter no of process\t");
    int n;
    scanf("%d",&n);
for(int i=0;i<n;i++){
    printf("enter arrival time and burst time\n");
    int arrival,burst;
    printf("arrival time is \t");
    scanf("%d",&arrival);
    printf("burst time is \t");
    scanf("%d",&burst);
    insert(i+1,arrival,burst);
}
  

}

void roundrobin(int tq){
node *temp, *curr;
int s=0,count=0, k=0,i=0,tat=0,wt=0;
temp=head;
do{
    k++;
    temp=temp->next;
}while(temp!=NULL);
int y=k;
curr=head;
for(s=0,i=0;k!=0;){
    if(curr->remaintime<=tq && curr->remaintime>0){
        s=s+curr->remaintime;
        curr->remaintime=0;
        count=1;
    }
    else if(curr->remaintime>0){
        s+=tq;
        curr->remaintime=curr->remaintime-tq;
    }
    if(curr->remaintime==0 && count==1){
        k--;
        printf("%d %d",curr->process,curr->burst);
        wt=wt+s-curr->arrival-curr->burst;
        tat=tat+s-curr->arrival;
        count=0;
    }
    if(curr->next==NULL){
        curr=head;
    }
    else{
        curr=curr->next;
    }
    }
    int avgwt=wt/y;
    int avgtat=tat/y;
    printf("avg time %d",avgwt);
    printf("avg time %d",avgtat);


}
void main(){
    int tq;
    input();
    printf("enter time quantum;");
    scanf("%d",&tq);
    roundrobin(tq);

}