#include "Usuario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>



Usuario::Usuario()
{
    this->id = 0;
    this->nombre = NULL;
    this->apellido = NULL;
    this->nombre_usu = NULL;
    this->contrasenya = NULL;
}

Usuario::Usuario(int id, char* nombre, char* apellido, char* nombre_usu, char* contrasenya)
{
    this->id = id;

    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);

    this->apellido = new char[strlen(apellido) + 1];
    strcpy(this->apellido, apellido);

    this->nombre_usu = new char[strlen(nombre_usu) + 1];
    strcpy(this->nombre_usu, nombre_usu);

    this->contrasenya = new char[strlen(contrasenya) + 1];
    strcpy(this->contrasenya, contrasenya);
}

int Usuario::getId()
{
    return this->id;
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

void Usuario::setId(int id)
{
    this->id = id;
}

void Usuario::setNombre(char* nombre)
{
    if (this->nombre != NULL)
        delete[] this->nombre;
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
}

void Usuario::setApellido(char* apellido)
{
    if (this->apellido != NULL)
        delete[] this->apellido;
    this->apellido = new char[strlen(apellido) + 1];
    strcpy(this->apellido, apellido);
}

void Usuario::setNombreUsuario(char* nombre_usu)
{
    if (this->nombre_usu != NULL)
        delete[] this->nombre_usu;
    this->nombre_usu = new char[strlen(nombre_usu) + 1];
    strcpy(this->nombre_usu, nombre_usu);
}

void Usuario::setContrasenya(char* contrasenya)
{
    if (this->contrasenya != NULL)
        delete[] this->contrasenya;
    this->contrasenya = new char[strlen(contrasenya) + 1];
    strcpy(this->contrasenya, contrasenya);
}

 char * Usuario::getContrasenya() {
    
    return this->contrasenya;

 }



Usuario Usuario::convertirEstructuraAClase(Estructura_Usuario::Usuario u)
{
    return Usuario(u.id, u.nombre, u.apellido, u.nombre_usu, u.contrasenya);
}

Estructura_Usuario::Usuario Usuario::convertirClaseAEstructura()
{
    Estructura_Usuario::Usuario us;

    us.id = this->id;

    us.nombre = (char*)malloc(strlen(this->nombre) + 1);
    strcpy(us.nombre, this->nombre);

    us.apellido = (char*)malloc(strlen(this->apellido) + 1);
    strcpy(us.apellido, this->apellido);

    us.nombre_usu = (char*)malloc(strlen(this->nombre_usu) + 1);
    strcpy(us.nombre_usu, this->nombre_usu);

    us.contrasenya = (char*)malloc(strlen(this->contrasenya) + 1);
    strcpy(us.contrasenya, this->contrasenya);

    return us;
}

char* Usuario::toString() const
{
    std::string str;
    str.append(std::to_string(id));
    str.append("$");
    str.append(nombre);
    str.append("$");
    str.append(apellido);
    str.append("$");
    str.append(nombre_usu);
    str.append("$");
    str.append(contrasenya);
    char* char_str = new char[str.length() + 1];
    strcpy(char_str, str.c_str());
    return char_str;
}

Usuario::~Usuario()
{
    delete[] nombre;
    delete[] apellido;
    delete[] nombre_usu;
    delete[] contrasenya;
}



ostream& operator<<(ostream& out, const Usuario& u)
{
    out << "Id: " << u.id << endl;
    out << "Nombre: " << u.nombre << endl;
    out << "Apellido: " << u.apellido << endl;
    out << "Nombre de usuario: " << u.nombre_usu << endl;
    
    return out;
}