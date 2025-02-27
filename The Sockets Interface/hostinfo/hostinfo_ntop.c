#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 105

int main(int argc, char *argv[]){
        struct addrinfo hints, *listp, *p;
        struct sockaddr_in *sockp;
        char buf[MAXLINE];

        if (argc != 2){
                printf("[-] usage: %s <domain name>\n", argv[0]);
                return 1;
        }

        // Get a list of addrinfo records
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family   = AF_INET;     // IPv4 only
        hints.ai_socktype = SOCK_STREAM; // Connections only
        if (getaddrinfo(argv[1], NULL, &hints, &listp) != 0){
                printf("[-] getaddrinfo: something went wrong!!!");
                return 1;
        }
        printf("[+] getaddrinfo was successful\n");

        // Walk the list and display each associated IP address
        for (p = listp; p != NULL; p = (*p).ai_next){
                sockp = (struct sockaddr_in *)(*p).ai_addr;
                inet_ntop(AF_INET, &((*sockp).sin_addr), buf, MAXLINE);
                printf("===> %s\n", buf);
        }

        // Clean up
        printf("[!] cleaning up...\n");
        freeaddrinfo(listp);

        printf("[+] done, exiting...");

        return 0;
}
