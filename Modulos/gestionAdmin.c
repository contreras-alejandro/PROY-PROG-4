#include <stdio.h>
#include <stdlib.h>
//#include <openssl/md5.h>                //Esta libreria sera para hacer el hash
#include <string.h>
#include "gestionAdmin.h"

//HACEMOS LA DEFINICION DE LAS CONSTANTES PARA LOS LOG

#define INFO 0
#define WARNING 1
#define ERROR 2

//sqlite3* abrirConexion(char* nombre_base) {
    //sqlite3 *db;
    //char *error_message = 0;
    //int resultado_apertura;

    //resultado_apertura = sqlite3_open(nombre_base, &db);

    //si el valor es 0, todo bien! sino, error en apertura

   // if (resultado_apertura != SQLITE_OK) {
       // printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        //sqlite3_close(db);
       // return NULL;
    //} else {
       // printf("Conexión a la base de datos establecida correctamente.\n");
        //return db;
    //}
//}

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
    FILE* ficheroLog = fopen("Ficheros/ficheroLog.txt", "a");
    if (ficheroLog != NULL) {
        if (severity == INFO) {
            fprintf(ficheroLog, "[INFO] Usuario:%s -> %s \n", usuario,info);
        } else if (severity == WARNING) {
               fprintf(ficheroLog, "[WARNING] Usuario:%s -> %s \n", usuario,info);
        } else if (severity == ERROR) {
            fprintf(ficheroLog, "[ERROR] Usuario:%s -> %s \n", usuario,info);
        }
        printf("log bien!\n");
        fclose(ficheroLog);
    }
    else{
       printf("Error al intentar abir el fichero LOG"); 
    }
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

    if(num==1) {
        return (lines[0]);
    }else if(num==2) {
        return (lines[1]);
    }else{
        return "sin ruta";
    };
}



