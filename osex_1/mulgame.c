#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>

// Shared variables
int *p;
sem_t *john_turn, *michael_turn;

int main() {
    // Allocate shared memory for p
    p = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Allocate semaphores for synchronization
    john_turn = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    michael_turn = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Initialize semaphores
    sem_init(john_turn, 1, 1);  // Semaphore for John's turn
    sem_init(michael_turn, 1, 0);  // Semaphore for Michael's turn

    // Initialize p to 1
    *p = 1;

    // Fork the process
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process (Michael)
        while (*p < 100) {  // Adjust the limit (N) as needed
            sem_wait(michael_turn);

            // Michael multiplies the number
            int factor = rand() % 8 + 2;  // Random number between 2 and 9
            *p *= factor;

            printf("Michael: Multiplying by %d, Result: %d\n", factor, *p);

            sem_post(john_turn);
        }
    } else {
        // Parent process (John)
        while (*p < 100) {  // Adjust the limit (N) as needed
            // John multiplies the number
            sem_wait(john_turn);

            int factor = rand() % 8 + 2;  // Random number between 2 and 9
            *p *= factor;

            printf("John: Multiplying by %d, Result: %d\n", factor, *p);

            sem_post(michael_turn);
        }

        // Wait for the child process to finish
        wait(NULL);

        // Cleanup
        sem_destroy(john_turn);
        sem_destroy(michael_turn);
        munmap(p, sizeof(int));
        munmap(john_turn, sizeof(sem_t));
        munmap(michael_turn, sizeof(sem_t));
    }

    return 0;}