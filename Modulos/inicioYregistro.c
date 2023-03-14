#include <stdio.h>
#include "../../sqlite/sqlite3.h"


sqlite3* abrirConexion(char* nombre_base) {
    sqlite3 *db;
    char *error_message = 0;
    int resultado_apertura;

    resultado_apertura = sqlite3_open(nombre_base, &db);

    //si el valor es 0, todo bien! sino, error en apertura

    if (resultado_apertura != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    } else {
        printf("Conexión a la base de datos establecida correctamente.\n");
        return db;
    }
}
