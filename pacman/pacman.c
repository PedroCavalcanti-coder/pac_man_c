#include <stdio.h>
#include <conio.h> // Para kbhit() e getch() no Windows
#include <time.h>
#include <stdbool.h>
#include "pacman.h"
#include "ghost.h"
#include "game.h"

bool bool_power_up = false;
clock_t power_up_start_time;

void get_score()
{
    // L�gica para ganhar ponto
    score += 8;
    if (score > ranking())
        write_ranking(score);
}

void power_up()
{
    score += 56;
    if (score > ranking())
        write_ranking(score);

    bool_power_up = true;
    power_up_start_time = clock(); // salva o tempo que o power-up começou
}

int verifica_power_up()
{
    if (bool_power_up)
    {
        double segundos = (double)(clock() - power_up_start_time) / CLOCKS_PER_SEC;
        if (segundos >= 10.0)
        {
            bool_power_up = false;
            return 0; // power-up expirado
        }
        return 1; // power-up ativo
    }
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
            default:
                // Se for outra coisa, pare o movimento para evitar bugs
                last_tecla = 0;
                break;
            }
        }
    }
}
