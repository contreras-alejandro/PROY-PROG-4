#ifndef _PROPUESTA_H
#define _PROPUESTA_H

namespace Estructuras
{
    typedef struct{
        char* nombre;
        char* descripcion;
        char* tipo;
        char* publico;
        char* municipio;
        char* direccion;
        char* fecha;
    }Propuesta;
}

class Propuesta
{
private:
    char* nombre;
    char* descripcion;
    char* tipo;
    char* publico;
    char* municipio;
    char* direccion;
    char* fecha;

public:
    Propuesta();
    Propuesta(char* nombre, char* descripcion, char* tipo, char* publico, char* municipio, char* direccion, char* fecha);
    char* getNombreAct();
    Propuesta convertirEstructuraAClase(Estructuras::Propuesta a);
    Estructuras::Propuesta convertirClaseAEstructura(Propuesta a);
    ~Propuesta();
};


#endif