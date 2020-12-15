#!/bin/bash

##  ___ _                      _    _     
## | _ |_)___ _ ___ _____ _ _ (_)__| |___ 
## | _ \ / -_) ' \ V / -_) ' \| / _` / _ \
## |___/_\___|_||_\_/\___|_||_|_\__,_\___/
##  __ _| |                               
## / _` | |                               
## \__,_|_|                               
##  ___         _      _                  
## / __| __ _ _(_)_ __| |_                
## \__ \/ _| '_| | '_ \  _|               
## |___/\__|_| |_| .__/\__|               
##               |_|      

while true
do
   # Visualizamos el menú
   echo -e "Por favor, seleccione una de las opciones que se le muestra a continuacion:"
   echo -e "1) Mostrar el código de el archivo intermedia.c"
   echo -e "2) Compilar el archivo intermedia.c"
   echo -e "3) Ejecución del programa intermedia.c"
   echo -e "4) Salir del programa."

   read option
   case $option in

      1) echo -e "Ha elegido ver el código del programa intermedia.c\n"
         cat intermedia.c;;

      2) echo -e "Su selección es: Compilar el archivo .c del programa\n"
         gcc -o intermedia intermedia.c;;

      3) echo -e "Ha elegido ejecutar el programa intermedia.c\n"
         echo -e "Seleccione el número de pacientes para la ejecución del programa: "
         read n

         if test -f intermedia
         then
            if test -x intermedia
            then
               ./intermedia $n
            else
               echo -e "No tiene permisos de ejecucion"
            fi
         else
            echo -e "Necesita compilar antes de ejecutar"
         fi;;   

      4) echo -e "Su selección es: Salir del script\n"
         exit 0;;
   esac
done