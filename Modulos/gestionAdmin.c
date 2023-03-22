#include <stdio.h>
#include <stdlib.h>
//#include <openssl/md5.h>                //Esta libreria sera para hacer el hash
#include <string.h>
#include "gestionAdmin.h"
#include "../sqlite/sqlite3.h"
#include "gestionBD.h"


//HACEMOS LA DEFINICION DE LAS CONSTANTES PARA LOS LOG

#define INFO 0
#define WARNING 1
#define ERROR 2

void logger(int severity, char* usuario, char* info) {
    char *ruta =leerProperties(3);
    FILE* ficheroLog = fopen(ruta, "a");
    if (ficheroLog != NULL) {
        if (severity == INFO) {
            fprintf(ficheroLog, "[INFO] Usuario:%s -> %s \n", usuario,info);
        } else if (severity == WARNING) {
               fprintf(ficheroLog, "[WARNING] Usuario:%s -> %s \n", usuario,info);
        } else if (severity == ERROR) {
            fprintf(ficheroLog, "[ERROR] Usuario:%s -> %s \n", usuario,info);
        }
        fclose(ficheroLog);
    }
    else{
       printf("Error al intentar abir el fichero LOG"); 
    }

    return;
}



char *leerProperties( int num) {
    char **lines = (char **) malloc(100 * sizeof(char *));
    char buffer[100];
    int i = 0;
    FILE *fichero = fopen("Ficheros/ficheroConfig.txt", "r");

    if (fichero == NULL) {
        printf("Error al abrir el archivo.\n");
    }

    else {

    while (fgets(buffer, 100, fichero) != NULL) {
        lines[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(lines[i], buffer);
        i++;
    }


    fclose(fichero);
    }

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


int comprobarLongitud(char *palabra, int minimo){
    if(strlen(palabra)>=minimo){
        return 1;
    }else{
        return 0;
    }
}




void crearAdmin(char*usuario){

    //QUE ATRIBUTOS SON NECESARIOS?
    // nombre, apellido nombreUsuario, contraseña
     char nombre[50], apellido[50], n_usuario[50], contrasena[50], contrasena2[50];
    int contrasenas_coinciden = 0;
    int usuarioValido=0;

    printf("Introduzca su nombre: ");
    fgets(nombre, 50, stdin);
    //FINALMENTE LE AÑADE UN \0
    nombre[strcspn(nombre, "\n")] = '\0';

    printf("Introduzca su apellido: ");
    fgets(apellido, 50, stdin);
    apellido[strcspn(apellido, "\n")] = '\0';
    
    while(usuarioValido==0){
    printf("Introduzca su nombre de usuario: ");
    fgets(n_usuario, 50, stdin);
    n_usuario[strcspn(n_usuario, "\n")] = '\0';
    if(comprobarLongitud(n_usuario,7)==0){
         printf("La longitud tiene que ser minimo de 7 caracteres\n");
         continue;
        
    }
    else {
        usuarioValido=1;
        break;
    }
    }

    while(contrasenas_coinciden==0){
        printf("Introduzca su contraseña: ");
        fgets(contrasena, 50, stdin);
        contrasena[strcspn(contrasena, "\n")] = '\0';
        
        if(comprobarLongitud(contrasena,7)==0){
            printf("La longitud tiene que ser minimo de 7 caracteres\n");
            continue;
        }

        printf("Confirme su contraseña: ");
        fgets(contrasena2, 50, stdin);
        contrasena2[strcspn(contrasena2, "\n")] = '\0';

        if(strcmp(contrasena, contrasena2)!=0){
            printf("Las contraseñas no coinciden. Vuelva a intentarlo.\n");
            
        }
        else{
            contrasenas_coinciden = 1;
        }
    }


    printf("\nDatos introducido del NUEVO ADMINs:\n");
    printf("Nombre: %s\n", nombre);
    printf("Apellido: %s\n", apellido);
    printf("Nombre de usuario: %s\n", n_usuario);
    printf("Contraseña: %s\n", contrasena);

    Administrador admin;
    strcpy(admin.nombre, nombre);
    strcpy(admin.apellido, apellido);
    strcpy(admin.nusuario, n_usuario);
    strcpy(admin.contrasenya, contrasena);


    //LLAMAMOS A METODO DE BD, QUE INTRODUCE UN ADMIN EN BD
    insertarAdmin(usuario,admin);
    return;
}



void crearActividad(char*usuario){

    char nombre[50], descripcion[250], tipo[50], publico[50], municipio[50], direccion[50], encargado[50], fecha[50];
    printf("Introduzca el nombre de la actividad: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    printf("Introduzca una descrpcion: ");
    fgets(descripcion, 250, stdin);
    descripcion[strcspn(descripcion, "\n")] = '\0';
    
    printf("Introduzca el tipo de actividad: ");
    fgets(tipo, 50, stdin);
    tipo[strcspn(tipo, "\n")] = '\0';
    
    printf("Introduzca a que publico esta dirigido: ");
    fgets(publico, 50, stdin);
    publico[strcspn(publico, "\n")] = '\0';

    printf("Introduzca el municipio: ");
    fgets(municipio, 50, stdin);
    municipio[strcspn(municipio, "\n")] = '\0';

    printf("Introduzca la direccion: ");
    fgets(direccion, 50, stdin);
    direccion[strcspn(direccion, "\n")] = '\0';

    printf("Introduzca el encargado: ");
    fgets(encargado, 50, stdin);
    encargado[strcspn(encargado, "\n")] = '\0';

    printf("Introduzca la fecha: ");
    fgets(fecha, 50, stdin);
    fecha[strcspn(fecha, "\n")] = '\0';



    printf("\nDatos introducido del NUEVO ADMINs:\n");
    printf("Nombre: %s\n", nombre);
    printf("Descripcion: %s\n", descripcion);
    printf("Tipo de actividad: %s\n", tipo);
    printf("Publico dirigido: %s\n", publico);
    printf("Municipio: %s\n", municipio);
    printf("Direccion: %s\n", direccion);
    printf("Encargado: %s\n", encargado);
    printf("Fecha: %s\n", fecha);

    Actividad act;
    strcpy(act.nombre, nombre);
    strcpy(act.descripcion, descripcion);
    strcpy(act.tipo, tipo);
    strcpy(act.publico, publico);
    strcpy(act.municipio, municipio);
    strcpy(act.direccion, direccion);
    strcpy(act.encargado, encargado);
    strcpy(act.fecha, fecha);


    insertarActividad(usuario,act);
    return;
}








