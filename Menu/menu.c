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

void menuAdmin(){
    int salir=0;   
    while (!salir)
    {
        int opcion=selectOpcion(printMenuAdmin());    
        switch (opcion) {
            case 1:
                printf("Has seleccionado la opcion 1: INICIAR SESION.\n");
                break;
            case 2:
                printf("Saliendo del programa\n");
                salir=1;
                break;
            default:
                printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
    }
    
}