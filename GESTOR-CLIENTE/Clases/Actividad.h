#ifndef _ACTIVIDAD_H
#define _ACTIVIDAD_H

namespace Estructuras
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
    Actividad convertirEstructuraAClase(Estructuras::Actividad a);
    Estructuras::Actividad convertirClaseAEstructura(Actividad a);
    ~Actividad();
};


#endif