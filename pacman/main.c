#include <stdio.h>

#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "menu.h"

int main()
{
    locate(); // Configura a localiza��o para o idioma padr�o do sistema
    //PlaySound("som.wav", NULL, SND_FILENAME | SND_ASYNC); // Reproduz o som de fundo
    system("color 0A"); // Muda a cor do texto para verde (Windows)
    menu(); // Chama a fun��o menu

    return 0;
}
