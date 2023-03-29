#ifndef GESTION_BD
#define GESTION_BD
#include "gestionAdmin.h"



int abrirConexion();
int cerrarConexion();
int login(char* usuario, char* contrasena);
void insertarAdmin(char *usuario,Administrador admin);
Actividad buscarActividadPorId(int id,char *usuario);
void insertarActividad(char *usuario, Actividad act);
void verActividades(char *usuario);
void eliminarAct(int id,char *usuario);
void subirActModificada(int id, Actividad act,char *usuario);
void eliminarTablaActividades(char *usuario);
int comprobarUsuario(char * nombreUsuario);

#endif
