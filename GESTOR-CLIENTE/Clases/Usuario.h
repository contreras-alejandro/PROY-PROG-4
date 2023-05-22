#ifndef _USUARIO_H
#define _USUARIO_H
#include <iostream>
using namespace std;
namespace Estructura_Usuario
{
    typedef struct{
        int id;
        char* nombre;
        char* apellido;
        char* nombre_usu;
        char* email;
        char* contrasenya;
    }Usuario;
}

class Usuario
{
private:
    int id;
    char* nombre;
    char* apellido;
    char* nombre_usu;  // CLAVE UNICA NO SE PODRA REPETIR
    char* contrasenya;
    
public:
    Usuario();
    Usuario(int id, char* nombre, char* apellido, char* nombre_usu, char* contrasenya);
    int getId();
    char* getNombre();
    char* getApellido();
    char* getNombreUsuario();
    void setId(int id);
    void setNombre(char* nombre);
    void setNombreUsuario(char* nombre_usu);
    void setApellido(char* apellido);
    void setContrasenya(char* contrasenya);
    char * getContrasenya();

    Usuario convertirEstructuraAClase(Estructura_Usuario::Usuario u);
    Estructura_Usuario::Usuario convertirClaseAEstructura();
    char* toString() const;
    ~Usuario();
    friend ostream& operator<<(ostream& out, const Usuario& p);
};

#endif
