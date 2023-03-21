#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

typedef struct {
    int id;
    char nombre[MAX_LENGTH];
    char resumen[MAX_LENGTH];
    char temas[MAX_LENGTH];
    char edad[MAX_LENGTH];
    char municipio[MAX_LENGTH];
    char direccion[MAX_LENGTH];
    char contacto[MAX_LENGTH];
    char fecha[MAX_LENGTH];
} Actividad;

int main() {
    FILE *csv;
    char linea[1024];
    Actividad actividades[300]; 
    int i = 0;

    csv = fopen("actividades.csv", "r");
    if (!csv) {
        printf("No se ha podido abrir el CSV\n");
        return 1;
    }

    while (fgets(linea, 1024, csv) && i < 300) {
        sscanf(linea, "%d;%%[^;];%%[^;];%%[^;];%%[^;];%%[^;];%%[^;];%%[^;]",
               &actividades[i].id, actividades[i].nombre, actividades[i].resumen, actividades[i].temas,
               actividades[i].edad, actividades[i].municipio, actividades[i].direccion, actividades[i].contacto,
               actividades[i].fecha);
        i++;
    }

    for (int j = 0; j < i; j++) {
        printf("ID: %d\n", actividades[j].id);
        printf("Nombre: %s\n", actividades[j].nombre);
        printf("Resumen: %s\n", actividades[j].resumen);
        printf("Temas: %s\n", actividades[j].temas);
        printf("Edad: %s\n", actividades[j].edad);
        printf("Municipio: %s\n", actividades[j].municipio);
        printf("Dirección: %s\n", actividades[j].direccion);
        printf("Contacto: %s\n", actividades[j].contacto);
        printf("Fecha: %s\n", actividades[j].fecha);
        printf("\n");
    }

    fclose(csv);
    return 0;
}