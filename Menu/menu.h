#ifndef MENU_H
#define MENU_H

#define MAX_CHARACTERS_FOR_OPTIONS 3

int selectOpcion();
int printMenuInicio();
int printMenuPrincipal();
int printGestionAct();
void menuInicio();
void menuPrincipal();
void menuGestionAct();
int comprobarOpcionValida(int opcion, int numOpciones);


#endif