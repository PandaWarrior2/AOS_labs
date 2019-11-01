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
typedef struct msg{
    long mtype;
    int value;
} msg;

void push(Proc **head, int pid){
    Proc * p = (Proc*) malloc(sizeof(Proc));
    p->pid = pid;
    p->next = (*head);
    *(head) = p;
}
int get_next(Proc *head, int pid){
    for(Proc *i=head; i->next; i = i->next){
        if(pid == i->pid){
            return i->pid;
        }
    }
    return -1;
}
int main(int argc, char * argv[]){
    Proc *head = NULL;
    int pid, qd, cqd;
    key_t ckey;
    for(int i=0;i<10;i++){
        if((pid = fork()) == -1){
            perror("fork");
        }
        else if(pid == 0){
            printf("[C] Created! pid = %d\n", getpid());
            msg *rc;
            if((ckey = ftok("queue", 1)) == -1){
                perror("ftok");
                exit(EXIT_FAILURE);
            }
            if((cqd = msgget(ckey, IPC_CREAT | 0666)) == -1){
                perror("msgget");
                exit(EXIT_FAILURE);
            }
            if(msgrcv(cqd, rc, getpid(), 0,0) == -1){
                perror("[C] msgrcv");
            }
            else{
                printf("[C %d] Получено сообщение %d\n", getpid(), rc->value);
            }
            while(1);
        }
        else{
            push(&head, pid);
            printf("[P] pushed! %d\n", head->pid);
        }
    }

    Proc *last, *i;
    for(last = head;last->next;last = last->next);
    last->next = head;
    printf("[P] head PID = %d \n", last->pid);
    key_t key;
    if((key = ftok("queue", 0)) == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    if((qd = msgget(key, IPC_CREAT | 0666)) == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    msg *mes;
    mes->mtype = last->pid;
    mes->value = 9;
    if(msgsnd(qd, mes, 3, 0) == -1){
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    else{
        printf("[P] SEND - сообщение отправлено!\n");
    }

    return 0;
}
