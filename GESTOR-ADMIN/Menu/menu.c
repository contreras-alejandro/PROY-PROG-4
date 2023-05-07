#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "../Modulos/gestionAdmin.h"
#include "../Modulos/gestionBD.h"
#include "../sqlite/sqlite3.h"
#include "../Modulos/leerCsv.h"


//FUNCION PARA DEVOLVER LA OPCION SELECCIONADA
int selectOpcion(int numOpciones){
   int opcion = 0;
   int valido =0;
    char str[MAX_CHARACTERS_FOR_OPTIONS];
    fflush(stdin);
    do {
        fflush(stdout);
        printf("Seleccione una opcion: (CTRL + C para salir)\n ");
        fgets(str, MAX_CHARACTERS_FOR_OPTIONS, stdin);
         if (sscanf(str, "%d", &opcion) == 1) {
            //SI ES VALIDA LA DEVOLVEMOS
            if (comprobarOpcionValida(opcion, numOpciones)) {
                valido=1;
                return opcion;
            }
               }
               else if(strlen(str) == 1){
                printf("Error, no se ha introducido ningun valor.\n");

               }
               else{
                 printf("Error, introduce una opcion valida.\n");

               }
}while(valido==0);

}

//FUNCION PARA COMPROBAR SI LA OPCION INTRODUCIDA ES VALIDA
int comprobarOpcionValida(int opcion, int numOpciones){
    //TIENE QUE SER MAYOR QUE CERO, Y MENOR O IGUAL AL TOTAL DE NUMERO DE OPCIONES
	if (opcion > 0 && opcion <= numOpciones){
		return 1;
	}else{
		printf("\nError, introduce una opcion valida.\n\n");
		return 0;
	}
}


//FUNCION PARA IMPRIMIR EL MENU DE INICIO

int printMenuInicio(){
    int numOpciones=2;
    printf("\n||MENU||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al programa de administracion del servidor**\n");
    printf("1. Iniciar sesion\n");
    printf("2. Salir\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}

//FUNCION PARA IMPRIMIR EL MENU PRINCIPAL
int printMenuPrincipal(){
    int numOpciones=3;

    printf("\n||MENU ADMINISTRADOR||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al menu de administrador**\n");
    printf("1. Gestionar ACTIVIDADES\n");
    printf("2. Crear ADMINISTRADOR\n");
    printf("3. Cerrar sesion\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}


//FUNCION PARA IMPRIMIR EL MENU DE GESTION DE ACTIVIDAD
int printGestionAct(){
    int numOpciones=7;
    printf("\n||GESTION DE ACTIVIDADES AL AIRE LIBRE||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al programa de administracion del servidor**\n");
    printf("1. Cargar actividades del CSV a BD\n");
    printf("2. Vaciar tabla ACTIVIDADES de la BD\n");
    printf("3. Visualizar ACTIVIDADES\n");
    printf("4. Anadir ACTIVIDADES\n");
    printf("5. Modificar ACTIVIDADES\n");
    printf("6. Eliminar una ACTIVIDAD\n");
    printf("7. Volver\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}

//FUNCION PARA GESTION DEL MENU DE INICIO
void menuInicio(){
    int salir=0;   
    while (salir==0)
    {
        int opcionesPosibles=printMenuInicio (); 
        //obtenemos la opcion seleccionada
        int opcion = selectOpcion(opcionesPosibles);
        //dependiendo la seleccionada, entramos en INICIO DE SESION o SALIMOS
        if(opcion==1) {

                printf("Has seleccionado la opcion 1: INICIAR SESION.\n");
                salir=1;
                menuLogin();
                salir=1;
                break;
        }else if(opcion==2) {
                        
                printf("Saliendo del programa...GRACIAS POR USAR NUESTRO PROGRAMA!\n");
                salir=1;
                break;
        } 
        else {
            printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
        }
    }


//FUNCION PARA GESTION DEL MENU PRINCIPAL
void menuPrincipal(char *usuario){
      int salir=0;   
      printf("Sesion iniciada por: %s\n", usuario);
    while (salir==0)
    {
        //OBTENEMOS LA OPCION SELECIONADA
        int opcion = selectOpcion(printMenuPrincipal()); 
        //DEPENDIENDO LA OPCION, ENTRAMOS EN LA FUNCION CORRESPONDIENTE.

        if(opcion==1) {
            printf("Has seleccionado la opcion 1: Gestionar ACTIVIDADES.\n");
            menuGestionAct(usuario);
            salir=1;
            break;
         } else if(opcion==2) {
            printf("Has seleccionado la opcion 2: Crear ADMINISTRADOR.\n");
            logger(0,usuario,"ACCEDIENDO A CREAR ADMINISTRADOR");
            crearAdmin(usuario); 
            menuPrincipal(usuario);       
            salir=1;
            break;
        } else if(opcion==3) {
            printf("CERRANDO SESION\n");
            menuInicio(usuario);
            salir=1;
            break;
        } else {
            //SI LA OPCION NO ES VALIDA, ERROR.
            printf("¡ERROR, SELECCIONE UN NUMERO VALIDO!\n");
            break;
        }
    }
}


//FUNCION PARA GESTION DEL MENU DE GESTION DE ACTIVIDADES
void menuGestionAct(char *usuario){
    int salir=0;   
    while (salir==0)
    {
        //OBTENEMOS LA OPCION
        int opcion=selectOpcion(printGestionAct()); 
         //DEPENDIENDO LA OPCION, ENTRAMOS EN LA FUNCION CORRESPONDIENTE.

        if(opcion==3) {
                printf("Has seleccionado la opcion 3: Visualizar ACTIVIDADES.\n");
                verActividades(usuario);
                menuGestionAct(usuario);
                salir=1;
        }else if(opcion==4) {     
                printf("Has seleccionado la opcion 4: Anadir ACTIVIDADES.\n");
                logger(0,usuario,"ACCEDIENDO A AÑADIR ACTIVIDADES");
                crearActividad(usuario);
                menuGestionAct(usuario);
                salir=1;
                break;
        }else if(opcion==5) {
                int id;
                int confirmar; 
                int existe;
                char resultado[10]; 
                logger(1,usuario,"ACCEDIENDO A MODIFICAR ACTIVIDADES");        
                printf("Has seleccionado la opcion 5: Modificar ACTIVIDADES.\n");
                 do {
                    printf("Ingrese el id de la actividad que quieras eliminar: ");
                    fflush(stdout);
                    //PEDIMOS EL ID POR TECLADO
                    fgets(resultado,10,stdin);
                    sscanf(resultado,"%i", &id);
                    existe= comprobarActividad(id,usuario);
                     if (existe == 0) {
                         printf("No existe una actividad con ese id\n");
                         }
                 }while(existe==0);
                printf("Estas seguro que quieres modificar esta actividad?\n");
                buscarActividadPorId(id,usuario);
                printf("1.Si\n2.No\nSeleccione una opcion:\n");
                fgets(resultado,10,stdin);
                sscanf(resultado,"%i", &confirmar);
                if(confirmar==1){  
                    modificarActividad(id,usuario);
                    menuGestionAct(usuario);
                }else if (confirmar==2)
                {
                    menuGestionAct(usuario);
                }
                salir=1;
        }else if(opcion==6) { 
                int id;
                int confirmar; 
                int existe; 
                char resultado[10];  
                printf("Has seleccionado la opcion 6: 6. Eliminar una ACTIVIDAD.\n");
                 //lo buscamos, Y SI EXISTE?!!! Y SE CONFIRMA, SE ELIMINA
                 do {
                    printf("Ingrese el id de la actividad que quieras eliminar: ");
                    fflush(stdout);
                    //PEDIMOS EL ID POR TECLADO
                    fgets(resultado,10,stdin);
                    sscanf(resultado,"%i", &id);
                    existe= comprobarActividad(id,usuario);
                     if (existe == 0) {
                         printf("No existe una actividad con ese id\n");
                         }
                 }while(existe==0);


                printf("Estas seguro que quieres eliminar esta actividad?\n");
                printf("1.Si\n2.No\nSeleccione una opcion:");
                fgets(resultado,10,stdin);
                sscanf(resultado,"%i", &confirmar);
                //SI CONFIRMAMOS
                if(confirmar==1){  
                    eliminarAct(id,usuario);
                    menuGestionAct(usuario);
                }else if (confirmar==2)
                {
                    menuGestionAct(usuario);
                }
                salir=1;
        }else if(opcion==1) {
                        
                logger(1,usuario,"ACCEDIENDO A IMPORTAR CSV A BASE DE DATOS");   
                printf("Has seleccionado la opcion 1: Importar csv a BD.\n");       
                cargarCsv(usuario);
                menuGestionAct(usuario);
                salir=1;
                break;

        }else if(opcion==2) {
                        
                logger(1,usuario,"ACCEDIENDO A ELIMINAR ACTIVIDADES");       
                printf("Has seleccionado la opcion 2: 2. Eliminar ACTIVIDADES.\n");
                eliminarTablaActividades(usuario);
                menuGestionAct(usuario);
                salir=1;
        }else if(opcion==7) {
                        
                printf("Volviendo al MENU PRINCIPAL\n");
                menuPrincipal(usuario);
                salir=1;

        }
        else {
            printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
        }
    }



//FUNCION PARA GESTION DEL MENU DE LOGIN
 void menuLogin() {
    //guardamos espacio en memoria, ya que el usuario lo pasaremos por las funciones para el log
    int resultado;
    int salir=0;

    //PEDIMOS LOS VALORES MIENTRAS NO SEAN CORRECTO

    while (salir==0)
    {

        char nombre_usu [20];
        char usu_contra [20];

        fflush(stdin);
        printf("Ingrese su nombre de usuario: ");
        fgets(nombre_usu,20,stdin);
        nombre_usu[strcspn(nombre_usu, "\n")] = 0;


        fflush(stdin);
        printf("Ingrese su contrasena: ");
        fgets(usu_contra,20,stdin);
        usu_contra[strcspn(usu_contra, "\n")] = 0;

        
        resultado = login(nombre_usu, usu_contra);

        if (resultado == 1) {
            //si son correctos, se inicia sesion
            printf("Iniciando sesion...\n");
            logger(0,nombre_usu,"SESION INICIADA");
            salir=1;
            menuPrincipal(nombre_usu);
        } else {
            printf("Introduce un usuario y contrasena correctos\n");
        }
    }
    

}


