#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "pacman.h"
#include "game.h"
#include "ghost.h"

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define PINK "\x1b[35m"
#define CYAN "\x1b[36m"
#define ORANGE "\x1b[38;5;208m"

// Posições globais
int py_anterior = -1, px_anterior = -1;
int py = -1, px = -1;
int py_pacman = -1, px_pacman = -1;

void ghost_move(int novo_py, int novo_px)
{
    if (py_anterior == -1 || px_anterior == -1)
        mapa[py][px] = ' ';
    else
        mapa[py][px] = mapa[novo_py][novo_px];

    mapa[novo_py][novo_px] = '@';
    py_anterior = py;
    px_anterior = px;
    py = novo_py;
    px = novo_px;
}

void ghost()
{
    // Comportamento genérico (vazio por enquanto)
}

void ghost_escape()
{
    for (int i = 0; i < MAX_LINHAS - 8; i++)
    {
        for (int j = 0; mapa[i][j] != '\0'; j++)
        {
            if (mapa[i][j] == 'C')
            {
                py_pacman = i;
                px_pacman = j;
            }
            if (mapa[i][j] == '@')
            {
                py = i;
                px = j;
            }
        }
    }

    if ((py_pacman - 1 == py && px_pacman == px) ||
        (py_pacman + 1 == py && px_pacman == px) ||
        (py_pacman == py && px_pacman - 1 == px) ||
        (py_pacman == py && px_pacman + 1 == px))
    {
        mapa[py][px] = ' ';
        py = -1;
        px = -1;
        return;
    }

    int dy[] = {1, -1, 0, 0};
    int dx[] = {0, 0, 1, -1};
    int max_dist = -1;
    int melhor_py = py, melhor_px = px;

    for (int i = 0; i < 4; i++)
    {
        int novo_py = py + dy[i];
        int novo_px = px + dx[i];

        if (mapa[novo_py][novo_px] != '#' && mapa[novo_py][novo_px] != '@')
        {
            int dist = abs(py_pacman - novo_py) + abs(px_pacman - novo_px);
            if (dist > max_dist)
            {
                max_dist = dist;
                melhor_py = novo_py;
                melhor_px = novo_px;
            }
        }
    }

    if (melhor_py != py || melhor_px != px)
        ghost_move(melhor_py, melhor_px);
}

void red()
{
    // Laço para percorrer as linhas do mapa (limitadas por MAX_LINHAS - 8)
    for (int i = 0; i < MAX_LINHAS - 8; i++)
    {
        // Laço para percorrer as colunas da linha atual até o fim da string
        for (int j = 0; mapa[i][j] != '\0'; j++)
        {
            // Se encontrar o Pac-Man ('C'), armazena sua posição
            if (mapa[i][j] == 'C')
            {
                py_pacman = i;
                px_pacman = j;
            }
            // Se encontrar o fantasma vermelho ('@'), armazena sua posição
            if (mapa[i][j] == '@')
            {
                py = i;
                px = j;
            }
        }
    }

    // Verifica se o fantasma está em uma posição adjacente ao Pac-Man
    if ((py_pacman - 1 == py && px_pacman == px) ||
        (py_pacman + 1 == py && px_pacman == px) ||
        (py_pacman == py && px_pacman - 1 == px) ||
        (py_pacman == py && px_pacman + 1 == px))
    {
        game_over(); // Pac-Man foi alcançado: fim de jogo
    }

    // Vetores de direção: baixo, cima, direita, esquerda
    int dy[] = {1, -1, 0, 0};
    int dx[] = {0, 0, 1, -1};

    // Calcula a distância entre o fantasma e o Pac-Man
    int dist_y = py_pacman - py;
    int dist_x = px_pacman - px;

    int prioridade[4], idx = 0;

    // Define a prioridade de movimentação baseada na maior distância
    if (abs(dist_y) >= abs(dist_x))
    {
        // Prioriza movimentos verticais
        if (dist_y > 0)
            prioridade[idx++] = 0; // Baixo
        else if (dist_y < 0)
            prioridade[idx++] = 1; // Cima

        if (dist_x > 0)
            prioridade[idx++] = 2; // Direita
        else if (dist_x < 0)
            prioridade[idx++] = 3; // Esquerda
    }
    else
    {
        // Prioriza movimentos horizontais
        if (dist_x > 0)
            prioridade[idx++] = 2; // Direita
        else if (dist_x < 0)
            prioridade[idx++] = 3; // Esquerda

        if (dist_y > 0)
            prioridade[idx++] = 0; // Baixo
        else if (dist_y < 0)
            prioridade[idx++] = 1; // Cima
    }

    // Preenche as direções restantes com prioridade menor
    for (int i = 0; i < 4; i++)
    {
        bool existe = false;
        for (int j = 0; j < idx; j++)
            if (prioridade[j] == i)
                existe = true;
        if (!existe)
            prioridade[idx++] = i;
    }

    // Tenta mover o fantasma na direção de maior prioridade possível
    for (int i = 0; i < 4; i++)
    {
        int dir = prioridade[i];
        int novo_py = py + dy[dir];
        int novo_px = px + dx[dir];

        // Verifica se a nova posição não é uma parede ou outro fantasma
        if (mapa[novo_py][novo_px] != '#' && mapa[novo_py][novo_px] != '@')
        {
            ghost_move(novo_py, novo_px); // Move o fantasma
            break;                        // Move uma única vez por chamada
        }
    }
}

void pink()
{
}

void cyan()
{
}
void orange()
{
}