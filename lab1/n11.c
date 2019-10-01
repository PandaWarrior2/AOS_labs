/*
 * =====================================================================================
 *
 *       Filename:  n11.c
 *
 *    Description: Lab 1, number 11
 *
 *        Version:  1.0
 *        Created:  01.10.2019 13:41:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  MEPhi
 *
 * =====================================================================================
 */
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
int main(int argc, char * argv[]){
    if(argc == 1){
        printf("Enter: %s <filename 1> <filename 2> ... <filename n>\n", argv[0]);
        return 0;
    }
    else{
        printf("Program for number 11 Lab 1 \n");
        struct stat buf;
        int code = 0;
        int max_idx = 0;
        int max_size = -1;
        for(int i = 1; i < argc; i++){
            //printf("%s\n", argv[i]);
            code = stat(argv[i], &buf);
            if(!code){
                printf("Файл %s прочитан. Общий размер в байтах: %d\n", argv[i], buf.st_size);
                if(buf.st_size > max_size){
                    max_idx = i;
                    max_size = buf.st_size;
                }
            }
            else {
                printf("Ошибка при открытии файла %s: %s\n", argv[i], strerror( errno ));
            }
        }
        printf("Самый длинный файл: %s\n ", argv[max_idx]);
    }
    return 1;
}
