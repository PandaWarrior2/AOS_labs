/*
 * =====================================================================================
 *
 *       Filename:  n11new.c
 *
 *    Description: Lab 3, number 11
 *
 *        Version:  1.0
 *        Created:  18.10.2019 12:15:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
void sighandler(int);
int create_matrix(int);
int print_matrix(int, int);
int action (int, int);
int main(int argc, char * argv[]){
    if(argc < 2){
        printf("Usage %s dimension\n", argv[0]);
        return 0;
    }
    int dim = atoi(argv[1]);
    int fd;
    if((fd = create_matrix(dim)) == -1){
        return 0;
    }

    struct sigaction act, oact;
    act.sa_handler = sighandler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, &oact);
   // sigaction(SIGINT, &act, &oact); // для удобного тестирования (ctrl+c)
    sigset_t mask, omask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, &omask);
    sigdelset(&mask, SIGUSR1);   // Сигнал, по которому синхронизируются процессы
    sigdelset(&mask, SIGINT);    // Для того, чтобы можно было выйти по ctrl+c
   // sigdelset(&mask, SIGALRM);   // Для корректной работы sleep()

    int pid;
    if((pid = fork()) == -1){
        perror("fork error");
        return 0;
    }

    if(pid){
        printf("[P] Дочерний процесс создан! PID = %d\n", pid);
        while(1){
            print_matrix(fd,dim);
            if(kill(pid, SIGUSR1) == -1){
                perror("[P] kill error");
            }
            sleep(1);
            if(sigsuspend(&mask) == -1){
                perror("[P] sigsuspend error");
            }
        }
    }
    else{
        printf("[C] PID = %d\n", getpid());
        while(1){
            if(sigsuspend(&mask) == -1) {
                perror("[C] sigsuspend error");
            }
            sleep(1);
            printf("[C] Выполняется обработка матрицы\n");
            action(fd, dim);
            if(kill(getppid(), SIGUSR1) == -1){
                perror("[C] kill error");
            }
        }
    }
    close(fd);
}

void sighandler(int sig){
    printf("[H] Handler call by PID = %d\n", getpid());
    int d;
    //scanf("%d", &d);
}

int create_matrix(int dim){
    int fd;
    if((fd = open("matrix", O_RDWR | O_CREAT, 0755)) == -1) {
        perror("Open error (matrix)");
        return -1;
    }
    for(int i = 0; i < dim*dim; i++){
        if(write(fd, "0", 1) == -1){
            perror("[create_matrix] Write error");
        }
    }
    return fd;

}

int action(int fd, int dim){
    int old_pos;
    if((old_pos = lseek(fd, 0, SEEK_CUR)) == -1){
        perror("[action] lseek_error");
        return -1;
    }
    if(lseek(fd, 0, SEEK_SET) == -1){
        perror("[action] lseek error");
        return -1;
    }

    char c;
    int n;
    do{
        if((n = read(fd, &c, 1)) == -1){
            perror("read error");
            return -1;
        }
        if(c == '0'){
            if(lseek(fd, (long)-1, SEEK_CUR) == -1){
                perror("lseek error");
            }
            if(write(fd, "1", 1) == -1){
                perror("write error");
            }
            break;
        }
        if(lseek(fd, 10, SEEK_CUR) == -1){
            perror("lseek error");
        }
    } while(n == 1);

    if(lseek(fd, old_pos, SEEK_SET) == -1){
        perror("[action] lseek_error");
        return -1;
    }
    return 1;
}

int print_matrix(int fd, int dim){
    int old_pos;
    if((old_pos = lseek(fd, 0, SEEK_CUR)) == -1){
        perror("[print_matrix] lseek_error");
        return -1;
    }
    if(lseek(fd, 0, SEEK_SET) == -1){
        perror("[print_matrix] lseek error");
        return -1;
    }
    int n;
    char * buf;
    buf = malloc(dim);
    while(n = read(fd,buf,dim)){
        if(n == -1){
            perror("read error");
        }
        else{
            printf("%s\n", buf);
        }
    }
    if(lseek(fd, old_pos, SEEK_SET) == -1){
        perror("[print_matrix] lseek_error");
        return -1;
    }
    return 1;
}
