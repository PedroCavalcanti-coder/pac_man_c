#include <stdio.h>
#include <stdlib.h>   // Para system("cls") (Linux/Windows)
#include <string.h>   // Para strlen()
#include <locale.h>   // Para setlocale()
#include <conio.h>    // Para getch() (Windows)
#include <windows.h>  // Para Sleep() (Windows)
#include <mmsystem.h> // Para PlaySound()
#include "game.h"
#include "menu.h"
#include "pacman.h"
#include "ghost.h"

// Definições de cores ANSI
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define WHITE "\x1b[37m"
#define DARK_BLUE "\x1b[34m" // Azul escuro
// #define RESET "\x1b[0m"

#define RED "\x1b[31m"
#define PINK "\x1b[35m"
#define CYAN "\x1b[36m"
#define ORANGE "\x1b[38;5;208m"

extern int MAX_COLUNAS = 50;
extern int MAX_LINHAS = 40;
char **mapa = NULL;
int **score = NULL;

// Função para ajustar o tamanho da janela do console
void setConsoleSize(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // width e height aqui são em pixels aproximados; ajuste conforme necessário
    // Cada caractere no console normalmente é 8x16 pixels (depende da fonte)
    int charWidth = 9;   // Aproximação da largura de um caractere em pixels
    int charHeight = 16; // Aproximação da altura de um caractere em pixels

    MoveWindow(console, r.left, r.top, width * charWidth, height * charHeight, TRUE);
}

// Função para ajustar o tamanho do buffer do console
void setConsoleBufferSize(int width, int height)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize = {(SHORT)width, (SHORT)height};
    SetConsoleScreenBufferSize(hOut, newSize);
}

void limparTela()
{
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void inicializa_mapa()
{
    // Ajusta buffer e janela para o tamanho do mapa + margem
    int margem_largura = 5;
    int margem_altura = 5;

    setConsoleBufferSize(MAX_COLUNAS + margem_largura, MAX_LINHAS + margem_altura);
    setConsoleSize(MAX_COLUNAS + margem_largura, MAX_LINHAS + margem_altura);

    mapa = malloc(MAX_LINHAS * sizeof(char *));
    for (int i = 0; i < MAX_LINHAS; i++)
    {
        mapa[i] = malloc(MAX_COLUNAS * sizeof(char));
        for (int j = 0; j < MAX_COLUNAS; j++)
        {
            mapa[i][j] = ' '; // ou qualquer outro caractere inicial
        }
    }

    // Desenha o mapa do jogo

    int linhas = 0;

    FILE *arquivo_mapa = fopen("mapa.txt", "r");

    if (arquivo_mapa == NULL)
    {
        perror("Erro ao abrir o arquivo_mapa");
        exit(0);
    }

    while (fgets(mapa[linhas], MAX_COLUNAS, arquivo_mapa) != NULL)
    {
        // Remove o caractere de nova linha '\n'
        mapa[linhas][strcspn(mapa[linhas], "\n")] = '\0';
        linhas++;
        if (linhas >= MAX_LINHAS)
            break; // evita overflow
    }

    fclose(arquivo_mapa);

    // printf("%d", linhas); //Operação de Debug
}

void libera_mapa()
{
    for (int i = 0; i < MAX_LINHAS; i++)
    {
        free(mapa[i]);
    }
    free(mapa);
}

void drawing_map()
{
    for (int i = 0; i < MAX_LINHAS - 8; i++)
    {
        printf("\t"); // Tab para centralizar horizontalmente
        for (int j = 0; mapa[i][j] != '\0'; j++)
        {
            switch (mapa[i][j])
            {
            case '#':
                printf(DARK_BLUE);
                break;
            case '.':
                printf(WHITE);
                break;
            case 'C':
                printf(YELLOW);
                break;
            case '@':
                printf(RED);
                break;
            default:
                printf(GREEN);
                break;
            }
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
    printf(GREEN); // Garante que tudo volte ao normal depois
}

void write_ranking(int score)
{
    FILE *arquivo = fopen("ranking.txt", "w");
    if (arquivo != NULL)
    {
        fprintf(arquivo, "%d\n", score);
        fclose(arquivo);
    }
    else
    {
        printf("Erro ao salvar ranking!\n");
    }
}

int ranking()
{
    // Aqui você pode implementar a lógica para abrir o ranking
    FILE *arquivo_ranking;
    char ranking[20];

    arquivo_ranking = fopen("ranking.txt", "r");
    if (arquivo_ranking == NULL)
    {
        perror("Erro ao abrir o arquivo_ranking");
        exit(0);
    }

    // Exibir o ranking
    while (fgets(ranking, sizeof(ranking), arquivo_ranking) != NULL)
    {
        // Remove o caractere de nova linha '\n'
        ranking[strcspn(ranking, "\n")] = '\0';
    }

    fclose(arquivo_ranking);

    return atoi(ranking); // Retorna a pontuação do ranking
}

void start_game()
{
    inicializa_mapa();
    game_loop(); // Chama a função para o loop do jogo
}

void game_loop()
{
    char opcao = ' ';
    // Loop infinito para o jogo
    while (1) // Continua até que a tecla '0' seja pressionada
    {

        ghost(); // Chama a função para o fantasma
        player_move();
        if (kbhit()) // Verifica se uma tecla foi pressionada
        {
            opcao = getch();  // Lê a tecla pressionada
            if (opcao == '0') // Se a tecla for '0', sai do loop
                break;
        }

        limparTela();
        drawing_map(); // Chama a função para desenhar o mapa
        printf(YELLOW);
        printf("\t\tScore: %d", score); // Exibe a pontuação (inicialmente 0)
        printf(GREEN);

        Sleep(300);
    }

    limparTela();   // Limpa a tela (Windows)
    exit(0);        // Sair do programa
    system("exit"); // Sair do programa
}

void gamo_over()
{
    // Aqui você pode implementar a lógica para o Game Over
    printf("Game Over!\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch();       // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    menu();        // Chama a função menu novamente
}

void locate()
{
    setlocale(LC_ALL, "Portuguese");
}
