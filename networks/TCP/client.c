//2 way client
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define SERVER_PORT 8080
#define MAX_LINE 256

int main(int argc, char *argv[]) {
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    int s;
    int len;

    if (argc == 2) {
        host = argv[1];
    } else {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }

    /* translate host name into peer's IP address */
    hp = gethostbyname(host);
    if (!hp) {
        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);

    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("simplex-talk: connect");
        close(s);
        exit(1);
    }
    printf("Connected to the server\n");

    /* main loop: get and send lines of text */
    while (1) {
        // Get client input and send to server
        printf("Client: ");
        fgets(buf, sizeof(buf), stdin);
        send(s, buf, strlen(buf), 0);

        // Receive server response
        memset(buf, 0, sizeof(buf));
        len = recv(s, buf, sizeof(buf), 0);
        if (len <= 0) {
            printf("Server disconnected\n");
            break;
        }
        printf("Server: %s", buf);
    }
    close(s);
    return 0;
}
