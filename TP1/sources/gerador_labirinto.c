#include <stdlib.h>
#include <stdio.h>
#include "../headers/gerador_labirinto.h"


void gerar_labirinto_aleatorio(Labirinto *labirinto, int tamanho, int chaves) {
    labirinto->colunas = tamanho;
    labirinto->linhas = tamanho;  // Número de linhas igual ao número de colunas
    labirinto->num_chaves = chaves;

    labirinto->matriz = malloc(labirinto->linhas * sizeof(int *));
    for (int i = 0; i < labirinto->linhas; i++) {
        labirinto->matriz[i] = malloc(labirinto->colunas * sizeof(int));
        for (int j = 0; j < labirinto->colunas; j++) {
           labirinto->matriz[i][j] = rand() % 2 + 1;  
        }
    }

    labirinto->pos_inicial_linha = labirinto->linhas - 1;  
    labirinto->pos_inicial_coluna = rand() % labirinto->colunas; 
    labirinto->matriz[labirinto->pos_inicial_linha][labirinto->pos_inicial_coluna] = 0;

    for (int i = 0; i < (labirinto->linhas * labirinto->colunas) / 4; i++) {  
        int linha = rand() % labirinto->linhas;
        int coluna = rand() % labirinto->colunas;
        labirinto->matriz[linha][coluna] = 2;
    }

    for (int i = 0; i < chaves; i++) {
        int linha = rand() % labirinto->linhas;
        int coluna = rand() % labirinto->colunas;
        while (labirinto->matriz[linha][coluna] != 1) {
            linha = rand() % labirinto->linhas;
            coluna = rand() % labirinto->colunas;
        }
        labirinto->matriz[linha][coluna] = 3;
    }

    
}

void salvar_labirinto_em_arquivo(Labirinto *labirinto, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return;
    }

    // Escreve as dimensões do labirinto e o número de chaves no arquivo
    fprintf(arquivo, "%d %d %d\n", labirinto->linhas, labirinto->colunas, labirinto->num_chaves);

    // Escreve o labirinto no arquivo
    for (int i = 0; i < labirinto->linhas; i++) {
        for (int j = 0; j < labirinto->colunas; j++) {
            fprintf(arquivo, "%d", labirinto->matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Labirinto salvo com sucesso no arquivo %s.\n", nome_arquivo);
}