#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct node
{
    int burst;
    int arrival;
    int process;
    int remaintime;
    struct node *next;
}node;
int x=sizeof(node);

void delete(node** head, node* target) {
    if (*head == NULL) {
        return;
    }
    if (*head == target) {
        *head = (*head)->next;
        free(target);
        return;
    }
    node* current = *head;
    while (current->next != NULL && current->next != target) {
        current = current->next;
    }
    if (current->next == NULL) {
        printf("Process not found!\n");
        return;
    }
    current->next = target->next;
    free(target);
}
void insert(node **head,int pid,int bt,int at){//mpdifying head pointer so double pointer..
    node *newnode;
    newnode=(node*)malloc(x);
    newnode->arrival=at;
    newnode->burst=bt;
    newnode->remaintime=bt;
    newnode->process=pid;
    if (*head==NULL||(*head)->arrival>newnode->arrival){
        newnode->next=*head;
        *head=newnode;
    }
    else{
        node * curr;
        curr=*head;
        while(curr->next!=NULL && curr->arrival<=(*head)->arrival){
            curr=curr->next;
        }
        newnode->next=curr->next;
        curr->next=newnode;
    }
}

node* findsjf(node *head,int ct){
    node*sj;
    sj=head;
    node*temp;
    temp=sj->next;
    if(head==NULL){
        return head;
    }
    while(temp!=NULL){
        if(temp->burst<sj->burst && temp->arrival<=ct){   
            sj=temp;      
        }
        temp=temp->next;
    }
    return sj;
}
void sjf(node *head){
    node* temp;
    int ct=0,n=0;
    int awt,atat;
    node *curr=head;
    while(curr!=NULL){
        curr=curr->next;
        n++;
    }
    int k=n;
    while(k!=0){
        temp=findsjf(head,ct);
        if(temp==NULL){
            ct++;//current time increased to increase range..
            continue;}
        int st=ct;
        int ft=st+temp->burst;
        int tat=ft-temp->arrival;
        int wt=ft-tat-temp->burst;
        printf("tat for %d tat is %d ",temp->process,tat);
        atat+=tat;
        awt+=wt;
        k--;  
        delete(&head,temp);
    }
    printf("avg wait time %d",awt/n);
}

void main(){
    node *head=NULL;
    insert(&head, 1, 0, 6);
    insert(&head, 2, 2, 4);
    insert(&head, 3, 1, 8);
    insert(&head, 4, 4, 3);
    insert(&head, 5, 3, 2);
    sjf(head);

    
}
