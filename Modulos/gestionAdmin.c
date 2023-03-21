#include <stdio.h>
#include <stdlib.h>
//#include <openssl/md5.h>                //Esta libreria sera para hacer el hash
#include <string.h>
#include "gestionAdmin.h"
#include "../sqlite/sqlite3.h"

//HACEMOS LA DEFINICION DE LAS CONSTANTES PARA LOS LOG

#define INFO 0
#define WARNING 1
#define ERROR 2

sqlite3* db;

int abrirConexion() {
   
    int resultado_apertura;

    //char *nombre_base = leerProperties(2);
    char *nombre_base = "Base_Datos/Base_Datos.db";

    resultado_apertura = sqlite3_open(nombre_base, &db);

    //si el valor es 0, todo bien! sino, error en apertura

    if (resultado_apertura != SQLITE_OK) {
       printf("Error al abrir la base de datos");
        sqlite3_close(db);
        return 1;
    } else {
        printf("Conexion a la base de datos establecida correctamente.\n");
        return 0;
    }
}

//METODO PARA HASHEAR CONTRANENYA

//Utilizaremos el metodo de hash: SHA-256 
//Este metodo recibira como parametros el puntero del char que queremos hashear y devolvera el puntero del mismo string hasheado
//char* string_hash(char *str)
//{
   // unsigned char hash[SHA256_DIGEST_LENGTH];   //crear un array de 32 de longitud
    //SHA256_CTX sha256;
    //char *output = (char*) malloc(2 * SHA256_DIGEST_LENGTH + 1);

    //SHA256_Init(&sha256);
    //SHA256_Update(&sha256, str, strlen(str));
    //SHA256_Final(hash, &sha256);

    //for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
       // sprintf(output + (i * 2), "%02x", hash[i]);
    //}
    //output[2 * SHA256_DIGEST_LENGTH] = '\0';

    //return output;
//}



//FUNCION LOG PARA ESCRIBIR EN EL FICHERO LOG LAS OPERACIONES REALIZADAS 


void logger(int severity, char* usuario, char* info) {
    char *ruta =leerProperties(3);
    FILE* ficheroLog = fopen(ruta, "a");
    if (ficheroLog != NULL) {
        if (severity == INFO) {
            fprintf(ficheroLog, "[INFO] Usuario:%s -> %s \n", usuario,info);
        } else if (severity == WARNING) {
               fprintf(ficheroLog, "[WARNING] Usuario:%s -> %s \n", usuario,info);
        } else if (severity == ERROR) {
            fprintf(ficheroLog, "[ERROR] Usuario:%s -> %s \n", usuario,info);
        }
        fclose(ficheroLog);
    }
    else{
       printf("Error al intentar abir el fichero LOG"); 
    }

    return;
}



char *leerProperties( int num) {
    char **lines = (char **) malloc(100 * sizeof(char *));
    char buffer[100];
    int i = 0;
    FILE *fichero = fopen("Ficheros/ficheroConfig.txt", "r");

    if (fichero == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    else {

    while (fgets(buffer, 100, fichero) != NULL) {
        lines[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(lines[i], buffer);
        i++;
    }


    fclose(fichero);
    }

    char *ruta;
    char *rutaLimpiada;

    if(num==1) {
        ruta = lines[0];
        
    }else if(num==2) {
        ruta = lines[1];
    }else if(num==3) {
        ruta = lines[2];
    }else{
       ruta = "Sin ruta";
    }

    rutaLimpiada = strtok(ruta, "\n\r ");
    return (rutaLimpiada);
}


int login(char* usuario, char* contrasena) {
    int resultado_consulta;
    sqlite3_stmt *stmt;
    char* consulta = "SELECT * FROM ADMIN WHERE USUARIO_ADMIN = ? AND CONTRASENYA_ADMIN = ?;";

    resultado_consulta = sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);

    if (resultado_consulta != SQLITE_OK) {
        printf("Error al preparar la consulta\n");
        return -1;
    }

    sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, contrasena, strlen(contrasena), SQLITE_STATIC);

    resultado_consulta = sqlite3_step(stmt);

    if (resultado_consulta == SQLITE_ROW) {
        printf("Nombre de usuario y contrasena correctas\n");
        return 1;
    } else if (resultado_consulta == SQLITE_ERROR) {
        printf("Error en la consulta: %s\n", sqlite3_errmsg(db));
        return -1;
    } else {
        printf("Credenciales incorrectas\n");
        return 0;
    }




}






