#ifndef GESTION_BD
#define GESTION_BD
#include "gestionAdmin.h"



int abrirConexion();
int cerrarConexion();
int login(char* usuario, char* contrasena);
void insertarAdmin(char *usuario,Administrador admin);
Actividad buscarActividadPorId(int id);
void insertarActividad(char *usuario, Actividad act);
void verActividades();
void eliminarAct(int id);
void subirActModificada(int id, Actividad act);

#endif
