#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "../Modulos/gestionAdmin.h"
#include "../sqlite/sqlite3.h"
//#include <unistd.h>

int selectOpcion(int numOpciones){
    int opcion;
    do
    {
        
        printf("Seleccione una opcion: ");
        printf("_________________________________________________________\n");
        char str[MAX_CHARACTERS_FOR_OPTIONS];
		fflush(stdout);
		fgets(str, MAX_CHARACTERS_FOR_OPTIONS, stdin);
		sscanf(str, "%d", &opcion);
		
    } while (!comprobarOpcionValida(opcion,numOpciones));
    return opcion;   
}

int comprobarOpcionValida(int opcion, int numOpciones){
	if (opcion > 0 && opcion <= numOpciones){
		return 1;
	}else{
		printf("\nError, introduce una opcion valida.\n\n");
		return 0;
	}
}


int printMenuInicio(){
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

    logger(0,"aitor","Acceso a el menu de administrador");
    abrirConexion();


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


void menuInicio(){
    int salir=0;   
    while (salir==0)
    {
        int opcion=selectOpcion(printMenuInicio()); 
        if(opcion==1) {

                printf("Has seleccionado la opcion 1: INICIAR SESION.\n");
                salir=1;
                menuLogin();
                salir=1;
                break;
        }else if(opcion==2) {
                        
                printf("Saliendo del programa\n");
                salir=1;
        } 
        else {
            printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
        }
    }



void menuPrincipal(){
    int salir=0;   
    while (salir==0)
    {
        int opcion=selectOpcion(printMenuPrincipal()); 
        if(opcion==1) {

                printf("Has seleccionado la opcion 1: Gestionar ACTIVIDADES.\n");
                menuGestionAct();
                salir=1;
        }else if(opcion==2) {
                        
                printf("Has seleccionado la opcion 2: Gestionar PROPUESTAS.\n");
                salir=1;
        }else if(opcion==3) {
                        
                printf("Has seleccionado la opcion 3: 3. Crear ADMINISTRADOR.\n");
                salir=1;
        }else if(opcion==4) {
                        
                printf("CERRANDO SESION\n");
                menuInicio();
                salir=1;
        }else {
            printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
        }
    }



void menuGestionAct(){
    int salir=0;   
    while (salir==0)
    {
        int opcion=selectOpcion(printGestionAct()); 
        if(opcion==1) {

                printf("Has seleccionado la opcion 1: Visualizar ACTIVIDADES.\n");
                salir=1;
        }else if(opcion==2) {
                        
                printf("Has seleccionado la opcion 2: Añadir ACTIVIDADES.\n");
                salir=1;
        }else if(opcion==3) {
                        
                printf("Has seleccionado la opcion 3: Modificar ACTIVIDADES.\n");
                salir=1;
        }else if(opcion==4) {
                        
                printf("Has seleccionado la opcion 4: 4. Eliminar ACTIVIDADES.\n");
                salir=1;
        }else if(opcion==5) {
                        
                printf("Volviendo al MENU PRINCIPAL\n");
                menuPrincipal();
        }
        else {
            printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
        }
    }





void menuLogin() {
    char usuario[50];
    char contrasena[50];
    abrirConexion();

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", usuario);

    printf("Ingrese su contrasena: ");
    scanf("%s", contrasena);

    int resultado = login(usuario, contrasena);

    if (resultado == 1) {
        printf("Iniciando sesion.\n");
        menuPrincipal();
    } else {
        printf("Credenciales incorrectas.\n");
    }
}