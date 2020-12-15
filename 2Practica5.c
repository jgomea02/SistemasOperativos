#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
    printf("Arrancando...\n");

    pid_t mipid;
    mipid = fork();
    
    if(mipid == -1){
        perror("Error en la llamada a fork()");
    } else if (mipid == 0){
        printf("Hijo: Mi pid %d\n", getpid());
    }else{
        printf("Padre: mi pid %d\n", getpid());
    }

    printf("Finalizando...\n");
    return 0;

}
