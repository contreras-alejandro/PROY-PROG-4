#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Modulos/gestionBD.h"
#include "../Modulos/gestionAdmin.h"


#define MAX_LINE_LENGTH 1024


void cargarCsv(char* usuario) {
    FILE* file = fopen("./Modulos/actividades.csv", "r");
    char linea[1024];
    if (!file) {
        printf("No se ha podido abrir el archivo CSV\n");
    }else{
        printf("CSV ABIERTO\n");
    }

    char line[MAX_LINE_LENGTH];
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


        insertarActividad(usuario, actividad);
    }

    fclose(file);
}
   



