#ifndef GESTION_BD
#define GESTION_BD
#include "gestionAdmin.h"


//FUNCION PARA ABRIR BASE DE DATOS
int abrirConexion();
//FUNCION PARA CERRAR LA BASE DE DATOS
int cerrarConexion();
//FUNCION PARA LOGIN DEL ADMIN
int login(char* usuario, char* contrasena);
//FUNCION PARA INSERTAR ADMIN EN BASE DE DATOS
void insertarAdmin(char *usuario,Administrador* admin);
//FUNCION PARA BUSCAR ACTIVIDD POR ID EN BASE DE DATOS
Actividad buscarActividadPorId(int id,char *usuario);
//FUNCION PARA INSERTAR ACTIVIDAD EN BASE DE DATOS
void insertarActividad(char *usuario, Actividad act);
//FUNCION PARA MOSTRAR LAS ACTIVIDADES DE LA BASE DE DATOS
void verActividades(char *usuario);
//FUNCION PARA ELIMINAR ACTIVIDAD DE BASE DE DATOS
void eliminarAct(int id,char *usuario);
//FUNCION PARA SUBIR UNA ACTIVIDAD MODIFICADA A BASE DE DATOS
void subirActModificada(int id, Actividad act,char *usuario);
//FUNCION PARA ELIMINAR TODAS LAS ACTIVIDADES DE BASE DE DATOS (NO LA TABLA!)
void eliminarTablaActividades(char *usuario);
//FUNCION PARA COMBROBAR QUE UN NOMBRE DE USUARIO NO EXISTE EN BASE DE DATOS (EVITAR REPETIDOS)
int comprobarUsuario(char * nombreUsuario);
//FUNCION PARA COMPROBAR QUE LA ACTIVIDAD A ELIMINAR EXISTE EN BASE DE DATOS
int comprobarActividad(int id,char * nombreUsuario);

////////////////////////////////////// CLIENTES /////////////////////////////////////////////////////////////

//REGISTRAR USUARIO
//LOG IN DE USUARIO (QUE DEVUELVA EL USUARIO COMO OBJETO)
Usuario* loginUsuario(char* usuario, char* contrasena);

//VER ACTIVIDADES CON FILTR0 (RECIBE UN INT, QUE DEPENDE CUAL SEA SERA UNA CONSULTA O OTRA)

// INSCIRBIR ACTIVIDAD (INT ID_USU, INT ID_ACT)

//COMPROBAR INSCRIPCION (INT ID_USU, INT ID_ACT) PARA COMPRAR SI ESTABA SUSCRITO
//ELIMINAR INSCR (INT ID_USU, INT ID_ACT)


//COMPROBAR PARTICIPACION(INT ID_USU, INT ID_ACT)  PARA COMPROBAR SI PUEDE VALORAR ESA ACTIVIDAD , SOLO SI HA PARTICIPADO
//VALORACION INSCR (INT ID_USU, INT ID_ACT , INT NOTA)










#endif
