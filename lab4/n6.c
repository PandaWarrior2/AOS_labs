/*
 * =====================================================================================
 *
 *       Filename:  n6.c
 *
 *    Description:  Lab 4, Number 6 - Tx
 *
 *        Version:  1.0
 *        Created:  21.10.2019 11:20:26
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
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "pcheck.h"
struct packet{
    int id;
    int value;
};

int main(int argc, char * argv[], char * argp[]){
    unlink("channel");
    pcheck(mknod("channel",  S_IFIFO | 0755, 0), "mknod error");
    int wfd = pcheck(open("channel",O_WRONLY), "open error");
    struct packet tx;
    int i = 0;
    int n;
    printf("[TX] Client started...\n");
    while(i < 1500){
        tx.id = i++;
        tx.value = rand() % 10000;
        n = pcheck(write(wfd, &tx, sizeof(struct packet)), "write error");
        if(n < sizeof(struct packet)){
            printf("[TX] Ошибка при отправке пакета! (%d bytes)\n", n);
        }
        else{
            printf("[TX] Пакет отправлен! (%d ; %d) (%d bytes)\n", tx.id, tx.value, n);
        }
        sleep(1);
    }
//    pcheck(unlink("channel"), "unlink error");
}
