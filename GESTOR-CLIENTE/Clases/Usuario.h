#ifndef _USUARIO_H
#define _USUARIO_H

namespace Estructura_Usuario
{
    typedef struct{
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
    char* nombre;
    char* apellido;
    char* nombre_usu;  // CLAVE UNICA NO SE PODRA REPETIR
    char* contrasenya;
    
public:
    Usuario();
    Usuario(char* nombre, char* apellido, char* nombre_usu, char* contrasenya);
    char* getNombre();
    char* getApellido();
    char* getNombreUsuario();
    Usuario convertirEstructuraAClase(Estructura_Usuario::Usuario u);
    Estructura_Usuario::Usuario convertirClaseAEstructura();
    ~Usuario();

};


#endif