#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Modulos/gestionBD.h"
#include "../Modulos/gestionAdmin.h"


#define MAX_LINE_LENGTH 1024

//FUNCION PARA CARGAR DESDE CSV A BASE DE DATOS


void cargarCsv(char* usuario) {
    //APERTURA DE FICHERO
    char *ruta = leerProperties(1);
    FILE* file = fopen(ruta, "r");
    char linea[1024];
    if (!file) {
        printf("No se ha podido abrir el archivo CSV\n");
    }else{
        printf("CSV ABIERTO\n");
        printf("CARGANDO A BASE DE DATOS DESDE CSV....\n");
    }



    //POR CADA LINEA, CREAMOS UNA ACTIVIDAD
    char line[MAX_LINE_LENGTH];

    //OMITIMOS LA PRIMERA LINEA
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file)) {

        line[strcspn(line, "\n")] = '\0';


        char* id_str = strtok(line, ";");
        char* nombre = strtok(NULL, ";");
        char* descripcion = strtok(NULL, ";");
        char* tipo = strtok(NULL, ";");
        char* publico = strtok(NULL, ";");
        char* municipio = strtok(NULL, ";");
        char* direccion = strtok(NULL, ";");
        char* encargado = strtok(NULL, ";");
        char* fecha = strtok(NULL, ";");


        int id = atoi(id_str);

        //PASAMOS LOS VALORES OBTENIDOS A LOS ATRIBUTOS DE UNA ACTIVIDADD Y DESPUES INSERTAMOS LA ACTIVIDAD EN BD
        

        Actividad actividad;
        snprintf(actividad.nombre, sizeof(actividad.nombre), "%s", nombre);
        snprintf(actividad.descripcion, sizeof(actividad.descripcion), "%s", descripcion);
        snprintf(actividad.tipo, sizeof(actividad.tipo), "%s", tipo);
        snprintf(actividad.publico, sizeof(actividad.publico), "%s", publico);
        snprintf(actividad.municipio, sizeof(actividad.municipio), "%s", municipio);
        snprintf(actividad.direccion, sizeof(actividad.direccion), "%s", direccion);
        snprintf(actividad.encargado, sizeof(actividad.encargado), "%s", encargado);
        snprintf(actividad.fecha, sizeof(actividad.fecha), "%s", fecha);



        //LA INSERTAMOS EN BD


        insertarActividad(usuario, actividad);
       
    }
     logger(1,usuario,"CARGADA LA BASE DE DATOS CON CSV");

    printf("ACTIVIDADES CARGADAS CON EXITO!!\n");

    fclose(file);
}
   



