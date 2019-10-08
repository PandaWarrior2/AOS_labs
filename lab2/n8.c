/*
 * =====================================================================================
 *
 *       Filename:  n8.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08.10.2019 09:04:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
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
int main(int argc, char * argv[]){
    if(argc == 1){
        printf("Usage: %s filename", argv[0]);
    }
    else {
        int fp;
        if((fp = open(argv[1], O_RDONLY)) == -1){
            perror("");
            exit(1);
        }
        else{
            int pid;
            if((pid = fork()) == -1){
                perror("");
                exit(2);
            }
            else if (pid){
                printf("[P] PID = %d\n", pid);
                int fd_p;
                if((fd_p = open("out_parent", O_WRONLY | O_CREAT)) == 1){
                    perror("");
                    exit(3);
                }
                else {
                    char buf[255];

                }
            }
            else {
                printf("[C] PID = %d\n", pid);
                int fd_c;
                if((fd_c = open("out_parent", O_WRONLY | O_CREAT)) == 1){
                    perror("");
                    exit(4);
                }
                else {
                
                }

            }
            close(fp);
        }
    }
    return 0;
}
