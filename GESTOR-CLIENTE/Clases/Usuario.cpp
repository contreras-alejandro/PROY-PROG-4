#include "Usuario.h"
#include <stdio.h>
#include  <string.h>
#include <stdlib.h>

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
Usuario Usuario::convertirEstructuraAClase(Estructuras::Usuario u)
{
    return Usuario(u.nombre, u.apellido, u.nombre_usu, u.email, u.contrasenya);
}

Estructuras::Usuario Usuario::convertirClaseAEstructura(Usuario u)
{
    Estructuras::Usuario us;

    us.nombre = (char*) malloc(strlen(u.nombre)+1);
    strcpy(us.nombre, u.nombre);

    us.apellido = (char*) malloc(strlen(u.apellido)+1);
    strcpy(us.apellido, u.apellido);

    us.nombre_usu = (char*) malloc(strlen(u.nombre_usu)+1);
    strcpy(us.nombre_usu, u.nombre_usu);

    us.email = (char*) malloc(strlen(u.email)+1);
    strcpy(us.email, u.email);

    us.contrasenya = (char*) malloc(strlen(u.contrasenya)+1);
    strcpy(us.contrasenya, u.contrasenya);

    return us;
}

Usuario::~Usuario()
{
    delete [] nombre;
    delete [] apellido;
    delete [] nombre_usu;
    delete [] email;
    delete [] contrasenya;
}