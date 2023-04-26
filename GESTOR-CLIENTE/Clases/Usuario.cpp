#include "Usuario.h"
#include <stdio.h>
#include  <string.h>
#include <stdlib.h>

Usuario::Usuario()
{
    this->nombre=NULL;
    this->apellido=NULL;
    this->nombre_usu=NULL;
    this->contrasenya=NULL;
}

Usuario::Usuario(char* nombre, char* apellido, char* nombre_usu, char* contrasenya)
{
    this->nombre= new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);

    this->apellido= new char[strlen(apellido)+1];
    strcpy(this->apellido, apellido);

    this->nombre_usu= new char[strlen(nombre_usu)+1];
    strcpy(this->nombre_usu, nombre_usu);


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
Usuario Usuario::convertirEstructuraAClase(Estructura_Usuario::Usuario u)
{
    return Usuario(u.nombre, u.apellido, u.nombre_usu, u.contrasenya);
}

Estructura_Usuario::Usuario Usuario::convertirClaseAEstructura()
{
    Estructura_Usuario::Usuario us;

    us.nombre = (char*) malloc(strlen(this->nombre)+1);
    strcpy(us.nombre, this->nombre);

    us.apellido = (char*) malloc(strlen(this->apellido)+1);
    strcpy(us.apellido, this->apellido);

    us.nombre_usu = (char*) malloc(strlen(this->nombre_usu)+1);
    strcpy(us.nombre_usu, this->nombre_usu);


    us.contrasenya = (char*) malloc(strlen(this->contrasenya)+1);
    strcpy(us.contrasenya, this->contrasenya);

    return us;
}

Usuario::~Usuario()
{
    delete [] nombre;
    delete [] apellido;
    delete [] nombre_usu;
   
    delete [] contrasenya;
}