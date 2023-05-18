#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <cstring>
#include "menu.h"
#include "gestionLog.h"
//#include "gestionCodigos.h"


#define const int MAX_CHARACTERS_FOR_OPTIONS = 50;

//FUNCION PARA DEVOLVER LA OPCION SELECCIONADA
int selectOpcion(int numOpciones)
{
    int opcion = 0;
    bool valido = false;
    std::string str;

    do {
        std::cout << "Seleccione una opcion: (CTRL + C para salir)" << std::endl;
        std::getline(std::cin, str);

        if (std::sscanf(str.c_str(), "%d", &opcion) == 1) {
            // SI ES VALIDA LA DEVOLVEMOS
            if (comprobarOpcionValida(opcion, numOpciones)) {
                valido = true;
                return opcion;
            }
        }
        else if (str.length() == 0) {
            std::cout << "Error, no se ha introducido ningun valor." << std::endl;
        }
        else {
            std::cout << "Error, introduce una opcion valida." << std::endl;
        }
    } while (!valido);

    return opcion;
}


//FUNCION PARA COMPROBAR SI LA OPCION INTRODUCIDA ES VALIDA
int comprobarOpcionValida(int opcion, int numOpciones) {
    if (opcion > 0 && opcion <= numOpciones) {
        return 1;
    } else {
        std::cout << "\nError, introduce una opcion valida.\n\n";
        return 0;
    }
}


//FUNCION PARA IMPRIMIR EL MENU DE INICIO

int printMenuInicio()
{
    int numOpciones = 3;

    std::cout << "\n||MENU||" << std::endl;
    std::cout << "_________________________________________________________" << std::endl;
    std::cout << "**Bienvenido al programa del usuario**" << std::endl;
    std::cout << "1. Registrar" << std::endl;
    std::cout << "2. Iniciar sesion" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "_________________________________________________________" << std::endl;

    return numOpciones;
}

//FUNCION PARA GESTION DEL MENU DE INICIO
void menuInicio(SOCKET s, char sendBuff[512], char recvBuff[512]) 
{
    int salir = 0;   
    while (salir == 0)
    {
        int opcionesPosibles = printMenuInicio (); 
        //obtenemos la opcion seleccionada
        int opcion = selectOpcion(opcionesPosibles);
        //dependiendo la seleccionada, entramos en INICIO DE SESION o SALIMOS
        if (opcion == 1) 
        {
            std::cout << "Has seleccionado la opcion 1: REGISTRAR." << std::endl;
            menuRegistrar(s,sendBuff,recvBuff);
            break;
        }
        else if (opcion == 2) 
        {
            std::cout << "Has seleccionado la opcion 2: INICIAR SESION." << std::endl;
            menuLogin(s,sendBuff,recvBuff);
            break;
        } 
        else if (opcion == 3) 
        {
            std::cout << "Saliendo del programa...GRACIAS POR USAR NUESTRO PROGRAMA!" << std::endl;
            salir = 1;
            break;
        } 
        else 
        {
            std::cout << "¡ERROR, SELECCIONE UN NUMERO!" << std::endl;
        }
    }
}




//FUNCION PARA IMPRIMIR EL MENU PRINCIPAL
int printMenuPrincipal() {
    int numOpciones = 6;

    std::cout << "\n||MENU USUARIO||\n";
    std::cout << "_________________________________________________________\n";
    std::cout << "**Bienvenido al menu del usuario**\n";
    std::cout << "1. Ver ACTIVIDADES\n";
    std::cout << "2. Inscribirse\n";
    std::cout << "3. Borrar inscripcion\n";
    std::cout << "4. VALORAR ACTIVIDAD\n";
    std::cout << "5. Perfil\n";
    std::cout << "6. Volver\n";
    std::cout << "_________________________________________________________\n";

    return numOpciones;
}

//FUNCION PARA GESTION DEL MENU PRINCIPAL
void menuPrincipal(SOCKET s, char sendBuff[512], char recvBuff[512],Usuario usuario) {
    logger(0,usuario.getNombreUsuario(),"ACCEDIENDO AL MENU PRINCIPAL");

    int salir=0;   
    std::cout << "Sesion iniciada por: " << usuario.getNombreUsuario() << std::endl;

    while (salir==0)
    {
        //OBTENEMOS LA OPCION SELECIONADA
        int opcion = selectOpcion(printMenuPrincipal()); 
        //DEPENDIENDO LA OPCION, ENTRAMOS EN LA FUNCION CORRESPONDIENTE.

        if(opcion==1) {
            std::cout << "Has seleccionado la opcion 1: Ver actividades." << std::endl;
            menuVerActividadesInicio(s,sendBuff,recvBuff,usuario);
            
            salir=1;
            break;
        } else if(opcion==2) {
            std::cout << "Has seleccionado la opcion 2: INSCRIBIR a ACTICIDAD." << std::endl;
            //menuPrincipal(usuario);
            salir=1;
            break;
        } else if(opcion==3) {
            std::cout << "Has seleccionado la opcion 3: BORRAR INSCRIPCION a ACTICIDAD." << std::endl;
            menuIncrbirse(s,sendBuff,recvBuff,usuario);     
            salir=1;
            break;
        } else if(opcion==4) {
            std::cout << "Has seleccionado la opcion 4: Valorar ACTIVIDAD." << std::endl;
            //menuInicio(usuario);
            salir=1;
            break;
        } else if(opcion==5) {
            std::cout << "Has seleccionado la opcion 5: PERFIL." << std::endl;
            std::cout << "Sesion iniciada por: " << usuario.toString() << std::endl;
            menuPerfil(s,sendBuff,recvBuff,usuario);
            salir=1;
            break;
        } else if(opcion==6) {
            std::cout << "Has seleccionado la opcion 6: VOLVER" << std::endl;
            menuInicio(s,sendBuff,recvBuff);
            salir=1;
            break;
        } else if(opcion==7) {
            std::cout << "VOLVER..." << std::endl;
            menuInicio(s,sendBuff,recvBuff);
            salir=1;
            break;
        } else {
            //SI LA OPCION NO ES VALIDA, ERROR.
            std::cout << "¡ERROR, SELECCIONE UN NUMERO VALIDO!" << std::endl;
            break;
        }
    }
}


//falta
int printMenuVerAct() {

    int numOpciones=4;

    std::cout << "\n||VER ACTIVIDADES||" << std::endl;
    std::cout << "_________________________________________________________" << std::endl;
    std::cout << "1.FILTRAR POR FECHA" << std::endl;
    std::cout << "2.FILTRAR POR PUBLICO" << std::endl;
    std::cout << "3.FILTRAR POR MEJOR VALORADAS" << std::endl;
    std::cout << "4.Volver" << std::endl;

    std::cout << "_________________________________________________________" << std::endl;
    return numOpciones;

}



//FUNCION PARA GESTION DEL MENU DE INICIO
void menuVerActividadesInicio(SOCKET s, char sendBuff[512], char recvBuff[512],Usuario usuario) {
     int salir=0;   
    while (salir==0)
    {
        int opcionesPosibles=printMenuVerAct (); 
        //obtenemos la opcion seleccionada
        int opcion = selectOpcion(opcionesPosibles);
        //dependiendo la seleccionada, entramos en INICIO DE SESION o SALIMOS
        if(opcion==1) {

                std::cout << "Has seleccionado la opcion 1: FILTRAR POR FECHA." << std::endl;

                char mensaje[512];
                sprintf(mensaje, "03$");
                send(s, mensaje, strlen(mensaje), 0);
                recv(s, recvBuff, 100000, 0);
                
                printf("ACTIVIDADES:\n %s", recvBuff);
                //std::vector<Actividad> actividades = strAActividades(recvBuff);
                //for ( auto& actividad : actividades) {
                   // std::cout << "Nombre: " << actividad.getNombreAct() << std::endl;

                //}
                menuVerActividadesInicio(s,sendBuff,recvBuff,usuario);
                salir=1;
                break;
                //PEDIMOS LAS ACTIVIDADES FILTRADAS POR FECHA (ORDENAR)
                
        }else if(opcion==2) {
                        
               std::cout << "Has seleccionado la opcion 2: FILTRAR POR PUBLICO." << std::endl;
               //PEDIMOS LAS ACTIVIDADES FILTRADAS POR PUBLICO (ORDENAR)
                char mensaje[512];
                sprintf(mensaje, "04$");
                send(s, mensaje, strlen(mensaje), 0);
                recv(s, recvBuff, 512, 0);
                salir=1;
                break;
        } 
        else if(opcion==3) {
                        
                std::cout << "Has seleccionado la opcion 3: FILTRAR POR MEJOR VALORADAS" << std::endl;
                //PEDIMOS LAS ACTIVIDADES MEJOR VALORADAS (PRIMERO ACCEDER A TABLA DE VALORACION
                // Y LAS ORDENAMOS, Y POR CADA UNA OBTENEMOS SU ID Y VAMOS A LA TABLA DE ACTVIDADES Y IMPRIMIMOS)
                char mensaje[512];
                sprintf(mensaje, "05$");
                send(s, mensaje, strlen(mensaje), 0);
                recv(s, recvBuff, 512, 0);
                salir=1;
                break;
                
        }

         else if(opcion==4) {
                        
                std::cout << "Volver..." << std::endl;
                salir=1;
                break;
        }  

        
        else {
            std::cout << "¡ERROR, SELECCIONE UN NUMERO!" << std::endl;
        }
    }
}



//FUNCION PARA MOSTRAR OPCIONES DE PERFIL
int printMenuPerfil() {
    int numOpciones = 2;
    std::cout << "\n||PERFIL||\n";
    std::cout << "_________________________________________________________\n";
    std::cout << "1. Ver INSCRIPCIONES\n";
    std::cout << "2. Ver datos de perfil\n";
    std::cout << "_________________________________________________________\n";
    return numOpciones;
}

//FUNCION PARA GESTION DEL MENU DE PERFIL
void menuPerfil(SOCKET s, char sendBuff[512], char recvBuff[512],Usuario usuario) {
    int salir = 0;

    while (salir == 0) {
        //OBTENEMOS LA OPCION SELECIONADA
        int opcion = selectOpcion(printMenuPerfil());
        //DEPENDIENDO LA OPCION, ENTRAMOS EN LA FUNCION CORRESPONDIENTE.

        if (opcion == 1) {
            std::cout << "Has seleccionado la opcion 1: Ver INSCRIPCIONES" << std::endl;
            //PEDIMOS INSCRIPCIONES DE ESE USUARIO 
            char mensaje[512];
            sprintf(mensaje, "0$");
            send(s, mensaje, strlen(mensaje), 0);
            recv(s, recvBuff, 512, 0);
            salir = 1;
            break;
        } else if (opcion == 2) {
            std::cout << "Has seleccionado la opcion 2: Ver datos de perfil" << std::endl;
            //LLAMAMOS AL FUNCION FRIEND, DE LA SOBRECARGA DEL OPERADOR >> CON EL USUARIO
            cout << usuario;
            menuPrincipal(s,sendBuff,recvBuff,usuario);
            salir = 1;
            break;
        } else {
            //SI LA OPCION NO ES VALIDA, ERROR.
            std::cout << "¡ERROR, SELECCIONE UN NUMERO VALIDO!" << std::endl;
        }
    }
}




//FUNCION PARA GESTION DEL MENU DE LOGIN


void menuLogin(SOCKET s, char sendBuff[512], char recvBuff[512]) {
    //guardamos espacio en memoria, ya que el usuario lo pasaremos por las funciones para el log
    int resultado;
    int salir = 0;

    //PEDIMOS LOS VALORES MIENTRAS NO SEAN CORRECTO

    while (salir == 0) {
        std::string nombre_usu;
        std::string usu_contra;

        std::cout << "Ingrese su nombre de usuario: ";
        std::getline(std::cin, nombre_usu);

        std::cout << "Ingrese su contrasena: ";
        std::getline(std::cin, usu_contra);

        //resultado = login(nombre_usu.c_str(), usu_contra.c_str());

        char mensaje[512]= {0};
        sprintf(mensaje, "02$%s$%s$", nombre_usu.c_str(), usu_contra.c_str());
        mensaje[strlen(mensaje)] = '$';

        // Enviamos el mensaje al servidor
        send(s, mensaje, strlen(mensaje), 0);


        // Recibimos la respuesta del servidor
        recv(s, recvBuff, 512, 0);
        

        
        printf("RESPUESTA:%c", recvBuff[0]);


        if (recvBuff[0] == '1') {
            //si son correctos, se inicia sesion
            Usuario usr = strAUsuario(recvBuff);
            printf("DATOS:  %s", recvBuff);
            std::cout << "Iniciando sesion..." << std::endl;
            menuPrincipal(s,sendBuff,recvBuff,usr);
            salir=1;
        
        } else {
                std::cout << "Introduce un usuario y contrasena correctos" << std::endl;;
        }
    }
}


void menuRegistrar(SOCKET s, char sendBuff[512], char recvBuff[512]) {
    Usuario u;

    std::cout << "Ingrese su nombre: ";
    char nombre[100];
    std::cin.getline(nombre, 100);
    u.setNombre(nombre);

    std::cout << "Ingrese su apellido: ";
    char apellido[100];
    std::cin.getline(apellido, 100);
    u.setApellido(apellido);

    std::cout << "Ingrese su nombre de usuario: ";
    char nombre_usu[100];
    std::cin.getline(nombre_usu, 100);
    u.setNombreUsuario(nombre_usu);

    std::cout << "Ingrese su contrasena: ";
    char contrasenya[100];
    std::cin.getline(contrasenya, 100);
    u.setContrasenya(contrasenya);

    char* str = u.toString();

    char mensaje[512];
    sprintf(mensaje, "01$%s$", str);
    send(s, mensaje, strlen(mensaje), 0);

    delete[] str;

    // esperar confirmación del servidor
    recv(s, recvBuff, 512, 0);
    if (recvBuff[0] == '1') {
        std::cout << "Usuario registrado con éxito.\n";
        menuInicio(s,sendBuff,recvBuff);
    } else {
        std::cout << "No se pudo registrar al usuario.\n";
        menuRegistrar(s,sendBuff,recvBuff);
    }
}


void menuIncrbirse(SOCKET s, char sendBuff[512], char recvBuff[512], Usuario usuario) {
    std::cout << "Introduzca el id de la actividad a la que quieras inscribirte\n";
    char idAct[100];
    std::cin.getline(idAct, 100);


    char mensaje[512];
    sprintf(mensaje, "06$%s$%s$", idAct, usuario.getId());
    send(s, mensaje, strlen(mensaje), 0);

}




//////////////////////////////////////////////////CODIGOS//////////////////////////////////////////////////////////////////////////////////////////////////

Usuario strAUsuario(char mensaje[512]) {
    Usuario usr;
    
    char copiaMensaje[512];
    strncpy(copiaMensaje, mensaje, sizeof(copiaMensaje));
    
    char* token = strtok(copiaMensaje, "$");

    token = strtok(nullptr, "$");

    int id = token ? atoi(token) : 0;
    usr.setId(id);

    token = strtok(nullptr, "$");

    char* nombre = const_cast<char*>(token ? token : "");
    token = strtok(nullptr, "$");

    char* apellido = const_cast<char*>(token ? token : "");
    token = strtok(nullptr, "$");

    char* nombre_usu = const_cast<char*>(token ? token : "");
    token = strtok(nullptr, "$");

    char* contrasenya = const_cast<char*>(token ? token : "");

    usr.setApellido(apellido);
    usr.setNombre(nombre);
    usr.setNombreUsuario(nombre_usu);
    usr.setContrasenya(contrasenya);
    
    return usr;
}


std::vector<Actividad> strAActividades( char* actividadesString) {
    std::vector<Actividad> listaActividades;
    char* copiaString = strdup(actividadesString); // Duplicar la cadena para evitar modificar la original

    // Tokenizar la cadena utilizando el delimitador "$"
    char* token = strtok(copiaString, "$");
    while (token != nullptr) {
        // Obtener cada atributo de la actividad
        char* nombre = token;
        char* descripcion = strtok(nullptr, "$");
        char* tipo = strtok(nullptr, "$");
        char* publico = strtok(nullptr, "$");
        char* municipio = strtok(nullptr, "$");
        char* direccion = strtok(nullptr, "$");
        char* encargado = strtok(nullptr, "$");
        char* fecha = strtok(nullptr, "$");

        // Crear un objeto Actividad con los atributos obtenidos y agregarlo a la lista
        Actividad actividad(nombre, descripcion, tipo, publico, municipio, direccion, encargado, fecha);
        listaActividades.push_back(actividad);

        // Obtener el siguiente token
        token = strtok(nullptr, "$");
    }

    free(copiaString); // Liberar la memoria asignada por strdup
    return listaActividades;
}




