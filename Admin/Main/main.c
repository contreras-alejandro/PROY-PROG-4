#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hConsole, 1);
    int opcion;
    
    do {
        printf("________\n");
        printf("||MENU||\n");
        printf("________\n");
        printf("**Bienvenido al programe de administración del servidor**\n");
        printf("1. Inicar sesión\n");
        printf("2. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Has seleccionado la opción 1: INICIAR SESIÓN.\n");
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