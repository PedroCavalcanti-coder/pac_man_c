#include <stdio.h>
#include <stdlib.h> // Para system("cls") (Linux/Windows)
#include <windows.h>
#include "pacman.h"

// pacman localization 16y 14x


void move_pacman(int *x, int *y, char direction, int *time_move)
{
    if(kbhit())
    {
        switch (getch()) // Lê a tecla pressionada
        {
            case 'w': // Cima
                //(*y)--;
                printf("Cima\n");
                while(1)
                {
                    *y--;
                    Sleep(*time_move);
                    if(kbhit())
                    {
                        break;
                    }
                }
            case 's': // Baixo
                //(*y)++;
                printf("Baixo\n");
                while(1)
                {
                    *y++;
                    Sleep(*time_move);
                    if(kbhit())
                    {
                        break;
                    }
                }
            case 'a': // Esquerda
                //(*x)--;
                printf("Esquerda\n");
                while(1)
                {
                    *x--;
                    Sleep(*time_move);
                    if(kbhit())
                    {
                        break;
                    }
                }
            case 'd': // Direita
                //(*x)++;
                printf("Direita\n");
                while(1)
                {
                    *x++;
                    Sleep(*time_move);
                    if(kbhit())
                    {
                        break;
                    }
                }
            default:
                break;
        }
    }
}