#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>  // needed for `struct sockaddr_in`

#define PORT    8000
#define MAXLINE 1024


void error(char *msg) {
    perror(msg);
    exit(1);
}


int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        // printf("%d\n", sockfd);
        error("Error opening socket.");
    }

    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));

    // set server
    servaddr.sin_family    = AF_INET;   // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    return 0;
}
