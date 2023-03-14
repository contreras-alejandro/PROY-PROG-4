#include <stdio.h>

int selectOpcion(int numOpciones){
    int opcion;
    do
    {
        printf("Seleccione una opcion: ");
        printf("_________________________________________________________\n");
        scanf("%d", &opcion);
    } while (opcion!=numOpciones);
    return opcion;   
}



int printMenuAdmin(){
    int numOpciones=2;
    printf("||MENU||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al programa de administracion del servidor**\n");
    printf("1. Inicar sesion\n");
    printf("2. Salir\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}

