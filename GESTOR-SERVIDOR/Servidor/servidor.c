#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "servidor.h"


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define TAMAINO_SENDBUFF 1024
#define TAMAINO_RECVBUFF 512
#define BYTES 2



Usuario strAUsuario(char* str){

    Usuario u;
    char* token = strtok(str, "$");
    u.nombre = (char*) malloc(strlen(token) + 1);
    strcpy(u.nombre, token);

    token = strtok(NULL, "$");
    u.apellido = (char*) malloc(strlen(token) + 1);
    strcpy(u.apellido, token);

    token = strtok(NULL, "$");
    u.nusuario = (char*) malloc(strlen(token) + 1);
    strcpy(u.nusuario, token);

    token = strtok(NULL, "$");
    u.contrasenya = (char*) malloc(strlen(token) + 1);
    strcpy(u.contrasenya, token);

    return u;

}