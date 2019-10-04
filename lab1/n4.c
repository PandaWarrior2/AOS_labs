/*
 * =====================================================================================
 *
 *       Filename:  n4.c
 *
 *    Description:  Lab 1, Number 4
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
        if((fp = open(argv[1], O_RDWR | O_CREAT, mode)) == -1) {
            perror("Open error");
            return 0;
        }
        else {
            printf("File %s opened! \n", argv[1]);
            strncpy(str, "0000000000\n", 11);
            for(int i = 0; i<10; i++){
                write(fp, str, 11);
            }
            printf("Составлена матрица 10х10, заполненная нулями:\n");
            if(lseek(fp, 0, SEEK_SET) == -1) {
                perror("Lseek error: ");
            }
            else{
                while(read(fp, str, 11) > 0) {
                    printf("%s", str);
                }
                printf("\nПроставим единицы в главной диагонали. Вжух...\n");
                lseek(fp, 0, SEEK_SET);
                for(int i = 0; i < 10; i++){
                    write(fp, "1", 1);
                    lseek(fp, 11, SEEK_CUR);
                }
                lseek(fp, 0, SEEK_SET);
                while(read(fp, str, 11) > 0) {
                    printf("%s", str);
                }

                printf("\nИдём с конца и проставляем 1 под главной диагональю1: \n");
                //int pos = lseek(fp, 10, SEEK_SET);
                //for(lseek(fp, -2, SEEK_END); lseek(fp, -2, SEEK_CUR) != -1; write(fp, "X", 1));
                //pos = write(fp, "2", 1);
                int pos = lseek(fp, -1L, SEEK_CUR);
                do{
                    //pos = lseek(fp, -1, SEEK_CUR);
                    //if(write(fp, '1', 1) == -1)
                    //    perror("");
                    write(fp, '1', 1);
                }while((pos = lseek(fp, -2, SEEK_CUR)) >= 70);

                int p = lseek(fp, 0, SEEK_SET);
                if(p == -1){
                    perror("");
                    return 0;
                }
                while(read(fp, str, 11) > 0) {
                    printf("%s", str);
                }
 
            }
            close(fp);

        }

    }
    return 1;

}

