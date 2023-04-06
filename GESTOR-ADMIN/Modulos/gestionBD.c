#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestionAdmin.h"
#include "../sqlite/sqlite3.h"
#include "gestionBD.h"
#include "gestionAdmin.h"

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


//FUNCION PARA LOGIN DEL USUARIO
int login(char* usuario, char* contrasena) {
    abrirConexion();
    int resultado_consulta;
    sqlite3_stmt *stmt;
    char* consulta = "SELECT * FROM ADMIN WHERE USUARIO_ADMIN = ? AND CONTRASENYA_ADMIN = ?;";

    //OBTENEMOS EL VALOR DE LA CONTRASENYA HASHEADA
    char* contrasenya_hasheada = hash_string(contrasena);
   

    resultado_consulta = sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);

    if (resultado_consulta != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        cerrarConexion();
        return -1;
    }

    sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, contrasenya_hasheada, strlen(contrasenya_hasheada), SQLITE_STATIC);

    //EJECUTAMOS SENTENCIA SQL

    resultado_consulta = sqlite3_step(stmt);

    //SI EL USUARIO EXISTE, DEVOLVEMOS UN 1, SINO, OTRO VALOR

    if (resultado_consulta == SQLITE_ROW) {
        printf("Nombre de usuario y contrasena correctas\n");
        sqlite3_finalize(stmt);
        cerrarConexion();
        return 1;
    } else if (resultado_consulta == SQLITE_ERROR) {
        //EN CASO DE ERROR, DEVUELVE -1
        printf("Error en la consulta: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        cerrarConexion();
        return -1;
    } else {
        printf("Credenciales incorrectas\n");
        sqlite3_finalize(stmt);
        cerrarConexion();
        return 0;
    }


}

//FUNCION PARA BUSCAR ACTIVIDD POR ID EN BASE DE DATOS
Actividad buscarActividadPorId(int id,char *usuario) {
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
    logger(0,usuario,mensaje);
    sqlite3_finalize(stmt);
    cerrarConexion();

    printf("La actividad buscada es:\n");
    //IMPRIMIMOS LA ACTIVIDAD ( A MODO DE RESUMEN)
    imprimirActividad(actividad);
    return actividad;
}




//METODO PARA COMPROBAR SI UN NOMBRE DE USUARIO ESTA YA UTILIZADO

int comprobarUsuario(char * nombreUsuario) {
    int resultado_consulta;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* consulta = "SELECT * FROM ADMIN WHERE USUARIO_ADMIN = ?";

    resultado_consulta = sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);

    if (resultado_consulta != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        cerrarConexion();
        return -1;
    }

    sqlite3_bind_text(stmt, 1, nombreUsuario, strlen(nombreUsuario), SQLITE_STATIC);
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


//METODO PARA INSERTAR ADMINISTRADOR EN BD
void insertarAdmin(char *usuario,Administrador* admin) {
    int rc;

    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "INSERT INTO ADMIN (NOMBRE_ADMIN, APELLIDO_ADMIN, USUARIO_ADMIN, CONTRASENYA_ADMIN) VALUES (?, ?, ?, ?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        logger(2,usuario,"ERROR AL PREPARAR CONSULTA");  
        return;
    }

    sqlite3_bind_text(stmt, 1, admin->nombre, strlen(admin->nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, admin->apellido, strlen(admin->apellido), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, admin->nusuario, strlen(admin->nusuario), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, admin->contrasenya, strlen(admin->contrasenya), SQLITE_STATIC);
    
    //EJECUTAMOS SENTENCIA.
     rc = sqlite3_step(stmt);
    //ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        logger(2,usuario,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
     //TODO HA IDO BIEN, INSERTADO.
    //VA TODO BIEN 
    printf("VALORES INSERTADOS!!\n");
    logger(1,usuario, "HA INSERTADO UN NUEVO ADMIN");
    //LIBERAMOS ESPACIO EN MEMORIA DEL ADMIN!
    liberarAdmin(admin);
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;
}





//FUNCION PARA INSERTAR ACTIVIDAD EN BASE DE DATOS
void insertarActividad(char *usuario,Actividad act) {
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "INSERT INTO ACTIVIDAD (NOMBRE_ACT, DESCRIPCION, TIPO_DE_ACTIVIDAD,PUBLICO,MUNICIPIO,DIRECCION,ENCARGADO,FECHA_ACT) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";

    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        logger(2,usuario,"ERROR AL PREPARAR CONSULTA");  
        return;
    }

    sqlite3_bind_text(stmt, 1, act.nombre, strlen(act.nombre), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, act.descripcion, strlen(act.descripcion), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, act.tipo, strlen(act.tipo), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, act.publico, strlen(act.publico), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, act.municipio, strlen(act.municipio), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, act.direccion, strlen(act.direccion), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, act.encargado, strlen(act.encargado), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, act.fecha, strlen(act.fecha), SQLITE_STATIC);

    //EJECUTAMOS SENTENCIA
     rc = sqlite3_step(stmt);
    
    //ERROR A LA HORA DE INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        logger(2,usuario,"ERROR AL EJECUTAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    //SI LLEGAMOS AQUI, SE HA INSERTADO CORRECTAMENTE
     char mensaje[100];
    sprintf(mensaje, "HA INSERTADO UNA NUEVA ACTIVIDAD! NOMBRE =  %s", act.nombre);
    logger(1,usuario, mensaje);
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;
}


//FUNCION PARA MOSTRAR LAS ACTIVIDADES DE LA BASE DE DATOS
void verActividades(char *usuario){


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

//FUNCION PARA ELIMINAR ACTIVIDAD DE BASE DE DATOS
void eliminarAct(int id,char *usuario){

    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char sql[100];


    sprintf(sql, "DELETE FROM ACTIVIDAD WHERE ID_ACT = %d", id);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    //EJECUTAMOS SENTENCIA

    rc = sqlite3_step(stmt);

     //ELIMINADA CON EXITO
    if (rc == SQLITE_DONE) {
        printf("Actividad eliminada con exito\n");
        char mensaje[50];
        sprintf(mensaje, "Eliminada la actividad con ID %i", id);
        logger(1, usuario,mensaje);
    } else {
        printf("No se encontro ninguna actividad con ese ID\n");
    }
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;
}


void subirActModificada(int id, Actividad act,char *usuario){
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char sql[200];
    sprintf(sql,"UPDATE ACTIVIDAD SET NOMBRE_ACT=?, DESCRIPCION=?, TIPO_DE_ACTIVIDAD=?, PUBLICO=?, MUNICIPIO=?, DIRECCION=?, ENCARGADO=?, FECHA_ACT=? WHERE ID_ACT=%d", id);


    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return;
    }

    sqlite3_bind_text(stmt, 1, act.nombre, strlen(act.nombre), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, act.descripcion, strlen(act.descripcion), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, act.tipo, strlen(act.tipo), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, act.publico, strlen(act.publico), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, act.municipio, strlen(act.municipio), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, act.direccion, strlen(act.direccion), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, act.encargado, strlen(act.encargado), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, act.fecha, strlen(act.fecha), SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);



    if (rc == SQLITE_DONE) {
        printf("Actividad modificada con exito\n");
    } else {
        printf("No se encontro ninguna actividad con ese ID\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    cerrarConexion();
    return;
}


void eliminarTablaActividades(char *usuario){
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "DELETE FROM ACTIVIDAD";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    rc = sqlite3_step(stmt);
    printf("\nELIMINANDO ACTIVIDADES DE BASE DE DATOS...\n");
    printf("ELIMINADAS CON EXITO!\n");
    logger(1,usuario,"ELIMINADO TODAS LAS ACTIVIDADES DE LA BD ");  

    sqlite3_finalize(stmt);
    cerrarConexion();


}

int comprobarActividad(int id, char * nombreUsuario){
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
