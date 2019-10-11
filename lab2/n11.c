/*
 * =====================================================================================
 *
 *       Filename:  n11.c
 *
 *    Description:  Lab 2, Numberb 11
 *
 *        Version:  1.0
 *        Created:  10.10.2019 19:03:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char * argv[], char * argp[]){
    if(argc < 2){
        printf("Usage: %s filename \n", argv[0]);
    }
    else{
        int code = fork();
        if(code == -1){
            perror("fork error");
            exit(1);
        }
        if(code){
            printf("[P] Parent PID = %d\n", getpid());
            printf("[P] Child process created!\n");

            char * args = (char*) malloc(strlen(*(argv+1)));
            int i = 0;
            for(i=1; *(argv+i); i++){
                args = (char*)realloc(args, strlen(args)+strlen(*(argv+i)));
                strcat(args, *(argv+i));
                strcat(args, " ");
            }
            if(wait(&i) == -1){
                perror("wait error");
            }
            else{
                printf("[P] Дочерний процесс завершился! code = %d\n", i);
            }
            printf("[P] Запускаем процесс командой system(%s)...\n", args);
            system(args);
        }
        else{
            printf("[C] Child PID = %d\n", getpid());
            execve(argv[1], (argv+1), argp);
            perror("[C] exec error");
        }
    }
}

