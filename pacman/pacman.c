#include <stdio.h>
#include <conio.h> // Para kbhit() e getch() no Windows
#include "pacman.h"
#include "game.h"

void get_score()
{
    // L�gica para ganhar ponto
    score += 8;
    if (score > ranking())
        write_ranking(score);
}

void power_up()
{
    // L�gica para ativar power-up
    printf("Power-up ativado!\n");
    score += 56;
    if (score > ranking())
        write_ranking(score);
}

void kill()
{
    // L�gica para ser morto ou perder vida
    printf("Voc� foi pego!\n");
}

// Variáveis globais para armazenar a última direção
char last_tecla = 0;

void player_move()
{
    int posy = -1;
    int posx = -1;
    char tecla = 0;

    // Verifica se uma tecla foi pressionada e atualiza a direção
    if (kbhit())
    {
        tecla = getch();
        // Se a tecla for uma das válidas, atualiza a direção
        if (tecla == 'w' || tecla == 'a' || tecla == 's' || tecla == 'd')
        {
            last_tecla = tecla;
        }
    }

    // Se houver uma direção válida armazenada, tenta mover
    if (last_tecla != 0)
    {
        // Localiza a posição atual do Pac-Man ('C')
        for (int i = 0; i < MAX_LINHAS - 8; i++)
        {
            for (int j = 0; mapa[i][j] != '\0'; j++)
            {
                if (mapa[i][j] == 'C')
                {
                    posy = i;
                    posx = j;
                }
            }
        }

        if (posx != -1 && posy != -1)
        {
            int ny = posy, nx = posx;

            // Define novo destino baseado na última tecla pressionada
            if (last_tecla == 'w')
                ny--;
            else if (last_tecla == 's')
                ny++;
            else if (last_tecla == 'a')
                nx--;
            else if (last_tecla == 'd')
                nx++;

            char destino = mapa[ny][nx];

            switch (destino)
            {
            case '#':
                // Pare o movimento se bater na parede
                last_tecla = 0;
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
            default:
                // Se for outra coisa, pare o movimento para evitar bugs
                last_tecla = 0;
                break;
            }
        }
    }
}
