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


int printMenuPrincipal(){
    int numOpciones=4;
    printf("||MENU ADMINISTRADOR||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido**\n");
    printf("1. Gestionar ACTIVIDADES\n");
    printf("2. Gestionar PROPUESTAS\n");
    printf("3. Crear ADMINISTRADOR\n");
    printf("4. Volver\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}



int printGestionAct(){
    int numOpciones=5;
    printf("||GESTION DE ACTIVIDADES AL AIRE LIBRE||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al programa de administracion del servidor**\n");
    printf("1. Visualizar ACTIVIDADES\n");
    printf("2. Añadir ACTIVIDADES\n");
    printf("3. Modificar ACTIVIDADES\n");
    printf("4. Eliminar ACTIVIDADES\n");
    printf("5. Volver\n");
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
                printMenuPrincipal();
            case 2:
                printf("Saliendo del programa\n");
                salir=0;
                break;
            default:
                printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
    }
    
}


