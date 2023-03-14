#include <stdio.h>
#include <windows.h>
#include "../Menu/menu.h"

int main() {
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hConsole, 1);
    int opcion;
    int numOpcion;
    
    do {
        numOpcion=printMenuAdmin();
        opcion=selectOpcion(numOpcion);    
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
    } while (opcion != 3);
    
    return 0;
}