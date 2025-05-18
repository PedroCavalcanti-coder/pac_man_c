#include <stdio.h>
#include <stdlib.h> // Para system("cls") (Linux/Windows)
#include <string.h> // Para strlen()
#include <locale.h> // Para setlocale()
#include <conio.h> // Para getch() (Windows)
#include <unistd.h> // Para sleep() (Linux)
#include <windows.h> // Para Sleep() (Windows)
#include "game.h"
#include "menu.h"
#include "pacman.h"

extern int MAX_COLUNAS = 50;
extern int MAX_LINHAS = 40;
char  **mapa = NULL;
int  **score = NULL;

void inicializa_mapa() {
    mapa = malloc(MAX_LINHAS * sizeof(char *));
    for (int i = 0; i < MAX_LINHAS; i++) {
        mapa[i] = malloc(MAX_COLUNAS * sizeof(char));
        for (int j = 0; j < MAX_COLUNAS; j++) {
            mapa[i][j] = ' '; // ou qualquer outro caractere inicial
        }
    }


    // Desenha o mapa do jogo

    int linhas = 0;

    FILE *arquivo_mapa = fopen("../mapa.txt", "r");

    if (arquivo_mapa == NULL) {
        perror("Erro ao abrir o arquivo_mapa");
        exit(0);
    }

    while (fgets(mapa[linhas], MAX_COLUNAS, arquivo_mapa) != NULL) {
        // Remove o caractere de nova linha '\n'
        mapa[linhas][strcspn(mapa[linhas], "\n")] = '\0';
        linhas++;
    }

    fclose(arquivo_mapa);

    //printf("%d", linhas); //Operação de Debug

}

void libera_mapa() {
    for (int i = 0; i < MAX_LINHAS; i++) {
        free(mapa[i]);
    }
    free(mapa);
}
void drawing_map()
{
    for (int i = 0; i < MAX_LINHAS-5; i++) {
        printf("\t%s\n", mapa[i]);
    }
}
void write_ranking(int score) {
    FILE *arquivo = fopen("ranking.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d\n", score);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar ranking!\n");
    }
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
    while(1) // Continua até que a tecla '0' seja pressionada
    {
        drawing_map(); // Chama a função para desenhar o mapa
        printf("\t\tScore: %d", score); // Exibe a pontuação (inicialmente 0)

        player_move();

        if(kbhit()) // Verifica se uma tecla foi pressionada
        {
            opcao = getch(); // Lê a tecla pressionada
            if(opcao == '0') // Se a tecla for '0', sai do loop
                break;
        }


        Sleep(300);



        system("cls"); // Limpa a tela (Windows)

    }

    system("cls"); // Limpa a tela (Windows)
    exit(0); // Sair do programa
    system("exit"); // Sair do programa
}
void gamo_over()
{
    // Aqui você pode implementar a lógica para o Game Over
    printf("Game Over!\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch(); // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    menu(); // Chama a função menu novamente
}
void locate()
{
    setlocale(LC_ALL, "Portuguese");
}
