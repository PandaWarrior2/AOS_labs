/*
 * =====================================================================================
 *
 *       Filename:  n7.c
 *
 *    Description:  Lab 4, number 7
 *
 *        Version:  1.0
 *        Created:  21.10.2019 20:11:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, m19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "pcheck.h"
int main(int argc, char * argv[]){
    if(argc < 2){
        printf("Usage: %s filename", argv[0]);
        exit(1);
    }
    int fd;
    if((fd = open(argv[1], O_RDWR)) == -1){
        perror("open error");
        exit(1);
    }

    int pid;
    if((pid = fork()) == -1){
        perror("fork error");
        exit(1);
    }

    if(pid){
    
    }
    else{
    
    }
    return 0;
}
