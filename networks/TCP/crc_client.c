#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define PORT 8080

// Function to perform XOR operation between two strings
void xor_operation(char *dividend, char *divisor, int length) {
    for (int i = 0; i < length; i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

// Function to perform CRC encoding using long division
void crc_encode(char *message, char *polynomial, char *encoded_message) {
    int message_len = strlen(message);
    int poly_len = strlen(polynomial);
    char temp_message[BUFFER_SIZE];

    // Copy the original message and append zeros equal to (polynomial length - 1)
    strcpy(temp_message, message);
    for (int i = 0; i < poly_len - 1; i++) {
        strcat(temp_message, "0");
    }

    // Perform long division (bitwise XOR operation)
    for (int i = 0; i <= strlen(temp_message) - poly_len; i++) {
        if (temp_message[i] == '1') {
            xor_operation(temp_message + i, polynomial, poly_len);
        }
    }

    // Copy the remainder (CRC) to the end of the original message
    strcpy(encoded_message, message);
    strcat(encoded_message, temp_message + message_len); // Append only the remainder part

    // Print the encoded message including the remainder
    printf("Encoded message (original message + CRC remainder): %s\n", encoded_message);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char message[BUFFER_SIZE];
    char polynomial[BUFFER_SIZE];
    char encoded_message[BUFFER_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Input message
    printf("Enter the message to send (in binary): ");
    if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }
    message[strcspn(message, "\n")] = 0; // Remove trailing newline

    // Input polynomial
    printf("Enter the generating polynomial (in binary): ");
    if (fgets(polynomial, BUFFER_SIZE, stdin) == NULL) {
        perror("Error reading polynomial");
        exit(EXIT_FAILURE);
    }
    polynomial[strcspn(polynomial, "\n")] = 0; // Remove trailing newline

    // Encode the message with CRC
    crc_encode(message, polynomial, encoded_message);

    // Send the encoded message and polynomial
    sendto(sockfd, encoded_message, strlen(encoded_message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    sendto(sockfd, polynomial, strlen(polynomial), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Message sent: %s\n", encoded_message);

    close(sockfd);
    return 0;
}