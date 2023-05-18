#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestionServer.h"
#include "../sqlite/sqlite3.h"
#include "gestionBD.h"
#include <time.h>


//HACEMOS LA DEFINICION DE LAS CONSTANTES PARA LOS LOG

#define INFO 0
#define WARNING 1
#define ERROR 2

#define MAX_LINE_ADMIN 50
//funcion para realizar el log
void logger(int severity, char* info) {
    //APERTURA
    char *ruta =leerProperties(3);
    time_t tiempo = time(NULL);
    struct tm *tm = localtime(&tiempo);
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", tm);
     //OBTENEMOS LA HORA ACTUAL
    FILE* ficheroLog = fopen(ruta, "a");
    if (ficheroLog != NULL) {
        //DEPENDIENDO DE LA SEVERIDAD INTRODUCIDA, SE ESCRIBE UN MENSAJE O OTRO
        if (severity == INFO) {
            fprintf(ficheroLog, " {%s} {%02d:%02d:%02d} [INFO] -> %s \n",fecha,
             tm->tm_hour, tm->tm_min, tm->tm_sec,info);

        } else if (severity == WARNING) {
               fprintf(ficheroLog, " {%s} {%02d:%02d:%02d} [WARNING]-> %s \n",fecha,
               tm->tm_hour, tm->tm_min, tm->tm_sec,info);
        } else if (severity == ERROR) {
            fprintf(ficheroLog, "{%s} {%02d:%02d:%02d} [ERROR] -> %s \n",fecha, tm->tm_hour, tm->tm_min, tm->tm_sec,
            info);
        }
        fclose(ficheroLog);
    }
    else{
       printf("Error al intentar abir el fichero LOG"); 
    }

    return;
}


//FUNCION PARA OBTENER LA RUTA DEL FICHERO PROPERTIES

char *leerProperties( int num) {
    //creamos una lista de char y dependiendo el num, obtendremos uno o otro.
    char **lines = (char **) malloc(100 * sizeof(char *));
    char buffer[100];
    int i = 0;
    FILE *fichero = fopen("Ficheros/ficheroConfig.txt", "r");

    if (fichero == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    else {

        //la llenamos con las ruta.

    while (fgets(buffer, 100, fichero) != NULL) {
        lines[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(lines[i], buffer);
        i++;
    }


    fclose(fichero);
    }

    //LIMPIAMOS LA RUTA, ELIMINAR \N, y devolvemos

    char *ruta;
    char *rutaLimpiada;

    if(num==1) {
        ruta = lines[0];
        
    }else if(num==2) {
        ruta = lines[1];
    }else if(num==3) {
        ruta = lines[2];
    }else{
       ruta = "Sin ruta";
    }

    rutaLimpiada = strtok(ruta, "\n\r ");
    return (rutaLimpiada);
}

//funcion para comprobar si una palabra cumple con el minimo de longitud
//LO USAREMOS PARA INTRODUCIR EL NOMBRE DE USUARIO O CONTRASENYA
int comprobarLongitud(char *palabra, int minimo){
    if(strlen(palabra)>=minimo){
        return 1;
    }else{
        return 0;
    }
}



//FUNCION PARA CREAR ADMINISTRADOR
void crearUsuario(){

    Usuario* usuario;
    usuario = (Usuario*) malloc(sizeof(Usuario));
    //QUE ATRIBUTOS SON NECESARIOS?
    // nombre, apellido nombreUsuario, contraseña
     char nombre[MAX_LINE_ADMIN], apellido[MAX_LINE_ADMIN], n_usuario[MAX_LINE_ADMIN],
      contrasena[MAX_LINE_ADMIN], contrasena2[MAX_LINE_ADMIN];
    int contrasenas_coinciden = 0;
    int usuarioValido=0;

    //los pedimos y almacenamos
    printf("Introduzca su nombre: ");
    fgets(nombre, MAX_LINE_ADMIN, stdin);
    //FINALMENTE LE AÑADE UN \0
    nombre[strcspn(nombre, "\n")] = '\0';

    //NOMBRE

	char *nombre_aux = malloc((MAX_LINE_ADMIN) * sizeof(char));
	sscanf(nombre, "%s", nombre_aux); 
	int tamanyo = strlen(nombre_aux);
	usuario->nombre = malloc((tamanyo + 1) * sizeof(char));
	strcpy(usuario->nombre, nombre_aux);
	free(nombre_aux);

    //APELLIDO

    printf("Introduzca su apellido: ");
    fgets(apellido, 50, stdin);
    apellido[strcspn(apellido, "\n")] = '\0';

    char *apellido_aux = malloc((MAX_LINE_ADMIN) * sizeof(char));
	sscanf(apellido, "%s", apellido_aux); 
	 tamanyo = strlen(apellido_aux);
	usuario->apellido = malloc((tamanyo + 1) * sizeof(char));
	strcpy(usuario->apellido, apellido_aux);
	free(apellido_aux);



    //ESTABLECEMOS QUE EL NOMBRE DE USUARIO Y CONTRANSEYA, MINIMO 7 CARACTERES
    
    while(usuarioValido==0){
    printf("Introduzca su nombre de usuario: ");
    fgets(n_usuario, 50, stdin);
    n_usuario[strcspn(n_usuario, "\n")] = '\0';
    if(comprobarLongitud(n_usuario,7)==0){
         printf("La longitud tiene que ser minimo de 7 caracteres\n");
         continue;
        
    } else if((comprobarUsuario(n_usuario)==1)){
            printf("NOMBRE DE USUARIO YA EXISTE, NO VALIDO");
        }
    else {
        usuarioValido=1;
        //METEMOS EL NOMBRE DE USUARIO EN EL ADMIN
         char *nombre_usu_aux = malloc((MAX_LINE_ADMIN) * sizeof(char));
         sscanf(n_usuario, "%s", nombre_usu_aux); 
        tamanyo = strlen(nombre_usu_aux);
	    usuario->nusuario = malloc((tamanyo + 1) * sizeof(char));
	    strcpy(usuario->nusuario, nombre_usu_aux);
	    free(nombre_usu_aux);

        break;
    }
    }

    while(contrasenas_coinciden==0){
        printf("Introduzca su contrasena: ");
        fgets(contrasena, 50, stdin);
        contrasena[strcspn(contrasena, "\n")] = '\0';
        
        if(comprobarLongitud(contrasena,7)==0){
            printf("La longitud tiene que ser minimo de 7 caracteres\n");
            continue;
        }

        printf("Confirme su contrasena: ");
        fgets(contrasena2, 50, stdin);
        contrasena2[strcspn(contrasena2, "\n")] = '\0';

        if(strcmp(contrasena, contrasena2)!=0){
            printf("Las contraseñas no coinciden. Vuelva a intentarlo.\n");
            
        }
        else {
            contrasenas_coinciden = 1;
        }
    }

    //UNA VEZ COFIRMADO QUE LAS CONTRASEÑAS COINCIDEN HASHEAMOS LA CONTRASEÑA ANTES DE PASARLA A LA BD
    char* contrasenya_hasheada = hash_string(contrasena);
    tamanyo = strlen(contrasenya_hasheada);
    usuario->contrasenya = malloc((tamanyo + 1) * sizeof(char));
    strcpy(usuario->contrasenya, contrasenya_hasheada);

  
    printf("\nDatos introducido del NUEVO USUARIO:\n");
    printf("Nombre: %s\n", usuario->nombre);
    printf("Apellido: %s\n", usuario->apellido);
    printf("Nombre de usuario: %s\n",  usuario->nusuario);

    //LLAMAMOS A METODO DE BD, QUE INTRODUCE UN ADMIN EN BD
    registrarUsuario(*usuario);
    return;
}

//FUNCION PARA IMPRIMIR POR CONSOLA UNA ACTIVIDAD
void imprimirActividad(Actividad act) {
    printf("Nombre: %s\n", act.nombre);
    printf("Descripcion: %s\n", act.descripcion);
    printf("Tipo: %s\n", act.tipo);
    printf("Publico: %s\n", act.publico);
    printf("Municipio: %s\n", act.municipio);
    printf("Direccion: %s\n", act.direccion);
    printf("Encargado: %s\n", act.encargado);
    printf("Fecha: %s\n", act.fecha);
}


//FUNCION PARA LIBERAR ESPACIO DE MEMORIA PARA ADMINISTRADOR
void liberarAdmin(Administrador* admin) {

    //LIBERAMOS LOS DIFERENTES ATRIBUTOS
    free(admin->nombre);
    free(admin->apellido);
    free(admin->nusuario);
    free(admin->contrasenya);

    //FINALMENTE EL ADMIN
    free(admin);

}

char* hash_string(char* str) {
    int hash = 0;
    int len = strlen(str);
     // Reservamos suficiente espacio para almacenar el hash en formato hexadecimal
    char* hash_str = malloc(len * 2 + 1);
    hash_str[0] = '\0';

    for (int i = 0; i < len; i++) {
        hash = (hash * 31 + str[i]) % 127;  //DIVIDIMOS POR NUMEROS PRIMOS
        char hex_str[3]; 
        snprintf(hex_str, 3, "%02x", hash); // Convertimos el valor del hash a formato hexadecimal
        strcat(hash_str, hex_str); // Concatenamos 
    }
    
    return hash_str;
    
     }


