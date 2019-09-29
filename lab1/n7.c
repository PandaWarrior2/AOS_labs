/*
 * =====================================================================================
 *
 *       Filename:  n7.c
 *
 *    Description:  Lab 1, number 7.
 *
 *        Version:  1.0
 *        Created:  29.09.2019 16:22:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin
 *   Organization:  m19-512
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
        printf("Enter: %s <filename>\n", argv[0]);
    }
    else {
        struct stat buf;
        int code = stat(argv[1], &buf);
        char str_t[100];

        printf("Информация о файле %s\n", argv[1]);
        printf("Устройство: %d\n", buf.st_dev);
        printf("inode: %d\n", buf.st_ino);
        printf("Режим доступа: %d\n", buf.st_mode);
        printf("Кол-во жестких ссылок: %d\n", buf.st_nlink);
        printf("Идентификатор пользователя-владельца: %d\n", buf.st_uid);
        printf("Идентификатор группы-владельца: %d\n", buf.st_gid);
        printf("Тип устройства: %d\n", buf.st_rdev);
        printf("Общий размер в байтах: %d\n", buf.st_size);
        printf("Размер блока ввода-вывода: %d\n", buf.st_blksize);
        printf("Количество выделенных блоков: %d\n", buf.st_blocks);
        strftime (str_t, 100, "%d.%m.%y %X", localtime(&buf.st_atime));
        printf("Время последнего доступа: %s\n", str_t);
        strftime (str_t, 100, "%d.%m.%y %X", localtime(&buf.st_mtime));
        printf("Время последней модификации: %s\n", str_t);
        strftime (str_t, 100, "%d.%m.%y %X", localtime(&buf.st_ctime));
        printf("Время последнего изменения: %s\n", str_t);
    }
    return 0;
}

