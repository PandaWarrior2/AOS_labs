/*
 * =====================================================================================
 *
 *       Filename:  n8.c
 *
 *    Description:  Lab 1 number 8
 *
 *        Version:  1.0
 *        Created:  29.09.2019 17:33:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, m19-512
 *   Organization:  mephi
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int copy(int, int);
int copy_new();

int main(int argc, char * argv[]){
   /*   printf("Number 8. Copying files...\n");
    int fileFrom = 0;
    if(argc >= 2){
        fileFrom = open(argv[1], O_RDONLY);
    }
    if(fileFrom == -1){
        perror("[FROM] Error");
        return 0;
    }
    int fileTo = 0;
    if(argc >= 3){
        fileTo = open(argv[2], O_WRONLY | O_CREAT,0755);
    }
    else {
        fileTo = 1; // STDOUT
        int code;
        char buf[255];
        do{
            if(code != -1)
                code = scanf("%s", buf);
        } while(code != -1);
    }
    if(fileTo == -1) {
        perror("[TO] Error");
        return 0;
    } */

    //copy(fileFrom, fileTo);
    int fileFrom, fileTo;
    if(argv[2]){
        close(1);
        fileTo = open(argv[2], O_WRONLY | O_CREAT, 0755);
        dup2(fileTo, 1);

    }
    if(argv[1]){
        close(0);
        fileFrom = open(argv[1], O_RDONLY);
        dup2(fileFrom, 0);
    }
    copy_new();
    close(fileFrom);
    close(fileTo);

    return 1;
}
int copy_new(){
    int c;
    char buf[255];
    do{
        c = read(0, buf, 255);
        write(1, buf, c);
    } while (c == 255);
    return 0;
}
int copy(int from, int to){
    int c;
    char buf[255];
    do{
        c = read(from, buf, 255);
        write(to, buf, c);
    } while(c == 255);
    return 0;
}
