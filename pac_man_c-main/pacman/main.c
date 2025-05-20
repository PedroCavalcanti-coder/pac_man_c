#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "menu.h"

int main()
{
    locate(); // Configura a localização para o idioma padrão do sistema
    // Toca o som de forma assíncrona (continua executando o resto do código)
    PlaySound("./playing-pac-man.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("color 0A"); // Muda a cor do texto para verde (Windows)
    menu(); // Chama a função

    return 0;
}
