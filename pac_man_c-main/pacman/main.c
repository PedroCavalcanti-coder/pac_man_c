#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "menu.h"

int main()
{
    locate(); // Configura a localiza��o para o idioma padr�o do sistema
    // Toca o som de forma ass�ncrona (continua executando o resto do c�digo)
    PlaySound("./playing-pac-man.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("color 0A"); // Muda a cor do texto para verde (Windows)
    menu(); // Chama a fun��o

    return 0;
}
