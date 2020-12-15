#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void muestraNumero(int sig); // Función de tipo handler

int main(int argc, char *argv[])
{

    /* Se le asigna el handler a la señal SIGUSR1 */
    if (signal(SIGUSR1, muestraNumero) == SIG_ERR)
    {
        perror("Llamada a signal.");
        exit(-1);
    }
    /* La proxima vez que se reciba la señal SIGUSR1
 * se llamará a la función muestraNumero()
 */
while(1);
}


void muestraNumero(int sig) {
 /* Se vuelve a asignar el handler a la señal SIGUSR1 */
 if (signal(SIGUSR1, muestraNumero)==SIG_ERR) {
 perror("Llamada a signal.");
 exit(-1);
 }
 /* Se ejecuta el código de la rutina de tratamiento */
 printf("Número de señal recibida: %d", sig);
}