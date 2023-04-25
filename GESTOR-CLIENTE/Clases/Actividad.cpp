#include "Actividad.h"
#include <stdio.h>
#include  <string.h>
#include <stdlib.h>

Actividad::Actividad()
{
    this->nombre=NULL;
    this->descripcion=NULL;
    this->tipo=NULL;
    this->publico=NULL;
    this->municipio=NULL;
    this->direccion=NULL;
    this->encargado=NULL;
    this->fecha=NULL;

}

Actividad::Actividad(char* nombre, char* descripcion, char* tipo, char* publico, char* municipio, char* direccion, char* encargado, char* fecha)
{
    this->nombre= new char[strlen(nombre)+1];
    strcpy(this->nombre, nombre);

    this->descripcion= new char[strlen(descripcion)+1];
    strcpy(this->descripcion, descripcion);

    this->tipo= new char[strlen(tipo)+1];
    strcpy(this->tipo, tipo);

    this->publico= new char[strlen(publico)+1];
    strcpy(this->publico, publico);

    this->municipio= new char[strlen(municipio)+1];
    strcpy(this->municipio, municipio);

    this->direccion= new char[strlen(direccion)+1];
    strcpy(this->direccion, direccion);

    this->encargado= new char[strlen(encargado)+1];
    strcpy(this->encargado, encargado);

    this->fecha= new char[strlen(fecha)+1];
    strcpy(this->fecha, fecha);
}

char* Actividad::getNombreAct()
{
    return this->nombre;
}

Actividad Actividad::convertirEstructuraAClase(Estructuras::Actividad a)
{
    return Actividad(a.nombre,a.descripcion,a.tipo,a.publico,a.municipio,a.direccion,a.encargado,a.fecha);
}

Estructuras::Actividad Actividad::convertirClaseAEstructura(Actividad a)
{
    Estructuras::Actividad ac;

    ac.nombre = (char*) malloc(strlen(a.nombre)+1);
    strcpy(ac.nombre, a.nombre);

    ac.descripcion = (char*) malloc(strlen(a.descripcion)+1);
    strcpy(ac.descripcion, a.descripcion);

    ac.tipo = (char*) malloc(strlen(a.tipo)+1);
    strcpy(ac.tipo, a.tipo);

    ac.publico = (char*) malloc(strlen(a.publico)+1);
    strcpy(ac.publico, a.publico);

    ac.municipio = (char*) malloc(strlen(a.municipio)+1);
    strcpy(ac.municipio, a.municipio);

    ac.direccion = (char*) malloc(strlen(a.direccion)+1);
    strcpy(ac.direccion, a.direccion);

    ac.encargado = (char*) malloc(strlen(a.encargado)+1);
    strcpy(ac.encargado, a.encargado);

    ac.fecha = (char*) malloc(strlen(a.fecha)+1);
    strcpy(ac.fecha, a.fecha);

    return ac;
}

Actividad::~Actividad()
{
    delete [] nombre;
    delete [] descripcion;
    delete [] tipo;
    delete [] publico;
    delete [] municipio;
    delete [] direccion;
    delete [] encargado;
    delete [] fecha;
}