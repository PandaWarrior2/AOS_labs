/*
 * =====================================================================================
 *
 *       Filename:  pcheck.c
 *
 *    Description: Systemcall checker
 *
 *        Version:  1.0
 *        Created:  21.10.2019 11:27:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "pcheck.h"
int pcheck(int func, char * message){
    if(func == -1) {
        perror(message);
        printf("%d\n", errno);
        exit(1);
    }
    else{
        return func;
    }
}
