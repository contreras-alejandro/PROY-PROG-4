#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Modulos/gestionBD.h"
#include "../Modulos/gestionAdmin.h"




void cargarDatosDesdeCSV(char* usuario) {
        
    char* archivo_csv = "../Ficheros/actividades.csv";
    FILE* fp = fopen(archivo_csv, "r");
    if (!fp) {
        printf("Error al abrir el archivo CSV\n");
        return;
    }

    // Saltar la primera línea que contiene los nombres de las columnas
    char buf[1024];
    fgets(buf, sizeof(buf), fp);

    // Leer cada registro del archivo CSV y llamar a insertarActividad para insertarlo en la base de datos
    while (fgets(buf, sizeof(buf), fp)) {
        char *id_str, *nombre, *descripcion, *temas, *edad, *municipio, *direccion, *contacto, *fecha_str;
        id_str = strtok(buf, ";");
        nombre = strtok(NULL, ";");
        descripcion = strtok(NULL, ";");
        temas = strtok(NULL, ";");
        edad = strtok(NULL, ";");
        municipio = strtok(NULL, ";");
        direccion = strtok(NULL, ";");
        contacto = strtok(NULL, ";");
        fecha_str = strtok(NULL, ";");

        Actividad act;
        strcpy(act.nombre, nombre);
        strcpy(act.descripcion, descripcion);
        strcpy(act.tipo, temas);
        strcpy(act.publico, edad);
        strcpy(act.municipio, municipio);
        strcpy(act.direccion, direccion);
        strcpy(act.encargado, contacto);
        strcpy(act.fecha, fecha_str);

        insertarActividad(usuario, act);
    }

    fclose(fp);
    printf("Datos cargados exitosamente desde el archivo CSV\n");
}