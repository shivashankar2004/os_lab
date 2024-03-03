#include<stdio.h>  
#include<conio.h>  
  
struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    struct Process* next;
};

struct Process* head = NULL;

void insertProcess(int process_id, int arrival_time, int burst_time) {
    struct Process* new_process = (struct Process*)malloc(sizeof(struct Process));
    new_process->process_id = process_id;
    new_process->arrival_time = arrival_time;
    new_process->burst_time = burst_time;
    new_process->remaining_time = burst_time;
    new_process->next = NULL;
    
    if (head == NULL) {
        head = new_process;
        new_process->next = head;
    } else {
        struct Process* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = new_process;
        new_process->next = head;
    }
}

void roundRobin(int quantum) {
    struct Process* current = head;
    int sum = 0, count = 0, y = 0, i = 0, wt = 0, tat = 0;
    float avg_wt, avg_tat;
    
    struct Process* temp = head;
    do {
        y++;
        temp = temp->next;
    } while (temp != head);
    
    printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
    for (sum = 0, i = 0; y != 0; ) {
        if (current->remaining_time <= quantum && current->remaining_time > 0) {
            sum = sum + current->remaining_time;
            current->remaining_time = 0;
            count = 1;
        } else if (current->remaining_time > 0) {
            current->remaining_time = current->remaining_time - quantum;
            sum = sum + quantum;
        }
        if (current->remaining_time == 0 && count == 1) {
            y--;
            printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", current->process_id, current->burst_time, sum - current->arrival_time, sum - current->arrival_time - current->burst_time);
            wt = wt + sum - current->arrival_time - current->burst_time;
            tat = tat + sum - current->arrival_time;
            count = 0;
        }
        if (current->next == head) {
            current = head;
        } else {
            current = current->next;
        }
    }
    avg_wt = wt * 1.0 / y;
    avg_tat = tat * 1.0 / y;
    printf("\n Average Turn Around Time: \t%f", avg_wt);
    printf("\n Average Waiting Time: \t%f", avg_tat);
}

int main() {
    int NOP, i, quantum;
    printf(" Total number of processes in the system: ");
    scanf("%d", &NOP);
    for (i = 0; i < NOP; i++) {
        printf("\n Enter the Arrival and Burst time of Process[%d]\n", i + 1);
        int arrival_time, burst_time;
        printf(" Arrival time is: \t");
        scanf("%d", &arrival_time);
        printf(" Burst time is: \t");
        scanf("%d", &burst_time);
        insertProcess(i + 1, arrival_time, burst_time);
    }
    printf("Enter the Time Quantum for the process: \t");
    scanf("%d", &quantum);
    roundRobin(quantum);
    getch();
    return 0;
}
