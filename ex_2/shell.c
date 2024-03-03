#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#define MAX 60
int main(){
    char *argv[MAX];
    int flag=1;

    while(flag){
        //1.) print out prompt
        printf("$");
        fflush(stdout);

        //2.)read an input
        char inp[MAX];
        fgets(inp,MAX,stdin);

        //3.) parsing line into program and command
        char *token;
        token=strtok(inp,"\n");
        int i=0;
        while(token!=NULL){
            argv[i]=token;
            token=strtok(NULL,"\n");
            i++;
        }
        argv[i]=NULL;

        if(strcmp(argv[0],"exit")==0){
            flag=0;
            continue;
        }

        if (strcmp(argv[0], "cat") == 0) {
            // Execute cat command
            for (int j = 1; argv[j] != NULL; j++) {
                FILE *fp = fopen(argv[j], "r");
                if (fp != NULL) {
                    char line[MAX];
                    while (fscanf(fp,"%s",line) != EOF) {
                        printf("%s", line);
                    }
                    fclose(fp);
                } else {
                    printf("cat: %s: No such file or directory\n", argv[j]);
                }
            }
            continue;
        }

        //4.) calling fork()
        pid_t pid=fork();
        if(pid<0){
            fprintf(stderr,"fork failed");
        }
        else if(pid==0){
            execvp(argv[0],argv);//exec function
            perror("command not found");
            return 0;
        }
        else{
            wait(NULL);//wait function
        }

    }
    return 0;
}