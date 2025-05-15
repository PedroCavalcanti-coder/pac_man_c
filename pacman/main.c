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

char mapa[MAX_LINHAS][MAX_COLUNAS];

void locate()
{
    setlocale(LC_ALL,""); // Configura a localiza��o para o idioma padr�o do sistema
}
void drawing_map()
{
    // Desenha o mapa do jogo

    FILE *arquivo_mapa;
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

    printf("Score: 0\n\n"); // Exibe a pontua��o (inicialmente 0)
    // Exibir o mapa
    for (int i = 0; i < linhas; i++) {
        printf("%s\n", mapa[i]);
    }

}


void game_over()
{
    // Aqui voc� pode implementar a l�gica para o Game Over
    printf("Game Over!\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch(); // Aguarda a tecla pressionada
    system("cls"); // Limpa a tela (Windows)
    menu(); // Chama a fun��o menu novamente
}
void game_loop()
{
    char opcao;
    do // Loop infinito para o jogo
    {
        if(kbhit()) // Verifica se uma tecla foi pressionada
        {
            opcao = getch(); // L� a tecla pressionada
            if(opcao == '0') // Se a tecla for '0', sai do loop
                break;
        }

        drawing_map(); // Chama a fun��o para desenhar o mapa

        Sleep(500); // Pausa por 100 milissegundos (Windows)

        system("cls"); // Limpa a tela (Windows)

    } while(1); // Continua at� que a tecla '0' seja pressionada

    system("cls"); // Limpa a tela (Windows)
    exit(0); // Sair do programa
    system("exit"); // Sair do programa
}

int main()
{
    locate(); // Configura a localiza��o para o idioma padr�o do sistema
    //PlaySound("som.wav", NULL, SND_FILENAME | SND_ASYNC); // Reproduz o som de fundo
    system("color 0A"); // Muda a cor do texto para verde (Windows)
    menu(); // Chama a fun��o menu

    return 0;
}
