#ifndef GESTION_BD
#define GESTION_BD
#include "gestionAdmin.h"



int abrirConexion();
int cerrarConexion();
int login(char* usuario, char* contrasena);
void insertarAdmin(char *usuario,Administrador admin);
void insertarActividad(char *usuario,Actividad act);
void verActividades();
void eliminarAct(int id);
void subirCambio(int id,Actividad act);

#endif