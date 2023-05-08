#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestionServer.h"
#include "../sqlite/sqlite3.h"
#include "gestionBD.h"
#include <time.h>

sqlite3* db;


//FUNCION PARA ABRIR BASE DE DATOS
int abrirConexion() {
   
    int resultado_apertura;

    //OBTENEMOS EL NOMBRE DE LA BASE DE DATOS
    char *nombre_base = leerProperties(2);

    resultado_apertura = sqlite3_open(nombre_base, &db);

    //si el valor es 0, todo bien! sino, error en apertura

    if (resultado_apertura != SQLITE_OK) {
       printf("Error al abrir la base de datos");
        sqlite3_close(db);
        return 1;
    } else {
        return 0;
    }
}

//FUNCION PARA CERRAR LA BASE DE DATOS
int cerrarConexion()  {
    
    int rc;
    rc = sqlite3_close(db);
    if (rc) {
        printf("No se pudo cerrar la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    return 0;
}


//FUNCION PARA BUSCAR ACTIVIDD POR ID EN BASE DE DATOS
Actividad buscarActividadPorId(int id,char *admin) {
    abrirConexion();
    sqlite3_stmt *stmt;
    char sql[100];
    int rc;

    Actividad actividad = {0};

    sprintf(sql, "SELECT * FROM ACTIVIDAD WHERE ID_ACT=%d", id);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return actividad;
    }

    //EJECUTAMOS SENTENCIA
    rc = sqlite3_step(stmt);
    //SI EXISTE, CREAMOS ACTIVIDAD
    if (rc == SQLITE_ROW) {
        strcpy(actividad.nombre, sqlite3_column_text(stmt, 1));
        strcpy(actividad.descripcion, sqlite3_column_text(stmt, 2));
        strcpy(actividad.tipo, sqlite3_column_text(stmt, 3));
        strcpy(actividad.publico, sqlite3_column_text(stmt, 4));
        strcpy(actividad.municipio, sqlite3_column_text(stmt, 5));
        strcpy(actividad.direccion, sqlite3_column_text(stmt, 6));
        strcpy(actividad.encargado, sqlite3_column_text(stmt, 7));
        strcpy(actividad.fecha, sqlite3_column_text(stmt, 8));
    }

    char mensaje[50];
    sprintf(mensaje, "ACTIVIDAD ENCONTRDA CON ID %i", id);
    logger(0,admin,mensaje);
    sqlite3_finalize(stmt);
    cerrarConexion();

    printf("La actividad buscada es:\n");
    //IMPRIMIMOS LA ACTIVIDAD ( A MODO DE RESUMEN)
    imprimirActividad(actividad);
    return actividad;
}




//METODO PARA COMPROBAR SI UN NOMBRE DE USUARIO ESTA YA UTILIZADO

int comprobarUsuario(char * usr) {
    int resultado_consulta;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* consulta = "SELECT * FROM USUARIO WHERE USUARIO_USU = ?";

    resultado_consulta = sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);

    if (resultado_consulta != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        cerrarConexion();
        return -1;
    }

    sqlite3_bind_text(stmt, 1, usr, strlen(usr), SQLITE_STATIC);
    //EJECUTAMOS CONSULTA
    resultado_consulta = sqlite3_step(stmt);

    //SI EXISTE, DEVOLVEMOD UN 1, SINO, OTRO VALOR

    if (resultado_consulta == SQLITE_ROW) {
        //EXISTE ESTE USUARIO
        sqlite3_finalize(stmt);
        cerrarConexion();
        return 1;
    
    } else if (resultado_consulta == SQLITE_ERROR) {
        //ERROR EN CONSULTA
        printf("Error en la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        cerrarConexion();
        return -1;
    } else {
        sqlite3_finalize(stmt);
        cerrarConexion();
        return 0;
}

}

//FUNCION PARA MOSTRAR LAS ACTIVIDADES DE LA BASE DE DATOS
void verActividades(char *admin){


    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "SELECT * FROM ACTIVIDAD";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return;
    }

    //NOMBRES DE COLUMNAS
    printf("%-7s %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n", "ID_ACT", "NOMBRE_ACT", "TIPO_DE_ACTIVIDAD", "PUBLICO", "MUNICIPIO", "DIRECCION", "ENCARGADO", "FECHA_ACT");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id_act = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre_act = sqlite3_column_text(stmt, 1);
        //const unsigned char* descripcion = sqlite3_column_text(stmt, 2);
        const unsigned char* tipo_de_actividad = sqlite3_column_text(stmt, 3);
        const unsigned char* publico = sqlite3_column_text(stmt, 4);
        const unsigned char* municipio = sqlite3_column_text(stmt, 5);
        const unsigned char* direccion = sqlite3_column_text(stmt, 6);
        const unsigned char* encargado = sqlite3_column_text(stmt, 7);
        const unsigned char* fecha_act = sqlite3_column_text(stmt, 8);
        //MOSTRAMOS LOS ATRIBUTOS DE CADA ACTIVIDAD
  
      printf("%-7d %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n", id_act, nombre_act, tipo_de_actividad, publico, municipio, direccion, encargado, fecha_act);
      printf("\n\n");
    
    }   

    
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }



    sqlite3_finalize(stmt);
    cerrarConexion();
    return;
}

int comprobarActividad(int id, char * usu){
    abrirConexion();
    sqlite3_stmt *stmt;
    int resulQ;
    int result = 0;

    char* sql =  "SELECT ID_ACT FROM ACTIVIDAD WHERE ID_ACT = ?";
    resulQ = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
     if (resulQ != SQLITE_OK) {
        printf("No se puede preparar la consulta");
        cerrarConexion();
        return 0;
     }

    sqlite3_bind_int(stmt, 1, id);
    resulQ=sqlite3_step(stmt);
    if (resulQ == SQLITE_ROW) { // se ha encontrado una fila con el id
        result = 1;
    }
    sqlite3_finalize(stmt);
    cerrarConexion();
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////



void registrarUsuario(Usuario u ) {
    int rc;

    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "INSERT INTO USUARIO (NOMBRE_USU, APELLIDO_USU, USUARIO_USU, CONTRASENYA_USU) VALUES (?, ?, ?, ?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        return;
    }

    sqlite3_bind_text(stmt, 1, u.nombre, strlen(u.nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, u.apellido, strlen(u.apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, u.nusuario, strlen(u.nusuario), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, u.contrasenya, strlen(u.contrasenya), SQLITE_STATIC);
    
    //EJECUTAMOS SENTENCIA.
     rc = sqlite3_step(stmt);
    //ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
     //TODO HA IDO BIEN, INSERTADO.
    //VA TODO BIEN 
    printf("VALORES INSERTADOS!!\n");
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    //LIBERAMOS ESPACIO EN MEMORIA DEL ADMIN!
    //liberarAdmin(admininistrador);
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;











}





Usuario* loginUsuario(char* usuario, char* contrasena){
    abrirConexion();
    int resultado_consulta;
    sqlite3_stmt *stmt;
    char* consulta = "SELECT * FROM USUARIO WHERE USUARIO_USU = ? AND CONTRASENYA_USU = ?;";

    //OBTENEMOS EL VALOR DE LA CONTRASENYA HASHEADA
    char* contrasenya_hasheada = hash_string(contrasena);
   
    resultado_consulta = sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);

    if (resultado_consulta != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        cerrarConexion();
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, contrasenya_hasheada, strlen(contrasenya_hasheada), SQLITE_STATIC);

    //EJECUTAMOS SENTENCIA SQL

    resultado_consulta = sqlite3_step(stmt);

    //SI EL USUARIO EXISTE, DEVOLVEMOS UN 1, SINO, OTRO VALOR

    Usuario* usr = malloc(sizeof(Usuario)); // Aquí creamos un puntero a Usuario y asignamos memoria dinámica

    if (resultado_consulta == SQLITE_ROW) {
        printf("Nombre de usuario y contrasena correctas\n");
        
        strcpy(usr->nombre, sqlite3_column_text(stmt, 2));
        strcpy(usr->apellido, sqlite3_column_text(stmt, 3));
        strcpy(usr->nusuario, sqlite3_column_text(stmt, 4));
        strcpy(usr->contrasenya, sqlite3_column_text(stmt, 5));

        
        sqlite3_finalize(stmt);
        cerrarConexion();
        return usr; // Devolvemos el puntero que hemos creado
    } else if (resultado_consulta == SQLITE_ERROR) {
        //EN CASO DE ERROR, DEVUELVE -1
        printf("Error en la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        cerrarConexion();
        free(usr); // En caso de error, liberamos la memoria dinámica
        return NULL;
    } else {
        printf("Credenciales incorrectas\n");
        sqlite3_finalize(stmt);
        cerrarConexion();
        free(usr); // Si las credenciales son incorrectas, liberamos la memoria dinámica
        return NULL;
    }
}

//FUNCION PARA INSERTAR VALORACION ACTIVIDAD EN BASE DE DATOS
void insertarInscrSipcionActividad(int idAct, int idUsu){

    int rc;

    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "INSERT INTO INSCRIPCION (ID_USU,ID_ACT) VALUES (?, ?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        return;
    }

    sqlite3_bind_int(stmt, 1,idUsu);
    sqlite3_bind_int(stmt, 2,idAct);
    //EJECUTAMOS SENTENCIA.
     rc = sqlite3_step(stmt);
    //ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
     //TODO HA IDO BIEN, INSERTADO.
    //VA TODO BIEN 
    printf("INSCRIPCION INSERTADO!!\n");
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    //LIBERAMOS ESPACIO EN MEMORIA DEL ADMIN!
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;




}


void insertarValoracionActividad(int idAct, int idUsu, float valoracion) {



    int rc;

    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "INSERT INTO VALORACION (ID_USU,ID_ACT,VALORACION) VALUES (?, ?, ?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        return;
    }

    sqlite3_bind_int(stmt, 1,idUsu);
    sqlite3_bind_int(stmt, 2,idAct);
     sqlite3_bind_int(stmt, 3,valoracion);
    //EJECUTAMOS SENTENCIA.
     rc = sqlite3_step(stmt);
    //ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
     //TODO HA IDO BIEN, INSERTADO.
    //VA TODO BIEN 
    printf("VALORACION INSERTADA!!\n");
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;










}


//FUNCION PARA ELIMINAR INSCRIPCION A UNA ACTIVIDAD
void eliminarInscripcion(int idAct, int id_usu) {

    
    int rc;

    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "DELETE * FROM INSCRIPCION WHERE ID_USU = ? AND ID_ACT = ?";
;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        return;
    }

    sqlite3_bind_int(stmt, 1,id_usu);
    sqlite3_bind_int(stmt, 2,idAct);
    //EJECUTAMOS SENTENCIA.
     rc = sqlite3_step(stmt);
    //ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
     //TODO HA IDO BIEN, INSERTADO.
    //VA TODO BIEN 
    printf("INSCRIPCION INSERTADO!!\n");
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;




}

//FUNCION PREVIA A VALORAR UNA ACTIVIDAD

// - TIENE QUE HABERSE REALIZADO LA ACTIVIDAD
// - EL USUARIO TIENE QUE HABER PARTICIPADO


//DEVUELVE 1, SI SE PUEDE VALORAR, 0 EN CUALQUIER OTRO CASO QUE INDIQUE QUE NO.

int comprobarInscripcionValorar(int id_act, int id_usu) {

 abrirConexion();
    sqlite3_stmt *stmt;
    int resulQ;
    int result = 0;

    // Primero, comprobamos si la actividad ya se ha realizado
    char* sql_act = "SELECT FECHA_ACT FROM ACTIVIDAD WHERE ID_ACT = ?";
    resulQ = sqlite3_prepare_v2(db, sql_act, -1, &stmt, NULL);
    if (resulQ != SQLITE_OK) {
        printf("No se puede preparar la consulta");
        cerrarConexion();
        return 0;
    }
    sqlite3_bind_int(stmt, 1, id_act);
    //EJECUTAMOS SENTENCIA
    resulQ = sqlite3_step(stmt);
    if (resulQ == SQLITE_ROW) {
        //EXISTE ESA ACTIVIDAD

        // Comprobamos si la fecha de la actividad es anterior a la fecha actual
        const char* fecha_str = (const char*) sqlite3_column_text(stmt, 0);
        time_t fecha_act = strtotime(fecha_str);
        //obtenemos la actual
        time_t fecha_actual = time(NULL);
        //comparamos
        if (fecha_act < fecha_actual) {
            // La actividad ya se ha realizado,
            //BUSCAMOS SI EXISTE ESA INSCRIPCION
            char* sql_ins = "SELECT ID_USU FROM INSCRIPCION WHERE ID_USU = ? AND ID_ACT = ?";
            resulQ = sqlite3_prepare_v2(db, sql_ins, -1, &stmt, NULL);
            if (resulQ != SQLITE_OK) {
                printf("No se puede preparar la consulta");
                sqlite3_finalize(stmt);
                cerrarConexion();
                return 0;
            }
            sqlite3_bind_int(stmt, 1, id_usu);
            sqlite3_bind_int(stmt, 2, id_act);
            resulQ = sqlite3_step(stmt);
            if (resulQ == SQLITE_ROW) {
                //EXISTE, DEVOLVEMOS 1
                result = 1;
            }
            else {

                //NO EXISTE INSCRIPCION DE ESE USUARIO
                printf("NO EXISTE INSCRIPCION DEL USUARIO A ESA ACTIVIDAD:\n");
                return 0;
            }
            sqlite3_finalize(stmt);
        }else {
            //LA FECHA INDICA, QUE TODAVIA NO SE HA REALIZADO
             printf(" LA ACTIVIDAD AUN NO SE HA REALIZADO:\n");
             return 0;
        }
    }
    cerrarConexion();
    return result;



}























