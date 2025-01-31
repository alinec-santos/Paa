#ifndef LABIRINTO_H
#define LABIRINTO_H

#define ANALISE 1  

typedef struct {
    int linha, coluna;
} Posicao;

typedef struct {
    int linhas;
    int colunas;
    int num_chaves;
    int **matriz;
    int pos_inicial_linha;
    int pos_inicial_coluna;
    Posicao *posicoes_visitadas;  
    int total_movimentos;          
    int pos_final_coluna;          
} Labirinto;

int carregar_labirinto(Labirinto *labirinto, const char *nome_arquivo);

void liberar_labirinto(Labirinto *labirinto);

int movimenta_estudante(Labirinto *labirinto, int linha, int coluna, int *movimentos, int *max_recursao, int nivel_atual);

void exibir_caminho(Labirinto *labirinto);

int main();
#endif
