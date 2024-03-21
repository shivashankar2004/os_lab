#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int burst;
    int arrival;
    int process;
    int remaintime;
    struct node *next;
}node;
int x=sizeof(node);
void insert(node **head,int pid,int bt,int at){
    node *newnode;
    newnode=(node*)malloc(x);
    newnode->arrival=at;
    newnode->burst=bt;
    newnode->remaintime=bt;
    newnode->process=pid;
    if(*head==NULL||(*head)->arrival>at){
        newnode->next=*head;
        *head=newnode;
    }
    else{
        node *curr;
        curr=*head;
        while(curr->next!=NULL && curr->next->arrival<=at){
                curr=curr->next;
        }
        newnode->next=curr->next;
        curr->next=newnode;
    }
}
void input(node **head){
    printf("enter o of process");
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("enter pid, arrival time and burst time for %d process\n",i+1);
        int arrival,burst,pid;
        printf("enter process is\t");
        scanf("%d",&pid);
        printf("arrival time is \t");
        scanf("%d",&arrival);//also ask enter process idd...
        printf("burst time is \t");
        scanf("%d",&burst);
        insert(head,pid,burst,arrival);
    }
}
void delete(node **head,node *tar){
    if(*head==NULL){
        return;
    }
    if(*head==tar){
        (*head)=(*head)->next;
        free(tar);
    }
    else{
        node *curr;
        curr=*head;
        while(curr->next!=NULL && curr->next!=tar){
            curr=curr->next;
        }
        if(curr->next==NULL){
            printf("no process");
            return;
        }
        curr->next=tar->next;
        free(tar);
    }
}
node *findsjf(node *head,int ct){
   node * sj=head;
   node *temp=head->next;
   while(temp!=NULL){
    if(temp->arrival<=ct && temp->remaintime>0){
        if(sj==NULL || temp->remaintime<sj->remaintime){
            sj=temp;
        }
    }
    temp=temp->next;
   }
   return sj;
}
void sjf(node *head){
    int ct=0;
    if(head==NULL){
        return;
    }
    node *curr=head;
    while(curr!=NULL){//change to process
       node *sj=findsjf(head,ct);
       if(sj==NULL){
            ct++;
            continue;
       }
       int st=ct;
       int ft=ct+1;
       ct=ft;
       
       if(sj->remaintime==0){
            int tat=ft-sj->arrival;
            int wt=tat-sj->burst;
            printf("%d\n",sj->process);
            delete(&head,sj);
       }
    }

}
void main(){
    node* head=NULL;
    input(&head);
    sjf(head);
}