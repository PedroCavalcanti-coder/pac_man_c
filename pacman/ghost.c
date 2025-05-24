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
        game_over();
    }

    int dy[] = {1, -1, 0, 0};
    int dx[] = {0, 0, 1, -1};

    int dist_y = py_pacman - py;
    int dist_x = px_pacman - px;

    int prioridade[4], idx = 0;

    if (abs(dist_y) >= abs(dist_x))
    {
        if (dist_y > 0)
            prioridade[idx++] = 0;
        else if (dist_y < 0)
            prioridade[idx++] = 1;

        if (dist_x > 0)
            prioridade[idx++] = 2;
        else if (dist_x < 0)
            prioridade[idx++] = 3;
    }
    else
    {
        if (dist_x > 0)
            prioridade[idx++] = 2;
        else if (dist_x < 0)
            prioridade[idx++] = 3;

        if (dist_y > 0)
            prioridade[idx++] = 0;
        else if (dist_y < 0)
            prioridade[idx++] = 1;
    }

    for (int i = 0; i < 4; i++)
    {
        bool existe = false;
        for (int j = 0; j < idx; j++)
            if (prioridade[j] == i)
                existe = true;
        if (!existe)
            prioridade[idx++] = i;
    }

    for (int i = 0; i < 4; i++)
    {
        int dir = prioridade[i];
        int novo_py = py + dy[dir];
        int novo_px = px + dx[dir];
        if (mapa[novo_py][novo_px] != '#' && mapa[novo_py][novo_px] != '@')
        {
            ghost_move(novo_py, novo_px);
            break;
        }
    }
}

void pink()
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
        game_over();
    }

    int dy[] = {1, -1, 0, 0};
    int dx[] = {0, 0, 1, -1};

    int target_y = py_pacman;
    int target_x = px_pacman;

    int diff_y = py_pacman - py;
    int diff_x = px_pacman - px;

    if (abs(diff_y) > abs(diff_x))
        target_y += (diff_y > 0) ? 2 : -2;
    else
        target_x += (diff_x > 0) ? 2 : -2;

    int prioridade[4], idx = 0;
    int dist_y = target_y - py;
    int dist_x = target_x - px;

    if (abs(dist_y) >= abs(dist_x))
    {
        if (dist_y > 0)
            prioridade[idx++] = 0;
        else if (dist_y < 0)
            prioridade[idx++] = 1;

        if (dist_x > 0)
            prioridade[idx++] = 2;
        else if (dist_x < 0)
            prioridade[idx++] = 3;
    }
    else
    {
        if (dist_x > 0)
            prioridade[idx++] = 2;
        else if (dist_x < 0)
            prioridade[idx++] = 3;

        if (dist_y > 0)
            prioridade[idx++] = 0;
        else if (dist_y < 0)
            prioridade[idx++] = 1;
    }

    for (int i = 0; i < 4; i++)
    {
        bool existe = false;
        for (int j = 0; j < idx; j++)
            if (prioridade[j] == i)
                existe = true;
        if (!existe)
            prioridade[idx++] = i;
    }

    for (int i = 0; i < 4; i++)
    {
        int dir = prioridade[i];
        int novo_py = py + dy[dir];
        int novo_px = px + dx[dir];
        if (mapa[novo_py][novo_px] != '#' && mapa[novo_py][novo_px] != '@')
        {
            ghost_move(novo_py, novo_px);
            break;
        }
    }
}

cyan()
{
}
orange()
{
}