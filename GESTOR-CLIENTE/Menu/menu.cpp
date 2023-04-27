#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"



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
    int numOpciones=3;
    printf("\n||MENU||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al programa del usuario**\n");
    printf("1. Registrar\n");
    printf("2. Iniciar sesion\n");
    printf("3. Salir\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}

//FUNCION PARA GESTION DEL MENU DE INICIO
void menuInicio() {
     int salir=0;   
    while (salir==0)
    {
        int opcionesPosibles=printMenuInicio (); 
        //obtenemos la opcion seleccionada
        int opcion = selectOpcion(opcionesPosibles);
        //dependiendo la seleccionada, entramos en INICIO DE SESION o SALIMOS
        if(opcion==1) {

                printf("Has seleccionado la opcion 1: REGISTRAR.\n");
                salir=1;
                //FUNCION DE MENU DE REGISTRO
                salir=1;
                break;
        }else if(opcion==2) {
                        
               printf("Has seleccionado la opcion 2: INICIAR SESION.\n");
                salir=1;
                menuLogin();
                break;
        } 
        else if(opcion==3) {
                        
                printf("Saliendo del programa...GRACIAS POR USAR NUESTRO PROGRAMA!\n");
                salir=1;
                break;
        } 
        else {
            printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
        }


}




//FUNCION PARA IMPRIMIR EL MENU PRINCIPAL
int printMenuPrincipal(){
    int numOpciones=6;

    printf("\n||MENU USUARIO||\n");
    printf("_________________________________________________________\n");
    printf("**Bienvenido al menu del usuario**\n");
    printf("1. Ver ACTIVIDADES\n");
    printf("2. Inscribirse\n");
    printf("3. Borrar inscripcion\n");
    printf("4. VALORAR ACTIVIDAD\n");
    printf("5. Perfil\n");
    printf("6. Volver\n");

    printf("_________________________________________________________\n");
    return numOpciones;
}

//FUNCION PARA GESTION DEL MENU PRINCIPAL
void menuPrincipal(char *usuario) {

    int salir=0;   
      printf("Sesion iniciada por: %s\n", usuario);
    while (salir==0)
    {
        //OBTENEMOS LA OPCION SELECIONADA
        int opcion = selectOpcion(printMenuPrincipal()); 
        //DEPENDIENDO LA OPCION, ENTRAMOS EN LA FUNCION CORRESPONDIENTE.

        if(opcion==1) {
            printf("Has seleccionado la opcion 1: Ver actividades.\n");
            //menuGestionAct(usuario);
            salir=1;
            break;
        } else if(opcion==2) {
            printf("Has seleccionado la opcion 2:  INSCRIBIR a ACTICIDAD.\n");
            //menuPrincipal(usuario);
            salir=1;
             break;
        } else if(opcion==3) {
            printf("Has seleccionado la opcion 3: BORRAR INSCRIPCION a ACTICIDAD.\n");
            //logger(0,usuario,"ACCEDIENDO A CREAR ADMINISTRADOR");
            //crearAdmin(usuario); 
            menuPrincipal(usuario);       
            salir=1;
            break;
        } else if(opcion==4) {
            printf("Has seleccionado la opcion 4: Valorar ACTIVIDAD.\n");
            //menuInicio(usuario);
            salir=1;
            break;
        
        } 
        else if(opcion==5) {
            printf("Has seleccionado la opcion 5:  PERFIL.\n");
            //menuInicio(usuario);
            salir=1;
            break;
        
        } 
        
          else if(opcion==6) {
            printf("Has seleccionado la opcion 6: VOLVER\n");
            //menuInicio(usuario);
            salir=1;
            break;
        
        } 
          else if(opcion==7) {
            printf("VOLVER...\n");
            //menuInicio(usuario);
            salir=1;
            break;
        
        } 
         
        else  {
            //SI LA OPCION NO ES VALIDA, ERROR.
            printf("¡ERROR, SELECCIONE UN NUMERO VALIDO!\n");
            break;
        }
    }
}

//falta
int printMenuVerAct() {

    int numOpciones=4;


    printf("\n||VER ACTIVIDADES||\n");
    printf("_________________________________________________________\n");
    printf("1.FILTRAR POR FECHA\n");
    printf("2.FILTRAR POR PUBLICO\n");
    printf("3.FILTRAR POR MEJOR VALORADAS\n");
    printf("4.Volver\n");

    printf("_________________________________________________________\n");
    return numOpciones;

}


//FUNCION PARA GESTION DEL MENU DE INICIO
void menuVerActividadesInicio() {
     int salir=0;   
    while (salir==0)
    {
        int opcionesPosibles=printMenuVerAct (); 
        //obtenemos la opcion seleccionada
        int opcion = selectOpcion(opcionesPosibles);
        //dependiendo la seleccionada, entramos en INICIO DE SESION o SALIMOS
        if(opcion==1) {

                printf("Has seleccionado la opcion 1: FILTRAR POR FECHA.\n");
                salir=1;
                //FUNCION DE MENU DE REGISTRO
                salir=1;
                break;
        }else if(opcion==2) {
                        
               printf("Has seleccionado la opcion 2: FILTRAR POR PUBLICO.\n");
                salir=1;
                break;
        } 
        else if(opcion==3) {
                        
                printf("Has seleccionado la opcion 3: FILTRAR POR MEJOR VALORADAS\n");
                salir=1;
                break;
        }

         else if(opcion==4) {
                        
                printf("Volver...\n");
                salir=1;
                break;
        }  

        
        else {
            printf("¡ERROR, SELECCIONE UN NUMERO!\n");
        }
        }

}










//FUNCION PARA MOSTRAR OPCIONES DE PERFIL
int printMenuPerfil() {
     int numOpciones=2;


     
    printf("\n||PERFIL||\n");
    printf("_________________________________________________________\n");
    printf("1. Ver INSCRIPCIONES\n");
    printf("2. Cambiar CONTRANSEYA\n");
    printf("_________________________________________________________\n");
    return numOpciones;
}

//FUNCION PARA GESTION DEL MENU DE PERFIL
void menuPerfil() {
     int salir=0;   

    while (salir==0)
    {
        //OBTENEMOS LA OPCION SELECIONADA
        int opcion = selectOpcion(printMenuPerfil()); 
        //DEPENDIENDO LA OPCION, ENTRAMOS EN LA FUNCION CORRESPONDIENTE.

        if(opcion==1) {
            printf("Has seleccionado la opcion 1: Ver INSCRIPCIONES\n");
            //funcion
            salir=1;
            break;
        } else if(opcion==2) {
            printf("Has seleccionado la opcion 2: Cambiar CONTRASENYA.\n");
            //funcion
            salir=1;
             break;
        }
         
        else  {
            //SI LA OPCION NO ES VALIDA, ERROR.
            printf("¡ERROR, SELECCIONE UN NUMERO VALIDO!\n");
            break;
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

        
        //resultado = login(nombre_usu, usu_contra);

        if (resultado == 1) {
            //si son correctos, se inicia sesion
            printf("Iniciando sesion...\n");
            salir=1;
            menuPrincipal(nombre_usu);
        } else {
            printf("Introduce un usuario y contrasena correctos\n");
        }
    }
 

}




