#include <stdio.h>
#include <stdlib.h>  // Para system("cls") (Linux/Windows)
#include <string.h>  // Para strlen()
#include <locale.h>  // Para setlocale()
#include <conio.h>   // Para getch() (Windows)
#include <unistd.h>  // Para sleep() (Linux)
#include <windows.h> // Para Sleep() (Windows)
#include "game.h"
#include "menu.h"

#include <windows.h>
#include <mmsystem.h>

#define YELLOW "\033[33m"
#define PURPLE "\033[35m"
#define GREEN "\033[0;32m"
#define RED "\x1b[31m"

int playng_sound = 0; // Variável para controlar o som

void menu()
{
    if (playng_sound == 0)
    {
        // Toca o som de forma ass�ncrona (continua executando o resto do c�digo)
        PlaySound("./playing-pac-man.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        playng_sound = 1; // Define a variável como 1 para indicar que o som está tocando
    }

    bool_game_over = 1; // Define game_over como verdadeiro para que o jogo inicie
    char menu[MAX_COLUNAS][MAX_LINHAS];

    FILE *arquivo_menu;
    int linhas = 0;
    arquivo_menu = fopen("menu.txt", "r");

    if (arquivo_menu == NULL)
    {
        perror("Erro ao abrir o arquivo_menu");
        exit(0);
    }

    while (fgets(menu[linhas], MAX_COLUNAS, arquivo_menu) != NULL)
    {
        // Remove o caractere de nova linha '\n'
        menu[linhas][strcspn(menu[linhas], "\n")] = '\0';
        linhas++;
    }

    fclose(arquivo_menu);

    printf(YELLOW);
    printf("\t ######     ###      ######           ##   ##     ###     ##    #       ****** \n");
    printf("\t #     #   #   #    #                # # # #    #   #    # #   #     ** ** \n");
    printf("\t #     #  #     #   #         ----   #  #  #   #     #   #  #  #    * * \n");
    printf("\t ######   #######   #         ----   #     #   #######   #   # #       * > \n");
    printf("\t #        #     #   #                #     #   #     #   #    ##     * * \n");
    printf("\t #        #     #   #                #     #   #     #   #     #      ** ** \n");
    printf("\t #        #     #    ######          #     #   #     #   #     #      ****** \n");

    printf(PURPLE);
    printf("\n\tCriado por Pedro H. Silva Cavalcanti\n\n");

    // Exibir o menu
    printf(GREEN);
    for (int i = 0; i < linhas; i++)
    {
        printf("\t%s\n", menu[i]);
    }

    printf(RED);
    printf("\n\tAVISO: JOGE EM TELA CHEIA PARA EVITAR BUGS!\n\n");
    printf(GREEN); // Para voltar ao normal

    char opcao;

    opcao = getch(); // Aguarda a tecla pressionada
    switch (opcao)
    {
    case '1':
        // Para a música
        PlaySound(NULL, 0, 0);
        playng_sound = 0;
        system("cls"); // Limpa a tela (Windows)
        start_game();
        break;

    case '3':
        system("cls"); // Limpa a tela (Windows)
        instruct();    // Chama a fun��o para mostrar as instru��es
        break;
        // Aqui voc� pode chamar a fun��o para mostrar as instru��es

    case '2':
        system("cls");           // Limpa a tela (Windows)
        open_ranking(ranking()); // Chama a fun��o para abrir o ranking
        break;

    case '4':
        // Para a música
        PlaySound(NULL, 0, 0);
        system("cls");
        exit(0); // Sair do programa
    }
}
void instruct()
{
    printf("===== PAC-MAN CLI GAME =====\n");
    printf("Controles:\n");
    printf("  W - Mover para cima\n");
    printf("  A - Mover para esquerda\n");
    printf("  S - Mover para baixo\n");
    printf("  D - Mover para direita\n");
    printf("Objetivo:\n");
    printf("  Colete todos os pontos (.) e evite os fantasmas (G)!\n");
    printf("  Você ê o Pac-Man (P).\n");
    printf("=============================\n\n");

    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch();       // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    playng_sound = 1;
    menu(); // Chama a fun��o menu novamente
}
void open_ranking(int pontuacao)
{
    printf("===== RANKING =====\n");
    printf("1. Jogador1 - %d pontos\n", pontuacao);
    printf("\nPressione qualquer tecla para voltar ao menu...\n");
    getch();       // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    playng_sound = 1;
    menu(); // Chama a fun��o menu novamente
}
