#ifndef _USUARIO_H
#define _USUARIO_H

namespace Estructuras
{
    typedef struct{
        char* nombre;
        char* apellido;
        char* nusuario;
        char* contrasenya;
    }Usuario;
}
class Usuario
{
private:
    char* nombre;
    char* apellido;
    char* nombre_usu;  // CLAVE UNICA NO SE PODRA REPETIR
    char* email;
    char* contrasenya;
    
public:
    Usuario();
    Usuario(char* nombre, char* apellido, char* nombre_usu, char* email, char* contrasenya);
    char* getNombre();
    char* getApellido();
    char* getNombreUsuario();
    Usuario convertirEstructuraAClase(Estructuras::Usuario u);
    Estructuras::Usuario convertirClaseAEstructura(Usuario u);
    ~Usuario();

};


#endif