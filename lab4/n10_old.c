/*
 * =====================================================================================
 *
 *       Filename:  n10.c
 *
 *    Description: Lab 4, number 10
 *
 *        Version:  1.0
 *        Created:  24.10.2019 15:06:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, m19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
int main(int argc, char * argv[]){
    int pfd[2];
    if(pipe(pfd) == -1){
        perror("Pipe error");
    }
    int pid;
    if((pid = fork()) == -1){
        perror("fork error");
    }
    char str[100];
    struct termios new_config, old_config;
    if(pid){
        wait(NULL);
        printf("[P] fork ok! %d \n", pid);
        if(tcgetattr(0, &old_config) == -1)
        {
            perror("tcgetaddr error");
        }
        new_config = old_config;
        new_config.c_iflag |= ~(ECHO);
       // new_config.c_iflag |= ISIG;
        //new_config.c_iflag &= ~ICRNL;
        new_config.c_cc[VMIN] = 1;
        //new_config.c_cc[VTIME] = 0;
        if(tcsetattr (STDIN_FILENO, TCSAFLUSH, &new_config) == -1){
            perror("tcsetattr error");
        }

        char *c;
        while(1){
            //read(0, &c, 1);
            //scanf("%s",str);
            //write(pfd[1], str, strlen(str));
        }
    }
    else{
        char *c;
        int r;
        close(pfd[1]);
        printf("[C] Child process started...\n");
       // while(1) {
           /*  if((r = read(0, &c, 1)) == -1){
                perror("[C] read error");
            }
            else if(r){
                write(1, &c, 1);
                write(1,".",1);
            }*/
       /*      read(0, &c, 1);
            write(1, &c, 1);
            write(1, ".", 1);
        }*/
    }
    return 0;
}
