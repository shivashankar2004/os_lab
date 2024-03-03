#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
void main(){
    printf("child <%ld> im always my pid is <%ld> and my parent got pid <%ld>./n",(long)getpid(),(long)getpid(),(long)getpid());
    printf("child<%ld>goodbye!/n",(long)getpid());
    exit(EXIT_SUCCESS);
}