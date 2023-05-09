#ifndef MENU_H
#define MENU_H
#define MAX_CHARACTERS_FOR_OPTIONS 3

#include <iostream>
#include <winsock2.h>
#include "../Clases/Usuario.h"
#include "../Codigos/gestionCodigos.h"


//FUNCION PARA DEVOLVER LA OPCION SELECCIONADA
int selectOpcion();

//FUNCION PARA IMPRIMIR EL MENU DE INICIO
int printMenuInicio();
//FUNCION PARA GESTION DEL MENU DE INICIO
void menuInicio(SOCKET s, char sendBuff[512], char recvBuff[512]);

//FUNCION PARA IMPRIMIR EL MENU PRINCIPAL
int printMenuPrincipal();
//FUNCION PARA GESTION DEL MENU PRINCIPAL
void menuPrincipal(std::string usuario);

//FUNCION PARA MOSTRAR OPCIONES DE PERFIL
int printMenuPerfil();
//FUNCION PARA GESTION DEL MENU DE PERFIL
void menuPerfil();

//FUNCION PARA MOSTRAR OPCIONES DE VER ACTIVIDADE
int printMenuVerAct();
//FUNCION PARA GESTION DEL MENU DE VER ACTIVIDADES
void menuVerActividades();

//FUNCION PARA MOSTRAR OPCIONES DE PERFIL
int printMenuLogin();
//FUNCION PARA GESTION DEL MENU DE LOGIN
void menuLogin(SOCKET s, char sendBuff[512], char recvBuff[512]);
//FUNCION PARA COMPROBAR SI LA OPCION INTRODUCIDA ES VALIDA
int comprobarOpcionValida(int opcion, int numOpciones);

void menuRegistrar(SOCKET s, char sendBuff[512], char recvBuff[512]);



#endif