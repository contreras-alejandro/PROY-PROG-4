#include <stdio.h>
#include <windows.h>
#include "../Menu/menu.h"

int main() {
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hConsole, 1);   
    menuAdmin();

    
    return 0;
}