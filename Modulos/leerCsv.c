#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Modulos/gestionBD.h"
#include "../Modulos/gestionAdmin.h"




void cargarCsv(char* archivoCSV, char* usuario) {
    FILE* archivo_csv = fopen(archivoCSV, "r");

    if (archivo_csv == NULL) {
        printf("Error al abrir el archivo CSV\n");
        return;
    }

    char linea[1024];
    int contador_linea = 0;

    while (fgets(linea, 1024, archivo_csv)) {
        if (contador_linea > 0) {
            char* token;
            char* valores[9];
            int indice_valor = 0;
            Actividad act;

            token = strtok(linea, ";");
            while (token != NULL) {
                valores[indice_valor++] = token;
                token = strtok(NULL, ";");
            }

            strcpy(act.nombre, valores[1]);
            strcpy(act.descripcion, valores[2]);
            strcpy(act.tipo, valores[3]);
            strcpy(act.publico, valores[4]);
            strcpy(act.municipio, valores[5]);
            strcpy(act.direccion, valores[6]);
            strcpy(act.encargado, valores[7]);
            strcpy(act.fecha, valores[8]);

            insertarActividad(usuario, act);
        }

        contador_linea++;
    }

    fclose(archivo_csv);
}
   



