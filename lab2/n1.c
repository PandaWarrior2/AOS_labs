/*
 * =====================================================================================
 *
 *       Filename:  n1.c
 *
 *    Description:  Lab #2, number 1.
 *
 *        Version:  1.0
 *        Created:  05.10.2019 23:01:48
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

int main(int argc, char * argv[], char * argp[]){
    if(argc < 3) {
        printf("Enter: %s <name> <value>\n", argv[0]);
    }
    else{
        int ret;
        char *env;
        if((ret = setenv(argv[1], argv[2], 1)) == -1){
            perror("SETENV error");
        }
        else{
            printf("Переменная окружения добавлена! setenv = %d\n", ret);
            env = getenv(argv[1]);
            printf("getenv(%s) = %s\n", argv[1], env);
        }
    }
    return 0;
}
