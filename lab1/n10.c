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
    int fp = open(argv[1], O_RDONLY);
    char *buf;
    buf = malloc(1);
    long code = 0;
    int lpos = 0;
    //lseek(fp, 15, SEEK_SET);
    lpos = lseek(fp, 0, SEEK_END);
    do {
        code = read(fp, buf, 1);
        lpos = lseek(fp, 0, SEEK_CUR);
        lpos = lseek(fp, lpos-2, SEEK_SET);
        printf("%c", buf[0]);
    } while(lpos >= 0);

    printf("\n");
    close(fp);
    return 0;
}
