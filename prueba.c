#include <stdio.h> // printf, stderr, fprintf
#include <time.h> // time
#include <stdlib.h>
int  main() {
    srand(time(NULL));
    int aleatorio = rand() % (10-1+1) +1;
    printf("El numero es %d", aleatorio);
    
    return 0;
}