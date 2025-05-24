#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "menu.h"

int main()
{
    locate();           // Configura a localiza��o para o idioma padr�o do sistema
    system("color 0A"); // Muda a cor do texto para verde (Windows)
    srand(time(NULL));  // Inicializa o gerador de n�meros aleat�rios
    menu();             // Chama a fun��o

    return 0;
}
