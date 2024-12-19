#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define PORT 8080

void xor_operation(char *dividend, char *divisor, int length) {
    for (int i = 0; i < length; i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

int crc_check(char *received_message, char *polynomial) {
    int message_len = strlen(received_message);
    int poly_len = strlen(polynomial);
    char temp[BUFFER_SIZE];

    // Copy the received message to a temporary buffer
    strcpy(temp, received_message);

    // Perform long division (bitwise XOR operation)
    for (int i = 0; i <= message_len - poly_len; i++) {
        if (temp[i] == '1') {
            xor_operation(temp + i, polynomial, poly_len);
        }
    }

    // Check if the remainder (CRC) is zero
    for (int i = message_len - poly_len + 1; i < message_len; i++) {
        if (temp[i] == '1') {
            return 1; // Error detected
        }
    }

    return 0; // No error
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char received_message[BUFFER_SIZE];
    char received_polynomial[BUFFER_SIZE];
    socklen_t len;
    int message_len;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);

    message_len = recvfrom(sockfd, received_message, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    received_message[message_len] = '\0'; 

    recvfrom(sockfd, received_polynomial, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    received_polynomial[strlen(received_polynomial)] = '\0';

    printf("Received message (including CRC): %s\n", received_message);

    if (crc_check(received_message, received_polynomial)) {
        printf("Error detected in the received message.\n");
    } else {
        printf("Received message is error-free: %.*s\n", (int)(strlen(received_message) - strlen(received_polynomial) + 1), received_message);
    }

    close(sockfd);
    return 0;
}