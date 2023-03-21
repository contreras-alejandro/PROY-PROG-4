#include <stdio.h>

int main() {
    FILE *csv;
    char linea[1024];
    csv=fopen("actividades.csv", "r");
    if (!csv) {
        printf("No se ha podido abrir el archivo CSV\n");
        return 1;
    }
    while (fgets(linea, 1024, csv)) {
        printf("%s", linea);
    }
    fclose(csv);
    return 0;
}