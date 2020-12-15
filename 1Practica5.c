#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pidproceso, pidpadre;
    pidproceso = getpid();
    pidpadre = getppid();
    printf("Soy el proceso de pid = %d\n", pidproceso);
    printf("Mi padre es el proceso de pid = %d\n", pidpadre);
    return 0;
}