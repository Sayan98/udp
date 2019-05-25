#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <strings.h>
#include <arpa/inet.h>      // needed for `struct sockaddr_in`
#include <netinet/in.h>     // needed for `struct sockaddr_in`


#define PORT    8000
#define MAXLINE 1024


void error(char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    char buffer[MAXLINE]; 
    char *hello = "Hi, I am the server";

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        // printf("%d\n", sockfd);
        error("Error opening socket.");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));

    // set server
    servaddr.sin_family    = AF_INET;   // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(-1);
    }

    int len, n;

    for(;;) {
        n = recvfrom(sockfd,
                     (char *) buffer, 
                     MAXLINE, 
                     MSG_WAITALL,
                     (struct sockaddr*) &cliaddr,
                     &len);

        buffer[n] = '\0';
        printf("Client %d sent: %s", cliaddr.sin_addr.s_addr, buffer);

        sendto(sockfd,
               (const char*) &hello,
               strlen(hello),
               MSG_DONTWAIT, 
               (const struct sockaddr*) &cliaddr, 
               len);
        printf("Hello message sent from server.");
    }

    return 0;
}
