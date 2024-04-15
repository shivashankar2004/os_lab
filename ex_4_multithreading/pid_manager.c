#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_PID 300
#define MAX_PID 5000
#define BITMAP_SIZE (MAX_PID - MIN_PID + 1)

// Global bitmap to represent availability of process identifiers
bool bitmap[BITMAP_SIZE] = { false };

// Function prototypes
int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);

int allocate_map() {
    // Initialize the bitmap to indicate all PIDs are available
    for (int i = 0; i < BITMAP_SIZE; i++) {
        bitmap[i] = false;
    }
    return 1; // Successfully initialized the bitmap
}

int allocate_pid() {
    // Find the first available PID in the bitmap and mark it as used
    for (int i = 0; i < BITMAP_SIZE; i++) {
        if (!bitmap[i]) {
            bitmap[i] = true;
            return MIN_PID + i; // Return the allocated PID
        }
    }
    return -1; // Unable to allocate a PID (all PIDs are in use)
}

void release_pid(int pid) {
    if (pid < MIN_PID || pid > MAX_PID) {
        fprintf(stderr, "Invalid PID\n");
        return;
    }

    // Release the PID by marking it as available in the bitmap
    bitmap[pid - MIN_PID] = false;
}

int main() {
    // Test the PID manager
    int status = allocate_map();
    if (status == -1) {
        printf("Failed to initialize PID manager\n");
        return EXIT_FAILURE;
    }

    // Allocate some PIDs
    int pid1 = allocate_pid();
    int pid2 = allocate_pid();
    int pid3 = allocate_pid();

    if (pid1 != -1 && pid2 != -1 && pid3 != -1) {
        printf("Allocated PIDs: %d, %d, %d\n", pid1, pid2, pid3);
    } else {
        printf("Failed to allocate PIDs\n");
        return EXIT_FAILURE;
    }

    // Release PID2 and allocate another PID
    release_pid(pid2);
    int pid4 = allocate_pid();

    if (pid4 != -1) {
        printf("Released PID %d and allocated new PID %d\n", pid2, pid4);
    } else {
        printf("Failed to allocate new PID\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
