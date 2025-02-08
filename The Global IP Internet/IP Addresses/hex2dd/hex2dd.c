#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* args[]){
  if (argc != 2){
    printf("./hex2dd <Network Bytes>\n");
    return 1;
  }

  unsigned int n;
  if (sscanf(args[1], "%x", n) == 0){
    printf("[!] Something wrong!!!");
    return 1;
  } 
  printf("[!] Got n = 0x%x\n", n);

  char* ipBuffer[105];
  // chuyen tu byte sang string
  ///
  
  return 0;
}
