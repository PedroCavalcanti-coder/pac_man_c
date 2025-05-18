#include <stdio.h>

#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "menu.h"

int main()
{
    locate(); // Configura a localização para o idioma padrão do sistema
    //PlaySound("som.wav", NULL, SND_FILENAME | SND_ASYNC); // Reproduz o som de fundo
    system("color 0A"); // Muda a cor do texto para verde (Windows)
    menu(); // Chama a função menu

    return 0;
}
