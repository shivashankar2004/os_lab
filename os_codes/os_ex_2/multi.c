#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int p = 1; // Shared variable
int n;    // Shared variable
sem_t john, michael;
pthread_t michael_thread, john_thread;

void* michael_plays(void* arg)
{
    while (p < n)
    {
        sem_wait(&john); // Wait for John's to finish
        if (p < n)
        {
            int multiplier = rand() % (9 - 2 + 1) + 2;
            p *= multiplier;
            printf("Michael's turn: %d\n", p);

            if (p >= n)
            {
                printf("Michael wins!\n");
                sem_post(&michael); // Signal John to exit
                break;
            }
        }
        sem_post(&michael); // Signal John to take his turn
    }
    return NULL;
}

void* john_plays(void* arg)
{
    pthread_create(&michael_thread, NULL, michael_plays, NULL);

    while (p < n)
    {
        sem_wait(&michael); // Wait for Michael's turn
        if (p < n)
        {
            int multiplier = rand() % (9 - 2 + 1) + 2;
            p *= multiplier;
            printf("John's turn: %d\n", p);

            if (p >= n)
            {
                printf("John wins!\n");
                sem_post(&john); // Signal Michael to exit
                break;
            }
        }
        sem_post(&john); // Signal Michael to take his turn
    }
    pthread_join(michael_thread, NULL);
    return NULL;
}

int main()
{
    printf("Enter the value of N: ");
    int x = scanf("%d", &n);

    srand(time(NULL)); 

    sem_init(&john, 0, 0);
    sem_init(&michael, 0, 1); 

    pthread_create(&john_thread, NULL, john_plays, NULL);
    pthread_join(john_thread, NULL);

    sem_destroy(&john);
    sem_destroy(&michael);

    return 0;
}