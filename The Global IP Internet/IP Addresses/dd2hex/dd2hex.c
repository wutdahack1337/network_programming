#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
        struct in_addr inaddr;   /* Address in network byte order */
        uint16_t       addr;     /* Address in host byte order */

        if (argc != 2){
                printf("[-] usage: %s <network byte order>\n", argv[0]);
                return 1;
        }

        if (inet_pton(AF_INET, argv[1], &inaddr) <= 0){
                printf("[-] something went wrong!!!\n");
                return 1;
        }

        addr = ntohs(inaddr.s_addr);
        printf("0x%x\n", addr);

        return 0;
}
