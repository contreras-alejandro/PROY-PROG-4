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

Actividad Actividad::convertirEstructuraAClase(Estructura_Actividad::Actividad a)
{
    return Actividad(a.nombre,a.descripcion,a.tipo,a.publico,a.municipio,a.direccion,a.encargado,a.fecha);
}

Estructura_Actividad::Actividad Actividad::convertirClaseAEstructura()
{
    Estructura_Actividad::Actividad ac;

    ac.nombre = (char*) malloc(strlen(this->nombre)+1);
    strcpy(ac.nombre,this->nombre);

    ac.descripcion = (char*) malloc(strlen(this->descripcion)+1);
    strcpy(ac.descripcion, this->descripcion);

    ac.tipo = (char*) malloc(strlen(this->tipo)+1);
    strcpy(ac.tipo, this->tipo);

    ac.publico = (char*) malloc(strlen(this->publico)+1);
    strcpy(ac.publico, this->publico);

    ac.municipio = (char*) malloc(strlen(this->municipio)+1);
    strcpy(ac.municipio, this->municipio);

    ac.direccion = (char*) malloc(strlen(this->direccion)+1);
    strcpy(ac.direccion, this->direccion);

    ac.encargado = (char*) malloc(strlen(this->encargado)+1);
    strcpy(ac.encargado, this->encargado);

    ac.fecha = (char*) malloc(strlen(this->fecha)+1);
    strcpy(ac.fecha, this->fecha);

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


ostream& operator<<(ostream& out, const Actividad& a)
{
    out << "Nombre: " << a.nombre << endl;
    out << "Descripcion: " << a.descripcion << endl;
    out << "Tipo: " << a.tipo << endl;
    out << "Publico: " << a.publico << endl;
    out << "Municipio: " << a.municipio << endl;
    out << "Direccion: " << a.direccion << endl;
    out << "Encargado: " << a.encargado << endl;
    out << "Fecha: " << a.fecha << endl;
    return out;
}