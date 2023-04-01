#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "../Modulos/gestionAdmin.h"
#include "../Modulos/gestionBD.h"
#include "../sqlite/sqlite3.h"
#include "../Modulos/leerCsv.h"
//#include <unistd.h>

//FUNCION PARA DEVOLVER LA OPCION SELECCIONADA
int selectOpcion(int numOpciones){
   int opcion = 0;
    char str[MAX_CHARACTERS_FOR_OPTIONS];
    printf("Seleccione una opcion: ");
    printf("_________________________________________________________\n");
    fflush(stdin);
    //PEDIMOS POR TECLADO LA OPCION
    while (fgets(str, MAX_CHARACTERS_FOR_OPTIONS, stdin) != NULL) {
        if (sscanf(str, "%d", &opcion) == 1) {
            //SI ES VALIDA LA DEVOLVEMOS
            if (comprobarOpcionValida(opcion, numOpciones)) {
                printf("La opcion seleccionada es %i\n", opcion);
                return opcion;
            }
        //SI NO SE INTRODUCE NINGUN VALOR, ERROR
        }
        if (strlen(str) == 1) {
            printf("Error, no se ha introducido ningun valor.\n");
        } 
         //SI NO ES VALIDA, ERROR
        else {
            printf("Error, introduce una opcion valida.\n");
        }
        printf("Seleccione una opcion: ");
    }

    return opcion;
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
    printf("||MENU||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al programa de administracion del servidor**\n");
    printf("1. Inicar sesion\n");
    printf("2. Salir\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}

//FUNCION PARA IMPRIMIR EL MENU PRINCIPAL
int printMenuPrincipal(){
    int numOpciones=4;

    printf("||MENU ADMINISTRADOR||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido**\n");
    printf("1. Gestionar ACTIVIDADES\n");
    printf("2. Gestionar PROPUESTAS\n");
    printf("3. Crear ADMINISTRADOR\n");
    printf("4. Cerrar sesion\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}


//FUNCION PARA IMPRIMIR EL MENU DE GESTION DE ACTIVIDAD
int printGestionAct(){
    int numOpciones=7;
    printf("||GESTION DE ACTIVIDADES AL AIRE LIBRE||\n");
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
                        
                printf("Saliendo del programa\n");
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
            printf("Has seleccionado la opcion 2: Gestionar PROPUESTAS.\n");
            printf("ESTA SECCION AUN NO ESTA DISPONIBLE, ESTARA HABILITADA CUANDO REALICEMOS EL CLIENTE");
            menuPrincipal(usuario);
            salir=1;
             break;
        } else if(opcion==3) {
            printf("Has seleccionado la opcion 3: Crear ADMINISTRADOR.\n");
            logger(0,usuario,"ACCEDIENDO A CREAR ADMINISTRADOR");
            crearAdmin(usuario); 
            menuPrincipal(usuario);       
            salir=1;
            break;
        } else if(opcion==4) {
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

                printf("Has seleccionado la opcion 1: Visualizar ACTIVIDADES.\n");
                verActividades(usuario);
                menuGestionAct(usuario);
                salir=1;
        }else if(opcion==4) {
                        
                printf("Has seleccionado la opcion 2: Anadir ACTIVIDADES.\n");
                logger(0,usuario,"ACCEDIENDO A AÑADIR ACTIVIDADES");
                crearActividad(usuario);
                menuGestionAct(usuario);
                salir=1;
                break;
        }else if(opcion==5) {
                int id;
                int confirmar; 
                logger(1,usuario,"ACCEDIENDO A MODIFICAR ACTIVIDADES");        
                printf("Has seleccionado la opcion 3: Modificar ACTIVIDADES.\n");
                printf("Ingrese el id de la actividad que quiera modificar: ");
                scanf("%d", &id);
                printf("Estas seguro que quieres modificar esta activiad?\n");
                buscarActividadPorId(id,usuario);
                printf("1.Si\n2.No\nseleccione opcion:");
                scanf("%d", &confirmar);
                if(confirmar==1){
                    //logger(0,usuario,"HA PASADO A MODIFICAR LA ACTIVIDAD CON ID %i",id);  
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
                    existe= comprobarActividadEliminar(id,usuario);
                     if (existe == 0) {
                         printf("No existe una actividad con ese id\n");
                         }
                 }while(existe==0);


                printf("Estas seguro que quieres eliminar esta activiad?\n");
                printf("1.Si\n2.No\nseleccione opcion:");
                scanf("%d", &confirmar);
                //SI CONFIRMAMOSS
                if(confirmar==1){
                    //logger(0,usuario,"HA PASADO A ELIMINAR LA ACTIVIDAD CON ID %i",id);  
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
    char *usuario = malloc(20 * sizeof(char));
    char *contrasena = malloc(20 * sizeof(char));
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
            printf("Iniciando sesion.\n");
            salir=1;
            menuPrincipal(nombre_usu);
        } else {
            printf("Introduce un usuario y contrasena correctos\n");
        }
        }
    //liberamos la contrasenya
    free(contrasena);
    logger(0,usuario,"SESION INICIADA");
    

}


