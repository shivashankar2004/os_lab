#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>

// Function prototype
void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct timeval start, end;

    // Shared memory creation
    int shm_fd = shm_open("/time_shm", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
        error("shm_open");

    if (ftruncate(shm_fd, sizeof(struct timeval)) == -1)
        error("ftruncate");

    struct timeval *start_time_ptr = mmap(NULL, sizeof(struct timeval), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (start_time_ptr == MAP_FAILED)
        error("mmap");

    pid_t pid = fork();

    if (pid == -1) {
        error("fork");
    } else if (pid == 0) { // Child process
        gettimeofday(&start, NULL);
        *start_time_ptr = start; // Write start time to shared memory
        execvp(argv[1], argv + 1);
        error("execvp"); // If execvp fails
    } else { // Parent process
        wait(NULL); // Wait for child process to finish
        gettimeofday(&end, NULL);
        double elapsed_time = (end.tv_sec - start_time_ptr->tv_sec) + (end.tv_usec - start_time_ptr->tv_usec) / 1000000.0;
        printf("Elapsed time: %.5f seconds\n", elapsed_time);
    }

    // Cleanup
    munmap(start_time_ptr, sizeof(struct timeval));
    shm_unlink("/time_shm");

    return 0;
}

//compiled by
// gcc time_pipe.c -o a.out -lrt
// //./a.out date
//o/p..
// Mon Apr 15 18:50:16 IST 2024
// Elapsed time: 0.03569 seconds
//(ftruncate)
//  It is typically used to change the size of a regular file or shared memory object referenced by a file descriptor
//  fd: The file descriptor of the file or shared memory object to be truncated.
// length: The new size to which the file should be truncated.


