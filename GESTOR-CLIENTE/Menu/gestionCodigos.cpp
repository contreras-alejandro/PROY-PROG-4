#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include "gestionCodigos.h"
#include <string>
#include <cstring> 


Usuario strAUsuario(char mensaje[512]) {
    Usuario usr;
    
    char copiaMensaje[512];
    strncpy(copiaMensaje, mensaje, sizeof(copiaMensaje));
    
    char* token = strtok(copiaMensaje, "$");

    token = strtok(nullptr, "$");

    int id = token ? atoi(token) : 0;
    usr.setId(id);

    token = strtok(nullptr, "$");

    char* nombre = const_cast<char*>(token ? token : "");
    token = strtok(nullptr, "$");

    char* apellido = const_cast<char*>(token ? token : "");
    token = strtok(nullptr, "$");

    char* nombre_usu = const_cast<char*>(token ? token : "");
    token = strtok(nullptr, "$");

    char* contrasenya = const_cast<char*>(token ? token : "");

    usr.setApellido(apellido);
    usr.setNombre(nombre);
    usr.setNombreUsuario(nombre_usu);
    usr.setContrasenya(contrasenya);
    
    return usr;
}



