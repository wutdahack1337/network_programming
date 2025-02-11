#include <stdio.h>
#include <string.h>
#include <netdb.h>

#define MAXLINE 105

int main(int argc, char* argv[]){
        struct addrinfo hints, *listp, *p;
        int             rc, flags;
        char            buf[MAXLINE];

        if (argc != 2){
                printf("[-] usage: %s <domain name>\n", argv[0]);
                return 1;
        }
        printf("[i] Starting...\n");

        /* Get a list of addrinfo records */
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;       // IPv4 only
        hints.ai_socktype = SOCK_STREAM; // Connections only

        rc = getaddrinfo(argv[1], NULL, &hints, &listp);
        if (rc != 0){
                printf("[-] getaddrinfo: something went wrong!!!\n");
                return 1;
        }
        printf("[+] getaddrinfo was successful\n");

        /* Walk the list and display each IP address */
        flags = NI_NUMERICHOST; // Display address string instead of domain name
        for (p = listp; p; p = (*p).ai_next){
                getnameinfo((*p).ai_addr, (*p).ai_addrlen, buf, MAXLINE, NULL, 0, flags);
                printf("==> %s\n", buf);
        }

        /* Clean up */
        printf("\n[i] cleaning up...\n");
        freeaddrinfo(listp);
        printf("[+] finished");
        return 0;
}
