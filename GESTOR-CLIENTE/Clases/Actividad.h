#ifndef _ACTIVIDAD_H
#define _ACTIVIDAD_H
#include <iostream>
using namespace std;

namespace Estructura_Actividad
{
    typedef struct{
        char* nombre;
        char* descripcion;
        char* tipo;
        char* publico;
        char* municipio;
        char* direccion;
        char* encargado;
        char* fecha;
    }Actividad;
}

class Actividad
{
private:
    char* nombre;
    char* descripcion;
    char* tipo;
    char* publico;
    char* municipio;
    char* direccion;
    char* encargado;
    char* fecha;

public:
    Actividad();
    Actividad(char* nombre, char* descripcion, char* tipo, char* publico, char* municipio, char* direccion, char* encargado, char* fecha);
    char* getNombreAct();
    Actividad convertirEstructuraAClase(Estructura_Actividad::Actividad a);
    Estructura_Actividad::Actividad convertirClaseAEstructura();
    ~Actividad();
    friend ostream& operator<<(ostream& out, const Actividad& p);
};


#endif