#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#define PORTNUM 13000
#define HOSTLEN 256

#define oops(msg) \
    do { \
        perror(msg); \
        exit(1); \
    } while (0)

int main() {
    // step 1
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        oops("socket");
    }

    // step 2
    struct sockaddr_in saddr;

    bzero(&saddr, sizeof(saddr));

    char hostname[HOSTLEN];
    gethostname(hostname, HOSTLEN);
    struct hostent *hp = gethostbyname(hostname);

    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
        oops("bind");
    }

    // step 3

    // step 4

    // step 5

    // step 6

    return 0;
}