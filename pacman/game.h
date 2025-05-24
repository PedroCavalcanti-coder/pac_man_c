#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

extern int MAX_COLUNAS;
extern int MAX_LINHAS;
extern char **mapa;
extern int *score;
extern int *bool_game_over;

void limparTela();
void inicializa_mapa();
void libera_mapa();
void start_game();
void game_loop();
void game_over();
void locate();
void drawing_map();
void write_ranking(int score);
int ranking();

#endif // GAME_H_INCLUDED
