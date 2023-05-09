#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "gestionCodigos.h"


Usuario strAUsuario(char* codigo) {
    Usuario u;
    char* token = strtok(codigo, "$"); // primer token (código "01")
    token = strtok(NULL, "$"); // segundo token (nombre)
    u.setNombre(strdup(token));
    token = strtok(NULL, "$"); // tercer token (apellido)
    u.setApellido(strdup(token));
    token = strtok(NULL, "$"); // cuarto token (nombre de usuario)
    u.setNombreUsuario(strdup(token));
    token = strtok(NULL, "$"); // quinto token (contraseña)
    printf(strdup(token));
    u.setContrasenya(strdup(token));
    return u;
}

