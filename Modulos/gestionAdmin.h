#ifndef GESTION_ADMIN
#define GESTION_ADMIN

typedef struct{
    char nombre[50];
    char apellido[50];
    char nusuario[50];
    char contrasenya[50];
}Administrador;


char* string_hash(char *str);
void logger(int severity, char* usuario, char* info);
char * leerProperties(int);
void crearAdmin();





#endif