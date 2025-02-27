#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int open_clientfd(char *hostname, char *port){
        struct addrinfo hints, *listp, *p;
        int clientfd;

        // Get a list of potential server addresses
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_socktype = SOCK_STREAM;    // Open a connection
        hints.ai_flags    = AI_NUMERICSERV; // ... using a numeric port arg.
        hints.ai_flags   |= AI_ADDRCONFIG;  // Recommended for connections
        getaddrinfo(hostname, port, &hints, &listp);

        // Walk the list for one that we can successfully connect to
        for (p = listp; p != NULL; p = (*p).ai_next){
                // Create a socket descriptor
                if ((clientfd = socket((*p).ai_family, (*p).ai_socktype, (*p).ai_protocol)) < 0){
                        continue;
                }

                // Connect to the server
                if (connect(clientfd, (*p).ai_addr, (*p).ai_addrlen) != -1){
                        break; // Success
                }
                close(clientfd); // Connect failed, try another
        }

        // Clean up
        freeaddrinfo(listp);
        if (!p){ // All connects failed
                return -1;
        } else { // The last connect succeeded
                return clientfd;
        }
}

int main(){

        return 0;
}
