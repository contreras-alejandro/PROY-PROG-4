#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "servidor.h"


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define TAMAINO_SENDBUFF 1024
#define TAMAINO_RECVBUFF 512
#define BYTES 2



Usuario strAUsuario(char* codigo) {
    Usuario u;
    char* token = strtok(codigo, "$"); // primer token (código "01")
    token = strtok(NULL, "$"); // segundo token (nombre)
    u.nombre = strdup(token);
    token = strtok(NULL, "$"); // tercer token (apellido)
    u.apellido = strdup(token);
    token = strtok(NULL, "$"); // cuarto token (nombre de usuario)
    u.nusuario = strdup(token);
    token = strtok(NULL, "$"); // quinto token (contraseña)
    printf(strdup(token));
    u.contrasenya = strdup(token);
    return u;
}