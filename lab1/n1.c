#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
int main(){
    printf("Start app...\n");
    int errCode;
    errCode = open("file", O_RDONLY, O_CREAT);

    printf("Return value: %d \n", errCode);
    printf("ERRNO: %d\n ", errno);
    if(errno != 0){
        perror("Произошла ошибка");
        printf("sys_errlist: %s\n", sys_errlist[errno]);
    }
   /*
   // sys errlist print
    for(int i = 0; i < sys_nerr; i++) {
        printf("sys_errlist[%d] = %s\n", i, sys_errlist[i]);
    }
    */

    return 0;
}
