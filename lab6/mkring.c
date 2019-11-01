/*
 * =====================================================================================
 *
 *       Filename:  mkring.c
 *
 *    Description:  Lab 6, prog for make rings;
 *
 *        Version:  1.0
 *        Created:  01.11.2019 11:41:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
typedef struct Proc {
    int pid;
    struct Proc *next;
} Proc;
void push(Proc **head, int pid){
    Proc * p = (Proc*) malloc(sizeof(Proc));
    p->pid = pid;
    p->next = (*head);
    *(head) = p;
}
int main(int argc, char * argv[]){
    Proc *head = NULL;
    int pid;
    for(int i=0;i<10;i++){
        if((pid = fork()) == -1){
            perror("fork");
        }
        else if(pid == 0){
            printf("[C] Created! pid = %d\n", getpid());
        }
        else{
            wait(NULL);
            push(&head, pid);
            printf("[P] pushed! %d\n", head->pid);
        }
    }

    Proc *last, *i;
    for(last = head;last->next;last = last->next);
    last->next = head;

    return 0;
}
