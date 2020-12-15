#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main(void){
    pid_t otropid;
    printf("Por favor, introduce el pid del proceso que desea terminar: ");
    scanf("%d", &otropid);
    kill(otropid, SIGTERM); //Termina el proceso de pid = otropid, para matar se pone SIGKILL por SIGterm
    exit(0);

}