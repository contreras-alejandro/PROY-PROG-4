#include <stdio.h>
#include <stdlib.h>
#include "../../sqlite/sqlite3.h"
#include <openssl/md5.h>                //Esta libreria sera para hacer el hash
#include <string.h>

sqlite3* abrirConexion(char* nombre_base) {
    sqlite3 *db;
    char *error_message = 0;
    int resultado_apertura;

    resultado_apertura = sqlite3_open(nombre_base, &db);

    //si el valor es 0, todo bien! sino, error en apertura

    if (resultado_apertura != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    } else {
        printf("Conexión a la base de datos establecida correctamente.\n");
        return db;
    }
}

//METODO PARA HASHEAR CONTRANENYA

//Utilizaremos el metodo de hash: SHA-256 
//Este metodo recibira como parametros el puntero del char que queremos hashear y devolvera el puntero del mismo string hasheado
char* string_hash(char *str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];   //crear un array de 32 de longitud
    SHA256_CTX sha256;
    char *output = (char*) malloc(2 * SHA256_DIGEST_LENGTH + 1);

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[2 * SHA256_DIGEST_LENGTH] = '\0';

    return output;
}
