/*
 * =====================================================================================
 *
 *       Filename:  n2.c
 *
 *    Description:  Lab #2, number 2.
 *
 *        Version:  1.0
 *        Created:  05.10.2019 23:15:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, m19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    int pid = fork();

    if(pid == -1){
        perror("[fork]");
    }

    if(pid){
        printf("Это сообщение выведено из родительского процесса\n");
    }
    else{
        printf("Это сообщение выведено из дочернего процесса\n");
    }
    return 0;
}

