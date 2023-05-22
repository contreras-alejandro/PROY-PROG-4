#ifndef GESTION_BD
#define GESTION_BD
#include "gestionServer.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//FUNCION PARA ABRIR BASE DE DATOS
int abrirConexion();
//FUNCION PARA CERRAR LA BASE DE DATOS
int cerrarConexion();
//FUNCION PARA BUSCAR ACTIVIDD POR ID EN BASE DE DATOS
Actividad* buscarActividadPorId(int id);
//FUNCION PARA MOSTRAR LAS ACTIVIDADES DE LA BASE DE DATOS
void verActividades(char *admin);
//FUNCION PARA COMBROBAR QUE UN NOMBRE DE USUARIO NO EXISTE EN BASE DE DATOS (EVITAR REPETIDOS)
int comprobarUsuario(char * usr);
//FUNCION PARA COMPROBAR QUE LA ACTIVIDAD A EXISTE EN BASE DE DATOS
int comprobarActividad(int id,char * usu);

////////////////////////////////////// CLIENTES /////////////////////////////////////////////////////////////

//REGISTRAR USUARIO
void registrarUsuario(Usuario u);
//LOG IN DE USUARIO (QUE DEVUELVA EL USUARIO COMO OBJETO)
Usuario* loginUsuario(char* usuario, char* contrasena);

//VER ACTIVIDADES CON FILTR0 (RECIBE UN INT, QUE DEPENDE CUAL SEA SERA UNA CONSULTA O OTRA)
void verActividadesFecha();

// INSCIRBIR A ACTIVIDAD (INT ID_USU, INT ID_ACT)
int insertarInscrSipcionActividad(char* idAct, char* id_usu);
//COMPROBAR INSCRIPCION (INT ID_USU, INT ID_ACT) PARA COMPRAR SI ESTABA SUSCRITO
////// IMPORTANTE, MIRAR SI YA HA PASADO O NO

//ELIMINAR INSCRIPCION
int eliminarInscripcion(char* idAct, char* id_usu);

//COMPROBAR PARTICIPACION(INT ID_USU, INT ID_ACT)  PARA COMPROBAR SI PUEDE VALORAR ESA ACTIVIDAD , SOLO SI HA PARTICIPADO
int comprobarInscripcionValorar(char* id_act, char* id_usu);

//VALORACION INSCR (INT ID_USU, INT ID_ACT , INT NOTA)
int insertarValoracionActividad(char* idAct, char* idUsu, double valoracion);

char* obtenerActividadesFecha();

char* obtenerActividadesTodas();

char* obtenerActividadesMejor();

char* obtenerInscripciones(char* id_usu);




#endif
