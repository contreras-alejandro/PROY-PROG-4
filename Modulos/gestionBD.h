#ifndef GESTION_BD
#define GESTION_BD
#include "gestionAdmin.h"



int abrirConexion();
int cerrarConexion();
int login(char* usuario, char* contrasena);
void insertarAdmin(char *usuario,Administrador admin);


#endif