/*
 * =====================================================================================
 *
 *       Filename:  n6.c
 *
 *    Description:  Lab 6, number 6.
 *
 *        Version:  1.0
 *        Created:  29.10.2019 09:40:28
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
#define PROCESS_NUM 5
int wclose = 0;
int H(char*);
void signal_handler(int);

int main(int argc, char * argv[]){
    printf("[P-%d] Server started!\n", getpid());
    int pid;

    int qd;
    if((qd = msgget(getpid(), IPC_CREAT | 0755)) == -1){
        perror("msgget");
        exit(1);
    }
    else{
        printf("[P-%d] Очередь создана!\n", getpid());
    }

    struct sigaction act;
    act.sa_handler = signal_handler;
    act.sa_flags = 0;
    if(sigaction(SIGCHLD, &act, NULL) == -1){
        perror("sigaction");
    }
    char child_qd[5];
    char par_qd[10];
    int n = sprintf(par_qd, "%d", getpid());
    par_qd[n] = '\0';
    char * args[] = {"./client", par_qd, child_qd, NULL};
    for(int i = 0; i < PROCESS_NUM; i++){
        if((pid = fork()) == -1){
            perror("fork");
            exit(1);
        }

        switch(pid){
            case -1:
                perror("fork");
                exit(1);
            case 0:
                printf("[C-%d] Child process (number %d) created!\n",getpid(), i);
                n = sprintf(args[2], "%d", getpid());
                args[2][n] = '\0';
                execv("./client", args);
                perror("execv");
                exit(1);
            default:
                break;
        }
    }
        struct {
            long mtype;
            char mtext[20];
        } rec, ans;

        int cqd;
        while(1){
            if(wclose == PROCESS_NUM){
                break;
            }

            if(msgrcv(qd, &rec, 20, 0, 0) == -1){
                perror("msgrcv");
            }
            else{
                printf("[RECIEVE] Сообщение получено: (%d;%s)\n", rec.mtype, rec.mtext);
                if((cqd = msgget(rec.mtype, 0755)) == -1){
                    perror("msgget");
                }
                ans.mtype = 1;
                sprintf(ans.mtext, "%d", H(rec.mtext));
                if(msgsnd(cqd, &ans, 20, 0) == -1){
                    perror("msgsnd");
                }
                else{
                    printf("[ANS] Ответ отправлен!(%s) -> %d\n", ans.mtext, rec.mtype);
                }
            }
        }
        if(msgctl(qd, IPC_RMID, NULL) == -1) {
            perror("msgctl");
        }
        else {
            printf("[P] Очередь родительского процесса удалена!\n");
        }
        return 0;
}
void signal_handler(int sigid){
    wclose++;
    int pid = waitpid(-1, NULL, 0);
    int qid;
    if((qid = msgget(pid, 0755)) == -1){
        perror("msgget");
    }

    if(msgctl(qid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(1);
    }
    else{
        printf("Очередь с ключом %d удалена!\n", pid);
    }
}
int H(char * str){
    int result = 0;
    int i = 0;
    do{
        result ^= *(str+i);
    } while(*(str+(++i)));
    return result;
}
