#include <iostream>
#include <string.h>
#include <time.h>
#include "gestionLog.h"


#define INFO 0
#define WARNING 1
#define ERROR 2


char * leerProperties(  ) {
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

    char *ruta;
    char *rutaLimpiada;

    ruta = lines[0];
        
    rutaLimpiada = strtok(ruta, "\n\r ");
    return (rutaLimpiada);
}



void logger(int severity, const char* usuario, const char* info) {
   //APERTURA
    char *ruta =leerProperties();
    time_t tiempo = time(NULL);
    struct tm *tm = localtime(&tiempo);
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", tm);
     //OBTENEMOS LA HORA ACTUAL
    FILE* ficheroLog = fopen(ruta, "a");
    if (ficheroLog != NULL) {
        //DEPENDIENDO DE LA SEVERIDAD INTRODUCIDA, SE ESCRIBE UN MENSAJE O OTRO
        if (severity == INFO) {
            fprintf(ficheroLog, " {%s} {%02d:%02d:%02d} [INFO] Usuario:%s -> %s \n",fecha,
             tm->tm_hour, tm->tm_min, tm->tm_sec,usuario,info);

        } else if (severity == WARNING) {
               fprintf(ficheroLog, " {%s} {%02d:%02d:%02d} [WARNING] Usuario:%s -> %s \n",fecha,
               tm->tm_hour, tm->tm_min, tm->tm_sec,usuario,info);
        } else if (severity == ERROR) {
            fprintf(ficheroLog, "{%s} {%02d:%02d:%02d} [ERROR] Usuario:%s -> %s \n",fecha, tm->tm_hour, tm->tm_min, tm->tm_sec,
            usuario,info);
        }
        fclose(ficheroLog);
    }
    else{
       printf("Error al intentar abir el fichero LOG"); 
    }

    return;
}
