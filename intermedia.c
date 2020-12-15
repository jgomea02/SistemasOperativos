/**
 * @author Jose Manuel Gómez Álvarez, 2020
 */

#include <stdio.h> // printf, stderr, fprintf
#include <sys/types.h> // pid_t
#include <unistd.h> // _exit, fork, sleep
#include <stdlib.h> // exit, WIFEXITED
#include <string.h> // strlen
#include <ctype.h> // isdigit
#include <time.h> // time
#include <signal.h> // signal
#include <wait.h> // wait, waitpid
#include <stdbool.h> // bool


//Funcion que calcula si se crea el número suficiente de vacunas.
void farmaceuticoSigusr1();
//Funcion que calcula si un enfermo ha reaccionado a la vacuna.
void enfermoSigusr1();
void medicoSigusr2(int size, pid_t *ptr);

int main(int argc, char *argv[]) //el  proceso es en si mismo el epidemiologo
{
    if (argc != 2)
    {
        // Comprueba que en la ejecución solo se introduzca un único valor.
        fprintf(stderr, "El programa debe de ser ejecutado con un único parámetro.\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < strlen(argv[1]) - 1; ++i)
    {
        // Comprueba que el argumento que se pasa por parametro sea un entero positivo
        char *cCurrent = (&argv[1])[i];
        if (*cCurrent != '\0' && !isdigit(*cCurrent))
        {
            fprintf(stderr, "El argumento del programa debe de ser un ENTERO POSITIVO\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Soy el proceso principal del programa, el epidemiologo y mi pid es %d\n", getpid());
    printf("\n");

    // Alamcena la entrada como un entero.
    int enfermos = atoi(argv[1]);

    // Declaracion de los procesos hijos de epidemiolgo que son farmaceutico y médico.
    pid_t farmaceutico;
    pid_t medico;

    farmaceutico = fork();
    if (farmaceutico == -1)
    {
        // Error forking.
        perror("Fork error %d\n");
        exit(EXIT_FAILURE);
    }
    else if (!farmaceutico)
    {
        printf("Aqui se crea el farmaceutico, su pid es %d y el de su padre es %d\n", getpid(), getppid());
        printf("\n");
        signal(SIGUSR1, farmaceuticoSigusr1);
        for (;;);
    }
    else
    {
        /*
        * De vuelta al proceso padre, realizamos otro fork para crear el otro proceso hijo, el médico, que será el encargado
        * de suministrar las vacunas a los enfermos.
        */

        medico = fork();
        //Comprobación de fork
        if (medico == -1)
        {
            perror("Fork error %d\n");
            exit(EXIT_FAILURE);
        }
        else if (!medico)
        {
            printf("Aqui se crea el médico, su pid es %d y el pid de su padre es %d\n", getpid(), getppid());
            printf("\n");
            pid_t rgpidEnfermos[enfermos];
            for (int i = 0; i < enfermos; ++i)
            {
                pid_t pidEnfermos = fork();
                if(pidEnfermos == -1)
                {
                    perror("Fork error\n");
                    exit(EXIT_FAILURE);
                }
                else if (!pidEnfermos)
                {
                    rgpidEnfermos[i] = pidEnfermos;
                    signal(SIGUSR1, enfermoSigusr1);
                    for (;;);
                }
                else
                {
                    rgpidEnfermos[i] = pidEnfermos;
                }
                
                printf("Soy el enfermo y mi pid es %d\n", rgpidEnfermos[i]);
                printf("\n");
            }
            signal(SIGUSR2, (void (*)(int)) medicoSigusr2);
            medicoSigusr2(enfermos, rgpidEnfermos);
        }
        else
        {
            sleep(2);
            kill(farmaceutico, SIGUSR1);

            bool sufVacunas;
            int  stat = 0;//status
            waitpid(farmaceutico, &stat, 0);
            if (WIFEXITED(stat))
            {
                sufVacunas = WEXITSTATUS(stat);
            }

            if (!sufVacunas)
            {
                fprintf(stderr, "No hay suficientes vacunas.\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("El farmaceutico hizo suficientes vacunas y se las da al médico para que las reparta.\n");
                printf("\n");
                kill(medico, SIGUSR2);
                stat = 0;
                waitpid(medico, &stat, 0);
                if (WIFEXITED(stat))
                {
                    printf("%d pacientes reaccionaron a la vacuna.\n", WEXITSTATUS(stat));
                }
            }
        }
    }
}

void farmaceuticoSigusr1()
{
    srand(time(NULL));
    // Reset the signal.
    signal(SIGUSR1, farmaceuticoSigusr1);
    _exit(rand() & 1); //lo mismo que poner rand() % 2
}

void enfermoSigusr1()
{
    srand(time(NULL));
    // Reset the signal.
    signal(SIGUSR1, enfermoSigusr1);
    _exit(!((rand() % 10 + 1) % 2));
}

void medicoSigusr2(int s, pid_t *p)
{
    signal(SIGUSR2, (void (*)(int)) medicoSigusr2);
    int enfermosConReaccion = 0;
    for (int i = 0; i < s; ++i)
    {
        kill(p[i], SIGUSR1);
        int status = 0;
        waitpid(p[i], &status, 0);
        if (WIFEXITED(status))
        {
            enfermosConReaccion += WEXITSTATUS(status);
        }
    }
    _exit(enfermosConReaccion);
}
