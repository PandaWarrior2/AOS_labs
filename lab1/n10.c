/*
 * =====================================================================================
 *
 *       Filename:  n10.c
 *
 *    Description:  Number 10, Lab 1
 *
 *        Version:  1.0
 *        Created:  29.09.2019 20:21:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  Mephi
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char * argv[]){
    int fp;
    if((fp = open(argv[1], O_RDONLY)) == -1){
        perror("");
    }
    else{
        char buf;
        long code = 0;
        lseek(fp, 0, SEEK_END);
        do{
            read(fp, &buf, 1);
            write(1, &buf, 1);
        } while(lseek(fp, (long)-2, SEEK_CUR) >= 0);

    printf("\n");
    close(fp);
    }
    return 0;
}
