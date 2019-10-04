/*
 * =====================================================================================
 *
 *       Filename:  n2n.c
 *
 *    Description:  Lab 1, Number 2
 *
 *        Version:  1.0
 *        Created:  03.10.2019 10:09:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, m19-512
 *   Organization:  MEphI
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

int main(int argc, char * argv[]) {
    if(argc == 1){
        printf("No arguments!\nEnter: %s <filename> <permissions>\n", argv[0]);
    }
    else if(argc == 2){
        printf("No permission options!\n");
    }
    else {
        printf("Creating file %s with permissions %s\n", argv[1], argv[2]);
        int fp;
        int mode = strtol(argv[2], 0, 8);
        int code;
        char str[255];
        int s_code;
        if((fp = open(argv[1], O_WRONLY | O_CREAT, mode)) == -1) {
            perror("[1] Open error");
            return 0;
        }
        else {
            printf("[1] File %s opened! \n", argv[1]);
                        do {
                if((code = scanf("%s", str)) != -1){
                    s_code = write(fp, str, strlen(str));
                    printf("[1] [SYSCALL] write = %d\n", s_code);
                    write(fp, '\n', 1);
                }
                else {
                    printf("[1] EOF\n");
                }
            } while(code != -1);
            close(fp);

        }

        if((fp = open(argv[1], O_RDONLY)) == -1) {
            perror("[2] Open error");
            return 0;
        }
        else {
            printf("[2] File opened! Reading data from file...\n");
            while(read(fp, str, 255) > 0){
                printf("[2] [DATA] str = %s\n", str);
            }
            close(fp);
        }
        if((fp = open(argv[1], O_RDWR)) == -1) {
            perror("[3] Open error");
            return 0;
        }
        else{
            printf("[3] File %s opened!\n", argv[1]);
            close(fp);
        }
    }
    return 1;

}
