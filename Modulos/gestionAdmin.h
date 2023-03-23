#ifndef GESTION_ADMIN
#define GESTION_ADMIN

typedef struct{
    char nombre[50];
    char apellido[50];
    char nusuario[50];
    char contrasenya[50];
}Administrador;

typedef struct{
    char nombre[50];
    char descripcion[250];
    char tipo[50];
    char publico[50];
    char municipio[50];
    char direccion[50];
    char encargado[50];
    char fecha[50];
}Actividad;


char* string_hash(char *str);
void logger(int severity, char* usuario, char* info);
char * leerProperties(int);
void crearAdmin();
void imprimirActividad(Actividad act);
void crearActividad(char*usuario);
void modificarActividad(int id);





#endif