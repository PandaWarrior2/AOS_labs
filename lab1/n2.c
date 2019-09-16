#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
int main(int argc, char * argv[]){
    if(argc == 1){
        printf("No arguments!\n");
    }
    else if(argc == 2){
        printf("No permission options!\n");
    }
    else {
        printf("Creating file %s with permissions %s\n", argv[1], argv[2]);
        FILE *fp = fopen(argv[1], "w");
        int code;
        char str[255];
        do {
            code = scanf("%s", str);
            if(code != -1){
                fwrite(&str, sizeof(char), strlen(str), fp);
                fwrite("\n", sizeof(char), 1, fp);
            }

        } while(code != -1);
        int mode = strtol(argv[2],0,8);
        fclose(fp);
        if(chmod(argv[1], mode) < 0){
            perror("chmod error: ");
        }
    }
    return 0;
}
