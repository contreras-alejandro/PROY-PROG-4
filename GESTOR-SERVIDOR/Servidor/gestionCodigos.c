#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "gestionCodigos.h"



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
    token = strtok(NULL, "$"); // quinto token (contraseña)s
    u.contrasenya = strdup(token);
    return u;
}

char* usuarioAStr(Usuario* u) {
    char* codigo = malloc(sizeof(char) * 200); // Reservamos espacio suficiente para la cadena de salida
    sprintf(codigo, "02$%s$%s$%s$%s", u->nombre, u->apellido, u->nusuario, u->contrasenya);
    return codigo;
}
