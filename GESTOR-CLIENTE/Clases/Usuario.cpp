#include "Usuario.h"
#include <stdio.h>
#include  <string.h>

Usuario::Usuario()
{
    this->nombre=NULL;
    this->apellido=NULL;
    this->nombre_usu=NULL;
    this->email=NULL;
    this->contrasenya=NULL;
}

Usuario::Usuario(char* nombre, char* apellido, char* nombre_usu, char* email, char* contrasenya)
{
    this->nombre= new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);

    this->apellido= new char[strlen(apellido)+1];
    strcpy(this->apellido, apellido);

    this->nombre_usu= new char[strlen(nombre_usu)+1];
    strcpy(this->nombre_usu, nombre_usu);

    this->email= new char[strlen(email)+1];
    strcpy(this->email, email);

    this->contrasenya= new char[strlen(contrasenya)+1];
    strcpy(this->contrasenya, contrasenya);
}

char* Usuario::getNombre()
{
    return this->nombre;
}

char* Usuario::getApellido()
{
    return this->apellido;
}

char* Usuario::getNombreUsuario()
{
    return this->nombre_usu;
}

Usuario::~Usuario()
{
    delete [] nombre;
    delete [] apellido;
    delete [] nombre_usu;
    delete [] email;
    delete [] contrasenya;
}