#include <stdio.h>
#include <conio.h> // Para kbhit() e getch() no Windows
#include "pacman.h"
#include "game.h"

void get_score() {
    // Lógica para ganhar ponto
    score += 8;
    if(score > ranking()) write_ranking(score);
}

void power_up() {
    // Lógica para ativar power-up
    printf("Power-up ativado!\n");
    score += 56;
     if(score > ranking()) write_ranking(score);
}

void kill() {
    // Lógica para ser morto ou perder vida
    printf("Você foi pego!\n");
}

void player_move()
{
    int posy = -1;
    int posx = -1;
    char tecla;

    if (kbhit())
    {
        // Localiza a posição atual do Pac-Man ('C')
        for (int i = 0; i < MAX_LINHAS - 8; i++) {
            for (int j = 0; mapa[i][j] != '\0'; j++) {
                if (mapa[i][j] == 'C') {
                    posy = i;
                    posx = j;
                }
            }
        }

        if (posx != -1 && posy != -1)
        {
            tecla = getch();
            int ny = posy, nx = posx;

            // Define novo destino
            if (tecla == 'w') ny--;
            else if (tecla == 's') ny++;
            else if (tecla == 'a') nx--;
            else if (tecla == 'd') nx++;

            char destino = mapa[ny][nx];

            switch (destino)
            {
                case '#':
                    // Não se move
                    break;
                case ' ':
                    mapa[ny][nx] = 'C';
                    mapa[posy][posx] = ' ';
                    break;
                case '.':
                    get_score();
                    mapa[ny][nx] = 'C';
                    mapa[posy][posx] = ' ';
                    break;
                case 'o':
                    power_up();
                    mapa[ny][nx] = 'C';
                    mapa[posy][posx] = ' ';
                    break;
                case '@':
                    kill();
                    mapa[ny][nx] = 'C';
                    mapa[posy][posx] = ' ';
                    break;
            }
        }
    }
}
