/*
 * =====================================================================================
 *
 *       Filename:  prog10.c
 *
 *    Description:  Subprogram for lab 2 (10-11 numbers)
 *
 *        Version:  1.0
 *        Created:  10.10.2019 20:26:42
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
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char * argv[], char * argp[]){
    printf("[SUB] Program started!\n");
    int i;
    printf("\n[SUB] Arguments:\n");
    for(i = 0; i < argc; i++){
        printf("[SUB] Argument %d = %s\n", i, *(argv+i));
    }
    printf("\n[SUB] Environment:\n");
    for(; *argp; argp++){
        printf("[SUB] %s\n", *argp);
    }
    printf("[SUB] Exit from program!\n");

}
