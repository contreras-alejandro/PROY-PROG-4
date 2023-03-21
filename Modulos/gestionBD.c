#include <stdio.h>
#include <stdlib.h>
//#include <openssl/md5.h>                //Esta libreria sera para hacer el hash
#include <string.h>
#include "gestionAdmin.h"
#include "../sqlite/sqlite3.h"



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