#include <stdio.h>
#include <arpa/inet.h>

#define MAXBUF 105

int main(int argc, char* argv[]){
        struct in_addr inaddr;      /* Address in network byte order    */
        uint16_t       addr;        /* Address in host byte order       */
        char           buf[MAXBUF]; /* Buffer for dotted-decimal string */

        if (argc != 2){
                printf("[-] usage: %s <hex number>\n", argv[0]);
                return 1;
        }

        sscanf(argv[1], "%x", &addr);
        printf("[!] Host: 0x%x\n", addr);

        inaddr.s_addr = ntohs(addr);
        // Network is BIG-ENDIAN byte
        printf("[!] Network: 0x%x\n", inaddr.s_addr);

        if (!inet_ntop(AF_INET, &inaddr, buf, MAXBUF)){
                printf("[!] Something went wrong\n");
                return 1;
        }
        printf("[+] ===> %s\n", buf);

        return 0;
}
