#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hConsole, 1);
    int opcion;
    
    do {
        printf("||MENU||\n");
        printf("_________________________________________________________\n");
        printf("**Bienvenido al programa de administracion del servidor**\n");
        printf("1. Inicar sesion\n");
        printf("2. Salir\n");
        printf("_________________________________________________________\n");
        printf("Seleccione una opcion: ");
        printf("_________________________________________________________\n");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Has seleccionado la opcion 1: INICIAR SESION.\n");
                break;
            case 2:
                printf("Saliendo del programa\n");
                break;
            default:
                printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
    } while (opcion != 2);
    
    return 0;
}