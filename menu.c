#include <stdio.h>
#include <stdlib.h> // Para system("cls") (Linux/Windows)
#include <string.h> // Para strlen()
#include <locale.h> // Para setlocale()
#include <conio.h> // Para getch() (Windows)
#include <unistd.h> // Para sleep() (Linux)
#include <windows.h> // Para Sleep() (Windows)
#include "menu.h"

#define MAX_LINHAS 30
#define MAX_COLUNAS 50


void menu()
{

    FILE *arquivo_menu;
    char menu[MAX_LINHAS][MAX_COLUNAS];
    int linhas = 0;
    arquivo_menu = fopen("../menu.txt", "r");

    if (arquivo_menu == NULL) {
        perror("Erro ao abrir o arquivo_menu");
        exit(EXIT_FAILURE);
    }

    while (fgets(menu[linhas], MAX_COLUNAS, arquivo_menu) != NULL) {
        // Remove o caractere de nova linha '\n'
        menu[linhas][strcspn(menu[linhas], "\n")] = '\0';
        linhas++;
    }

    fclose(arquivo_menu);

    // Exibir o menu
    for (int i = 0; i < linhas; i++) {
        printf("%s\n", menu[i]);
    }

    char opcao;

    opcao = getch(); // Aguarda a tecla pressionada
    switch (opcao) {
        case '1':
            system("cls"); // Limpa a tela (Windows)
            start_game();

        case '3':
            system("cls"); // Limpa a tela (Windows)
            instruct(); // Chama a função para mostrar as instruções
            break;
            // Aqui você pode chamar a função para mostrar as instruções

        case '2':
            system("cls"); // Limpa a tela (Windows)
            open_ranking(ranking()); // Chama a função para abrir o ranking
            break;
        
        case '4':
            printf("Sair\n");
            exit(0); // Sair do programa
            system("exit");// Sair do programa
            break;
    }

}
void start_game()
{
    //char opcao;

    //game_loop(); // Chama a função para o loop do jogo 
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
    printf("  Você é o Pac-Man (P).\n");
    printf("=============================\n\n");


    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch(); // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    menu(); // Chama a função menu novamente
}
int ranking()
{
    // Aqui você pode implementar a lógica para abrir o ranking
    FILE *arquivo_ranking;
    char ranking[20];

    arquivo_ranking = fopen("../ranking.txt", "r");
    if (arquivo_ranking == NULL) {
        perror("Erro ao abrir o arquivo_ranking");
        exit(EXIT_FAILURE);
    }

    // Exibir o ranking
    while (fgets(ranking, sizeof(ranking), arquivo_ranking) != NULL) {
        // Remove o caractere de nova linha '\n'
        ranking[strcspn(ranking, "\n")] = '\0';
        printf("%s\n", ranking);
    } 

    fclose(arquivo_ranking);

    return atoi(ranking); // Retorna a pontuação do ranking
}
void open_ranking(int pontuacao)
{
    printf("===== RANKING =====\n");
    printf("1. Jogador1 - %d pontos\n", pontuacao);
    printf("\nPressione qualquer tecla para voltar ao menu...\n");
    getch(); // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    menu(); // Chama a função menu novamente
}