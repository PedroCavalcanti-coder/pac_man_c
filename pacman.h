// Tipos de células do mapa (enum)
typedef enum {
    VAZIO,
    PAREDE,
    COMIDA,
    POWER_UP,
    INIMIGO
} TipoCelula;

// Direções (enum)
typedef enum {
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA,
    PARADO
} Direcao;

// Estrutura do jogador
typedef struct {
    int x, y;
    int vidas;
    int pontos;
    Direcao dir;
} PacMan;

// Estrutura dos fantasmas
typedef struct {
    int x, y;
    Direcao dir;
    int velocidade;
} Fantasma;

// Estrutura do jogo
typedef struct {
    char **mapa;
    int largura, altura;
    PacMan jogador;
    Fantasma fantasmas[4]; // 4 fantasmas
    int comida_restante;
} Jogo;