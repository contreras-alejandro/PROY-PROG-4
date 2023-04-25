#ifndef MENU_H
#define MENU_H
#define MAX_CHARACTERS_FOR_OPTIONS 3

//FUNCION PARA DEVOLVER LA OPCION SELECCIONADA
int selectOpcion();
//FUNCION PARA IMPRIMIR EL MENU DE INICIO
int printMenuInicio();
//FUNCION PARA IMPRIMIR EL MENU PRINCIPAL
int printMenuPrincipal();


//FUNCION PARA GESTION DEL MENU PRINCIPAL
void menuPrincipal(char *usuario);

int printMenuPerfil();
//FUNCION PARA GESTION DEL MENU DE LOGIN
void menuLogin();
//FUNCION PARA COMPROBAR SI LA OPCION INTRODUCIDA ES VALIDA
int comprobarOpcionValida(int opcion, int numOpciones);


#endif