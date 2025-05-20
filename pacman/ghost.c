#include <stdio.h>
#include "pacman.h"
#include "game.h"

// Defini��es de cor ANSI
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define PINK "\x1b[35m"
#define CYAN "\x1b[36m"
#define ORANGE "\x1b[38;5;208m"

int py_anterior = -1, px_anterior = -1;
int py_futuro = -1, px_futuro = -1;
int py = -1, px = -1;
int py_pacman = -1, px_pacman = -1;

void ghost()
{
    // Localiza a posição atual do Pac-Man ('C')
    for (int i = 0; i < MAX_LINHAS - 8; i++)
    {
        for (int j = 0; mapa[i][j] != '\0'; j++)
        {
            if (mapa[i][j] == 'C')
            {
                py_pacman = i;
                px_pacman = j;
            }
        }
    }
    // Localiza a posição atual do fantasma ('@')
    for (int i = 0; i < MAX_LINHAS - 8; i++)
    {
        for (int j = 0; mapa[i][j] != '\0'; j++)
        {
            if (mapa[i][j] == '@')
            {
                py = i;
                px = j;
            }
        }
    }

    // Calcula a nova posição do fantasma com base na posição do pacman
    int ny = py, nx = px;
    if (py < py_pacman)
    {
        if (mapa[py + 1][px] != '#') // Se o estado para onde quero ir não for uma parede
        {
            ny = py + 1;
            // Se o estado para onde quero ir for habitavel:
            // ele recebe meu valor[x]
            // e o meu estado atual vai receber o valor anterior(antes de eu habita-lo)[x]

            // a posição onde o fantasma vai habitar recebe o valor do fantasma
            mapa[ny][px] = '@';
            // a posição onde o fantasma habita vai receber o valor anterior(antes de dele habita-lo)
            // Se o fantasma já tinha uma posição anterior, atualiza a posição anterior
            if (py_anterior != -1 && px_anterior != -1)
            {
                mapa[py][px] = mapa[py_anterior][px_anterior];
            }
            else
            {
                // Se não, apenas limpa a posição atual do fantasma
                mapa[py][px] = ' ';
            }
            // Atualiza a posição anterior do fantasma
            py_anterior = ny;
            px_anterior = px;
        }
        else
        {
            // Se o estado para onde quero ir for uma parede, executa a lógica para calcular a nova rota
            // EXEMPLO: Se o fantasma não puder se mover para baixo, tenta mover para cima
        }
    }
    else if (py > py_pacman)
    {
        if (mapa[py - 1][px] != '#') // Se o estado para onde quero ir não for uma parede
        {
            ny = py - 1;
            // Se o estado para onde quero ir for habitavel:
            // ele recebe meu valor[x]
            // e o meu estado atual vai receber o valor anterior(antes de eu habita-lo)[x]

            // a posição onde o fantasma vai habitar recebe o valor do fantasma
            mapa[ny][px] = '@';
            // a posição onde o fantasma habita vai receber o valor anterior(antes de dele habita-lo)
            // Se o fantasma já tinha uma posição anterior, atualiza a posição anterior
            if (py_anterior != -1 && px_anterior != -1)
            {
                mapa[py][px] = mapa[py_anterior][px_anterior];
            }
            else
            {
                // Se não, apenas limpa a posição atual do fantasma
                mapa[py][px] = ' ';
            }
            // Atualiza a posição anterior do fantasma
            py_anterior = ny;
            px_anterior = px;
        }
        else
        {
            // Se o estado para onde quero ir for uma parede, executa a lógica para calcular a nova rota
            // EXEMPLO: Se o fantasma não puder se mover para baixo, tenta mover para cima
        }
    }
    if (px < px_pacman)
    {
        if (mapa[py][px + 1] != '#') // Se o estado para onde quero ir não for uma parede
        {
            ny = px + 1;
            // Se o estado para onde quero ir for habitavel:
            // ele recebe meu valor[x]
            // e o meu estado atual vai receber o valor anterior(antes de eu habita-lo)[x]

            // a posição onde o fantasma vai habitar recebe o valor do fantasma
            mapa[ny][px] = '@';
            // a posição onde o fantasma habita vai receber o valor anterior(antes de dele habita-lo)
            // Se o fantasma já tinha uma posição anterior, atualiza a posição anterior
            if (py_anterior != -1 && px_anterior != -1)
            {
                mapa[py][px] = mapa[py_anterior][px_anterior];
            }
            else
            {
                // Se não, apenas limpa a posição atual do fantasma
                mapa[py][px] = ' ';
            }
            // Atualiza a posição anterior do fantasma
            py_anterior = ny;
            px_anterior = px;
        }
        else
        {
            // Se o estado para onde quero ir for uma parede, executa a lógica para calcular a nova rota
            // EXEMPLO: Se o fantasma não puder se mover para baixo, tenta mover para cima
        }
    }
    else if (px > px_pacman)
    {
        if (mapa[py][px - 1] != '#') // Se o estado para onde quero ir não for uma parede
        {
            ny = px - 1;
            // Se o estado para onde quero ir for habitavel:
            // ele recebe meu valor[x]
            // e o meu estado atual vai receber o valor anterior(antes de eu habita-lo)[x]

            // a posição onde o fantasma vai habitar recebe o valor do fantasma
            mapa[ny][px] = '@';
            // a posição onde o fantasma habita vai receber o valor anterior(antes de dele habita-lo)
            // Se o fantasma já tinha uma posição anterior, atualiza a posição anterior
            if (py_anterior != -1 && px_anterior != -1)
            {
                mapa[py][px] = mapa[py_anterior][px_anterior];
            }
            else
            {
                // Se não, apenas limpa a posição atual do fantasma
                mapa[py][px] = ' ';
            }
            // Atualiza a posição anterior do fantasma
            py_anterior = ny;
            px_anterior = px;
        }
        else
        {
            // Se o estado para onde quero ir for uma parede, executa a lógica para calcular a nova rota
            // EXEMPLO: Se o fantasma não puder se mover para baixo, tenta mover para cima
        }
    }
}
void ghost_move()
{
    // Lógica para mover o fantasma
    // Aqui você pode implementar a lógica de movimento do fantasma
    // Por exemplo, mover o fantasma em direção ao pacman
    // ou de forma aleatória
    int ny = py, nx = px;

    switch (mapa[ny][nx])
    {
    case '#':
        // Pare o movimento se bater na parede
        break;
    case ' ':
        mapa[ny][nx] = '@';
        mapa[py][px] = ' ';
        break;
    case '.':
        mapa[ny][nx] = '@';
        mapa[py][px] = '.';
        break;
    case 'o':
        mapa[ny][nx] = '@';
        mapa[py][px] = 'o';
        break;
    case '@':
        mapa[ny][nx] = '@';
        mapa[py][px] = '@';
        break;
    default:
        // Se for outra coisa, pare o movimento para evitar bugs
        break;
    }
}
void pink()
{
}
void red()
{
}
void cyan()
{
}
void orange()
{
}
