#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestionServer.h"
#include "../sqlite/sqlite3.h"
#include "gestionBD.h"


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


//FUNCION PARA BUSCAR ACTIVIDAD POR ID EN BASE DE DATOS
Actividad* buscarActividadPorId(int id) {
    abrirConexion();
    sqlite3_stmt *stmt;
    char sql[100];
    int rc;

     Actividad* actividad = (Actividad*) malloc(sizeof(Actividad));

    sprintf(sql, "SELECT * FROM ACTIVIDAD WHERE ID_ACT=%d", id);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return NULL;
    }

    //EJECUTAMOS SENTENCIA
    rc = sqlite3_step(stmt);
    //SI EXISTE, CREAMOS ACTIVIDAD
    if (rc == SQLITE_ROW) {
        strcpy(actividad->nombre, sqlite3_column_text(stmt, 1));
        strcpy(actividad->descripcion, sqlite3_column_text(stmt, 2));
        strcpy(actividad->tipo, sqlite3_column_text(stmt, 3));
        strcpy(actividad->publico, sqlite3_column_text(stmt, 4));
        strcpy(actividad->municipio, sqlite3_column_text(stmt, 5));
        strcpy(actividad->direccion, sqlite3_column_text(stmt, 6));
        strcpy(actividad->encargado, sqlite3_column_text(stmt, 7));
        strcpy(actividad->fecha, sqlite3_column_text(stmt, 8));
    }
    else{
        //NO EXISTE!
        return NULL;
    }

    char mensaje[50];
    sprintf(mensaje, "ACTIVIDAD ENCONTRDA CON ID %i", id);
    //logger(0,admin,mensaje);
    sqlite3_finalize(stmt);
    cerrarConexion();
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
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    //LIBERAMOS ESPACIO EN MEMORIA DEL ADMIN!
    //liberarAdmin(admininistrador);
    sqlite3_finalize(stmt);
    cerrarConexion();
    return;











}





Usuario* loginUsuario(char* usuario, char* contrasena) {
    abrirConexion();
    int resultado_consulta;
    sqlite3_stmt *stmt;
    char* consulta = "SELECT * FROM USUARIO WHERE USUARIO_USU = ? AND CONTRASENYA_USU = ?;";

    // OBTENEMOS EL VALOR DE LA CONTRASEÑA HASHEADA
   
    resultado_consulta = sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);

    if (resultado_consulta != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        cerrarConexion();
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, contrasena, strlen(contrasena), SQLITE_STATIC);

    // EJECUTAMOS SENTENCIA SQL

    resultado_consulta = sqlite3_step(stmt);

    // SI EL USUARIO EXISTE, DEVOLVEMOS UN 1, SINO, OTRO VALOR

    Usuario* usr = (Usuario*) malloc(sizeof(Usuario)); // Aquí creamos un puntero a Usuario y asignamos memoria dinámica

    if (resultado_consulta == SQLITE_ROW) {
       

        // OBTENEMOS EL VALOR DEL ID

        
        const unsigned char* idU = sqlite3_column_text(stmt, 0);
        usr->id = malloc(strlen(idU) + 1);
        strcpy(usr->id, idU);

        // ASIGNAMOS LOS DEMÁS CAMPOS

        const unsigned char* nombreA = sqlite3_column_text(stmt, 1);
        usr->nombre = malloc(strlen(nombreA) + 1);
        strcpy(usr->nombre, nombreA);

        const unsigned char* apellidoA = sqlite3_column_text(stmt, 2);
        usr->apellido = malloc(strlen(apellidoA) + 1);
        strcpy(usr->apellido, apellidoA);

        usr->nusuario = malloc(strlen(usuario) + 1);
        strcpy(usr->nusuario, usuario);

        usr->contrasenya = malloc(strlen(contrasena) + 1);
        strcpy(usr->contrasenya, contrasena);

        sqlite3_finalize(stmt);
        cerrarConexion();
        return usr; // Devolvemos el puntero que hemos creado
    } else if (resultado_consulta == SQLITE_ERROR) {
        // EN CASO DE ERROR, DEVUELVE -1
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
int insertarInscrSipcionActividad(char* idAct, char* id_usu){

    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    const char* sql = "INSERT INTO INSCRIPCION (ID_USU,ID_ACT) VALUES (?, ?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        return 0;
    }

    sqlite3_bind_text(stmt, 1, id_usu, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, idAct, -1, SQLITE_STATIC);
    // EJECUTAMOS SENTENCIA.
    rc = sqlite3_step(stmt);
    // ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    // TODO HA IDO BIEN, INSERTADO.
    // VA TODO BIEN 
    
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    sqlite3_finalize(stmt);
    cerrarConexion();
    return 1;




}


int insertarValoracionActividad(char* idAct, char* idUsu, double valoracion) {



    int rc;

    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "INSERT INTO VALORACION (ID_USU,ID_ACT,VALORACION) VALUES (?, ?, ?)";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        return 0;
    }

    sqlite3_bind_text(stmt, 1,idUsu,-1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2,idAct,-1, SQLITE_STATIC);

    sqlite3_bind_double(stmt, 3, valoracion);
    //EJECUTAMOS SENTENCIA.
     rc = sqlite3_step(stmt);
    //ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
     //TODO HA IDO BIEN, INSERTADO.
    //VA TODO BIEN 
    
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    sqlite3_finalize(stmt);
    cerrarConexion();
    return 1;

}


//FUNCION PARA ELIMINAR INSCRIPCION A UNA ACTIVIDAD
int eliminarInscripcion(char* idAct, char* id_usu) {
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    const char* sql = "DELETE FROM INSCRIPCION WHERE ID_USU = ? AND ID_ACT = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        return 0;
    }

    sqlite3_bind_text(stmt, 1, id_usu, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, idAct, -1, SQLITE_STATIC);
    // EJECUTAMOS SENTENCIA.
    rc = sqlite3_step(stmt);
    // ERROR AL INSERTAR
    if (rc != SQLITE_DONE) {
        printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
        //logger(2,admin,"ERROR AL PREPARAR CONSULTA");  
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    // TODO HA IDO BIEN, INSERTADO.
    // VA TODO BIEN 
    
    //logger(1,admin, "HA INSERTADO UN NUEVO ADMIN");
    sqlite3_finalize(stmt);
    cerrarConexion();
    return 1;
}



//FUNCION PARA MOSTRAR LAS ACTIVIDADES DE LA BASE DE DATOS
// FUNCION PARA OBTENER LAS ACTIVIDADES DE LA BASE DE DATOS COMO UNA CADENA DE CARACTERES SEPARADA POR '$'
char* obtenerActividadesFecha() {
    
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "SELECT * FROM ACTIVIDAD ORDER BY FECHA_ACT";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return NULL;
    }

    // NOMBRES DE COLUMNAS
    
    char* actividades = malloc(sizeof(char) * 1000000);
    sprintf(actividades, "%-7s %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n", "ID_ACT", "NOMBRE_ACT", "TIPO_DE_ACTIVIDAD", "PUBLICO", "MUNICIPIO", "DIRECCION", "ENCARGADO", "FECHA_ACT");
    int contador=0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && contador <50) {
        int id_act = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre_act = sqlite3_column_text(stmt, 1);
        const unsigned char* tipo_de_actividad = sqlite3_column_text(stmt, 3);
        const unsigned char* publico = sqlite3_column_text(stmt, 4);
        const unsigned char* municipio = sqlite3_column_text(stmt, 5);
        const unsigned char* direccion = sqlite3_column_text(stmt, 6);
        const unsigned char* encargado = sqlite3_column_text(stmt, 7);
        const unsigned char* fecha_act = sqlite3_column_text(stmt, 8);

        // CONCATENAR LOS ATRIBUTOS DE CADA ACTIVIDAD A LA CADENA DE ACTIVIDADES
        char temp[5000];
        sprintf(temp, "%-7d %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n\n", id_act, nombre_act, tipo_de_actividad, publico, municipio, direccion, encargado, fecha_act);
        strcat(actividades, temp);
        contador++;
    }

    sqlite3_finalize(stmt);
    cerrarConexion();    
    return actividades;
}




char* obtenerActividadesTodas() {
    
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "SELECT * FROM ACTIVIDAD";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return NULL;
    }

    // NOMBRES DE COLUMNAS
    
    char* actividades = malloc(sizeof(char) * 1000000);
    sprintf(actividades, "%-7s %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n", "ID_ACT", "NOMBRE_ACT", "TIPO_DE_ACTIVIDAD", "PUBLICO", "MUNICIPIO", "DIRECCION", "ENCARGADO", "FECHA_ACT");
    int contador=0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && contador <50) {
        int id_act = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre_act = sqlite3_column_text(stmt, 1);
        const unsigned char* tipo_de_actividad = sqlite3_column_text(stmt, 3);
        const unsigned char* publico = sqlite3_column_text(stmt, 4);
        const unsigned char* municipio = sqlite3_column_text(stmt, 5);
        const unsigned char* direccion = sqlite3_column_text(stmt, 6);
        const unsigned char* encargado = sqlite3_column_text(stmt, 7);
        const unsigned char* fecha_act = sqlite3_column_text(stmt, 8);

        // CONCATENAR LOS ATRIBUTOS DE CADA ACTIVIDAD A LA CADENA DE ACTIVIDADES
        char temp[5000];
        sprintf(temp, "%-7d %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n\n", id_act, nombre_act, tipo_de_actividad, publico, municipio, direccion, encargado, fecha_act);
        strcat(actividades, temp);
        contador++;
    }

    sqlite3_finalize(stmt);
    cerrarConexion();    
    return actividades;
}


char* obtenerActividadesMejor() {
   
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "SELECT * FROM ACTIVIDAD ORDER BY (SELECT AVG(VALORACION) FROM VALORACION WHERE ID_ACT = ACTIVIDAD.ID_ACT) DESC LIMIT 10";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return NULL;
    }

    // NOMBRES DE COLUMNAS
    
    char* actividades = malloc(sizeof(char) * 1000000);
    sprintf(actividades, "%-7s %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n", "ID_ACT", "NOMBRE_ACT", "TIPO_DE_ACTIVIDAD", "PUBLICO", "MUNICIPIO", "DIRECCION", "ENCARGADO", "FECHA_ACT");
    int contador=0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && contador <50) {
        int id_act = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre_act = sqlite3_column_text(stmt, 1);
        const unsigned char* tipo_de_actividad = sqlite3_column_text(stmt, 3);
        const unsigned char* publico = sqlite3_column_text(stmt, 4);
        const unsigned char* municipio = sqlite3_column_text(stmt, 5);
        const unsigned char* direccion = sqlite3_column_text(stmt, 6);
        const unsigned char* encargado = sqlite3_column_text(stmt, 7);
        const unsigned char* fecha_act = sqlite3_column_text(stmt, 8);

        // CONCATENAR LOS ATRIBUTOS DE CADA ACTIVIDAD A LA CADENA DE ACTIVIDADES
        char temp[5000];
        sprintf(temp, "%-7d %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n\n", id_act, nombre_act, tipo_de_actividad, publico, municipio, direccion, encargado, fecha_act);
        strcat(actividades, temp);
        contador++;
    }

    sqlite3_finalize(stmt);
    cerrarConexion();    
    return actividades;
}

char* obtenerInscripciones(char* id_usu) {
    
    int rc;
    abrirConexion();
    sqlite3_stmt *stmt;
    char* sql = "SELECT ACTIVIDAD.* FROM ACTIVIDAD INNER JOIN INSCRIPCION ON ACTIVIDAD.ID_ACT = INSCRIPCION.ID_ACT WHERE INSCRIPCION.ID_USU = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return NULL;
    }

    // Bind el parámetro de ID_USU a la consulta preparada
    sqlite3_bind_text(stmt, 1, id_usu, -1, SQLITE_STATIC);

    // NOMBRES DE COLUMNAS
    
    char* actividades = malloc(sizeof(char) * 1000000);
    sprintf(actividades, "%-7s %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n", "ID_ACT", "NOMBRE_ACT", "TIPO_DE_ACTIVIDAD", "PUBLICO", "MUNICIPIO", "DIRECCION", "ENCARGADO", "FECHA_ACT");
    int contador=0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW && contador <50) {
        int id_act = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre_act = sqlite3_column_text(stmt, 1);
        const unsigned char* tipo_de_actividad = sqlite3_column_text(stmt, 3);
        const unsigned char* publico = sqlite3_column_text(stmt, 4);
        const unsigned char* municipio = sqlite3_column_text(stmt, 5);
        const unsigned char* direccion = sqlite3_column_text(stmt, 6);
        const unsigned char* encargado = sqlite3_column_text(stmt, 7);
        const unsigned char* fecha_act = sqlite3_column_text(stmt, 8);

        // CONCATENAR LOS ATRIBUTOS DE CADA ACTIVIDAD A LA CADENA DE ACTIVIDADES
        char temp[5000];
        sprintf(temp, "%-7d %-30s %-30s %-30s %-30s %-40s %-30s %-30s\n\n", id_act, nombre_act, tipo_de_actividad, publico, municipio, direccion, encargado, fecha_act);
        strcat(actividades, temp);
        contador++;
    }

    sqlite3_finalize(stmt);
    cerrarConexion();    
    return actividades;
}








//FUNCION PREVIA A VALORAR UNA ACTIVIDAD

// - TIENE QUE HABERSE REALIZADO LA ACTIVIDAD
// - EL USUARIO TIENE QUE HABER PARTICIPADO


//DEVUELVE 1, SI SE PUEDE VALORAR, 0 EN CUALQUIER OTRO CASO QUE INDIQUE QUE NO.

int comprobarInscripcionValorar(char* id_act, char* id_usu) {

 abrirConexion();
    sqlite3_stmt *stmt;
    int resulQ;
    int result = 0;

    // Primero, comprobamos si la actividad ya se ha realizado
    //char* sql_act = "SELECT FECHA_ACT FROM ACTIVIDAD WHERE ID_ACT = ?";
    //resulQ = sqlite3_prepare_v2(db, sql_act, -1, &stmt, NULL);
    //if (resulQ != SQLITE_OK) {
        //printf("No se puede preparar la consulta");
        //sqlite3_finalize(stmt);
        //cerrarConexion();
        //return 0;
   // }
    //sqlite3_bind_text(stmt, 1, id_act, -1, SQLITE_STATIC);
    //EJECUTAMOS SENTENCIA
    //resulQ = sqlite3_step(stmt);

        //EXISTE ESA ACTIVIDAD
        //BUSCAMOS SI EXISTE ESA INSCRIPCION
        char* sql_ins = "SELECT ID_USU FROM INSCRIPCION WHERE ID_USU = ? AND ID_ACT = ?";
        resulQ = sqlite3_prepare_v2(db, sql_ins, -1, &stmt, NULL);
        if (resulQ != SQLITE_OK) {
            printf("No se puede preparar la consulta");
            sqlite3_finalize(stmt);
            cerrarConexion();
            return 0;
        }
        sqlite3_bind_text(stmt, 1, id_usu, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, id_act, -1, SQLITE_STATIC);
        resulQ = sqlite3_step(stmt);
        if (resulQ == SQLITE_ROW) {
            //EXISTE, DEVOLVEMOS 1
            result = 1;
            sqlite3_finalize(stmt);
            cerrarConexion();
            return result;
        }
        else {

            //NO EXISTE INSCRIPCION DE ESE USUARIO
            
            sqlite3_finalize(stmt);
            cerrarConexion();
            return 0;
        }
 
    }

























