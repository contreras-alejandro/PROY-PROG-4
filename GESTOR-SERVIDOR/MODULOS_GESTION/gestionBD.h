#ifndef GESTION_BD
#define GESTION_BD
#include "gestionServer.h"


//FUNCION PARA ABRIR BASE DE DATOS
int abrirConexion();
//FUNCION PARA CERRAR LA BASE DE DATOS
int cerrarConexion();
//FUNCION PARA LOGIN DEL ADMIN
int loginAdmin(char* admin, char* contrasena);
//FUNCION PARA INSERTAR ADMIN EN BASE DE DATOS
void insertarAdmin(char *admin,Administrador* admininistrador);
//FUNCION PARA BUSCAR ACTIVIDD POR ID EN BASE DE DATOS
Actividad buscarActividadPorId(int id,char *admin);
//FUNCION PARA INSERTAR ACTIVIDAD EN BASE DE DATOS
void insertarActividad(char *admin, Actividad act);
//FUNCION PARA MOSTRAR LAS ACTIVIDADES DE LA BASE DE DATOS
void verActividades(char *admin);
//FUNCION PARA ELIMINAR ACTIVIDAD DE BASE DE DATOS
void eliminarAct(int id,char *admin);
//FUNCION PARA SUBIR UNA ACTIVIDAD MODIFICADA A BASE DE DATOS
void subirActModificada(int id, Actividad act,char *admin);
//FUNCION PARA ELIMINAR TODAS LAS ACTIVIDADES DE BASE DE DATOS (NO LA TABLA!)
void eliminarTablaActividades(char *admin);
//FUNCION PARA COMBROBAR QUE UN NOMBRE DE USUARIO NO EXISTE EN BASE DE DATOS (EVITAR REPETIDOS)
int comprobarUsuarioAdmin(char * usrAdmin);
//FUNCION PARA COMPROBAR QUE LA ACTIVIDAD A ELIMINAR EXISTE EN BASE DE DATOS
int comprobarActividad(int id,char * admin);

////////////////////////////////////// CLIENTES /////////////////////////////////////////////////////////////

//REGISTRAR USUARIO
void registrarUsuario(Usuario u);
//LOG IN DE USUARIO (QUE DEVUELVA EL USUARIO COMO OBJETO)
Usuario* loginUsuario(char* usuario, char* contrasena);

//VER ACTIVIDADES CON FILTR0 (RECIBE UN INT, QUE DEPENDE CUAL SEA SERA UNA CONSULTA O OTRA)

// INSCIRBIR A ACTIVIDAD (INT ID_USU, INT ID_ACT)
void insertarInscripcionActividad(int idAct, int idUsu);
//COMPROBAR INSCRIPCION (INT ID_USU, INT ID_ACT) PARA COMPRAR SI ESTABA SUSCRITO
////// IMPORTANTE, MIRAR SI YA HA PASADO O NO

//ELIMINAR INSCRIPCION
void eliminarInscripcion(int idAct, int id_usu);

//COMPROBAR PARTICIPACION(INT ID_USU, INT ID_ACT)  PARA COMPROBAR SI PUEDE VALORAR ESA ACTIVIDAD , SOLO SI HA PARTICIPADO
int comprobarInscripcionValorar(int id_act, int id_usu);
//VALORACION INSCR (INT ID_USU, INT ID_ACT , INT NOTA)
void insertarValoracionActividad(int idAct, int idUsu, float valoracion);


#endif
