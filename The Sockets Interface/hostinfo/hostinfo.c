#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAXLINE 105

int main(int argc, char* argv[]){
        struct addrinfo *p, *listp, hints;
        char            buf[MAXLINE];
        int             rc, flags;

        if (argc != 2){
                printf("[-] usage: %s <domain name>\n", argv[0]);
                return 1;
        }

        /* Get a list of addinfo records */
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family   = AF_INET;     /* IPv4 only        */
        hints.ai_socktype = SOCK_STREAM; /* Connections only */

        if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0){
                printf("[-] something went wrong!!!\n");
                return 1;
        }
        printf("[+] finished getaddrinfo()\n");


        /* Walk the list and display each IP address */
        flags = NI_NUMERICHOST; /* Display address string instead of domain name */
        for (p = listp; p; p = p->ai_next){
                getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
                printf("[+] ===> %s\n", buf);
        }

        /* Clean up */
        freeaddrinfo(listp);

        return 0;
}
