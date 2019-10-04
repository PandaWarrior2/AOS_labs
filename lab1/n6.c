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
        char str[11];
        int s_code;
        if((fp = open(argv[1], O_RDWR | O_CREAT, mode)) == -1) {
            perror("Open error");
            return 0;
        }
        else {
            int i;
            printf("File %s opened! \n", argv[1]);
            strncpy(str, "0000000000", 10);
            for(i = 0; i<10; i++){
                write(fp, str, 10);
                lseek(fp, 10, SEEK_CUR);
            }
            printf("6. Работа с разреженным файлом\n");
            printf("Составлена матрица 10х10, заполненная нулями:\n");
            if(lseek(fp, 0, SEEK_SET) == -1) {
                perror("Lseek error: ");
            }
            else{
                  while(read(fp, str, 10) > 0) {
                    printf("%s\n", str);
                    lseek(fp, 10, SEEK_CUR);
                }
                printf("\nПроставим единицы в главной диагонали. Вжух...\n");
                lseek(fp, 0, SEEK_SET);
                for(i = 0; i < 10; i++){
                    write(fp, "1", 1);
                    lseek(fp, 20, SEEK_CUR);
                }
                lseek(fp, 0, SEEK_SET);
                while(read(fp, str, 10) > 0) {
                    printf("%s\n", str);
                    lseek(fp, 10, SEEK_CUR);
                }

                printf("\nИдём с конца и проставляем 1 под главной диагональю. Вжух...\n");
                int pos = lseek(fp, (long)-1, SEEK_END);
                int s_pos = pos;
                do{
                    if((s_pos/10) >= (s_pos % 10)){
                        write(fp, "1", 1);
                    }
                    if((pos % 10) == 9) {
                        lseek(fp, (long)-10, SEEK_CUR);
                    }
                    else {
                        s_pos -= pos;
                    }
                }while((pos = lseek(fp, (long)-2, SEEK_CUR)) >= 0);

                lseek(fp, 0, SEEK_SET);
                while((pos = read(fp, str, 10)) > 0){
                    printf("%s\n", str);
                    lseek(fp, 10, SEEK_CUR);
                }
            }
            close(fp);

        }

    }
    return 1;

}

