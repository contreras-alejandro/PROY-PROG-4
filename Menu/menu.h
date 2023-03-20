#ifndef MENU_H
#define MENU_H

#define MAX_CHARACTERS_FOR_OPTIONS 3

int selectOpcion();
int printMenuInicio();
int printMenuPrincipal();
int printGestionAct();
void menuInicio();
void menuPrincipal(char *usuario);
void menuGestionAct(char *usuario);
void menuLogin();
int comprobarOpcionValida(int opcion, int numOpciones);


#endif