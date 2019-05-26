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
    struct sockaddr_in servaddr;

    char buffer[MAXLINE]; 
    char *hello = "Hello, I am the client";

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    unsigned int n, len; 

    sendto(sockfd,
            (const char *)hello, 
            strlen(hello),
            MSG_CONFIRM, 
            (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    printf("Hello message sent from client.\n"); 


    n = recvfrom(sockfd, 
                 (char *)buffer, 
                 MAXLINE, 
                 MSG_WAITALL,
                 (struct sockaddr *) &servaddr, 
                 &len); 
    buffer[n] = '\0'; 
    
    printf("Server sent: %s\n", buffer); 
    close(sockfd); 

    return 0;
}
