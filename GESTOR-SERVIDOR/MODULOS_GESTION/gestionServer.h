#ifndef GESTION_SERVER
#define GESTION_SERVER

//creamos la estrucutra para almacenar los datos del administrador
//la usaremos para  la funcion crearAdmin, de modo que insertara un admin en VD

//ESTA ACORDE CON LA BASE DE DATOS, CON LOS ATRIBUTOS
// NOMBRE
// APELLIDO
// NOMBRE DE USUARIO
// CONTRASENYA

typedef struct{
    char* nombre;
    char* apellido;
    char* nusuario;
    char* contrasenya;
}Administrador;

//LO MISMO CON LA ACTIVIDAD

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


typedef struct{
    char* id;
    char* nombre;
    char* apellido;
    char* nusuario;  // CLAVE UNICA NO SE PODRA REPETIR
    char* contrasenya;
}Usuario;

//FUNCION QUE DEVUELVE EL VALOR INTRODUCIDO HASHEADO! (PARA LA CONTRASENYA)
char* hash_string(char* str);
//funcion para realizar el log
void logger(int severity, char* info);
//FUNCION PARA OBTENER LA RUTA DEL FICHERO PROPERTIES
char * leerProperties(int);


//FUNCION PARA CREAR USUARIO!
void crearUsuario();


//FUNCION PARA IMPRIMIR POR CONSOLA UNA ACTIVIDAD
void imprimirActividad(Actividad act);
//FUNCION PARA CREAR UNA ACTIVIDAD
void crearActividad(char*usuario);

//////////////////////////////////////////////////////
//        NUEVO METODOS   













#endif