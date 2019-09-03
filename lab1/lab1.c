#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
void main(){
    printf("Start app...\n");
    int errCode;
    errCode = open("file", O_RDONLY, O_CREAT);

    printf("Return value: %d \n", errCode);
    printf("ERRNO: %d\n ", errno);
}
