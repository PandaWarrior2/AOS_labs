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
    char buf[2];
    int code = 0;
    int lpos = 0;
    lpos = lseek(fp, -1, SEEK_END);
    printf("pos = %d\n", lpos);
    do {
        code = read(fp, buf, 2);
        printf("%s", buf);
        buf[1] = '\0';
        lpos = lseek(fp, -1, SEEK_CUR);
        printf("pos = %d\n", lpos);
    } while(lpos > 0);

    printf("\n");
    close(fp);
    return 0;
}
