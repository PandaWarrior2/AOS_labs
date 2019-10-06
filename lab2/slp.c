/*
 * =====================================================================================
 *
 *       Filename:  slp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06.10.2019 11:34:19
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
#include <signal.h>

int main(int argc, char * argv[]){
    printf("[SLP] Started!\n");
    if(argc < 2){
        printf("Usage: %s time(sec)\n", argv[0]);
    }
    else {
        int s_time = atoi(argv[1]);
        int i;
        for(i = 0; i < s_time; i++){
            printf("[SLP] %d/%d; PID = %d; PPID = %d\n", i, s_time, getpid(), getppid());
            if(i == 3) {
                kill(getppid(), 9);
            }
            sleep(1);
        }
    }
        printf("[SLP] Done!\n");
    return 0;
}

