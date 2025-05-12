#include <stdio.h>
#include <stdlib.h> // Para system("cls") (Linux/Windows)
#include <string.h> // Para strlen()
#include <locale.h> // Para setlocale()
#include <conio.h> // Para getch() (Windows)
#include <unistd.h> // Para sleep() (Linux)
#include <windows.h> // Para Sleep() (Windows)
#include "pacman.h"

#define MAX_LINHAS 100
#define MAX_COLUNAS 50


int main()
{
    //PlaySound("som.wav", NULL, SND_FILENAME | SND_ASYNC); // Reproduz o som de fundo
    system("color 0A"); // Muda a cor do texto para verde (Windows)
    locate(); // Chama a função locate para configurar a localização
    menu(); // Declaração da função menu

    return 0;
}

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
            open_ranking(); // Chama a função para abrir o ranking
            break;
        
        case '4':
            printf("Sair\n");
            exit(0); // Sair do programa
            system("exit");// Sair do programa
            break;
    }

}

start_game()
{
    char opcao;

    do // Loop infinito para o jogo
    {
        if(kbhit()) // Verifica se uma tecla foi pressionada
        {
            opcao = getch(); // Lê a tecla pressionada
            if(opcao == '0') // Se a tecla for '0', sai do loop
                break;
        }
        
        drawing_map(); // Chama a função para desenhar o mapa
        
        Sleep(500); // Pausa por 100 milissegundos (Windows)

        system("cls"); // Limpa a tela (Windows)

    } while(1); // Continua até que a tecla '0' seja pressionada
    
    system("cls"); // Limpa a tela (Windows)
    exit(0); // Sair do programa
    system("exit"); // Sair do programa
    
}

void drawing_map()
{
    // Desenha o mapa do jogo

    FILE *arquivo_mapa;
    char mapa[MAX_LINHAS][MAX_COLUNAS];
    int linhas = 0;

    arquivo_mapa = fopen("../mapa.txt", "r");
    if (arquivo_mapa == NULL) {
        perror("Erro ao abrir o arquivo_mapa");
        exit(EXIT_FAILURE);
    }

    while (fgets(mapa[linhas], MAX_COLUNAS, arquivo_mapa) != NULL) {
        // Remove o caractere de nova linha '\n'
        mapa[linhas][strcspn(mapa[linhas], "\n")] = '\0';
        linhas++;
    }

    fclose(arquivo_mapa);

    // Exibir o mapa
    for (int i = 0; i < linhas; i++) {
        printf("%s\n", mapa[i]);
    }

}
open_ranking()
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

    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch(); // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    menu(); // Chama a função menu novamente
}
instruct()
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
void locate()
{
    setlocale(LC_ALL,""); // Configura a localização para o idioma padrão do sistema
}