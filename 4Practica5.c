#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
    pid_t pid;
    int estado, edad, edadHijo;

    edad = fork();
    edadHijo = fork();

    if(pid > 0){
    pid = wait(&estado);
    edad = WEXITSTATUS(estado);
    printf("Mi hijo %d ha fallecido a los %d años.\n", pid, edad);
    pid = wait(&estado);
    printf("pid = %d\n", pid);
    }else{

    }
    return 0;
}