#include <stdio.h>
#include <stdlib.h>
#include "../headers/labirinto.h"

int carregar_labirinto(Labirinto *labirinto, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 0; 
    }

    fscanf(arquivo, "%d %d %d", &labirinto->linhas, &labirinto->colunas, &labirinto->num_chaves);
    labirinto->matriz = (int **)malloc(labirinto->linhas * sizeof(int *));
    labirinto->posicoes_visitadas = malloc(labirinto->linhas * labirinto->colunas * sizeof(Posicao));
    labirinto->total_movimentos = 0;

    for (int i = 0; i < labirinto->linhas; i++) {
        labirinto->matriz[i] = (int *)malloc(labirinto->colunas * sizeof(int));
        for (int j = 0; j < labirinto->colunas; j++) {
            char celula;
            fscanf(arquivo, " %c", &celula);
            labirinto->matriz[i][j] = celula - '0';
            if (labirinto->matriz[i][j] == 0) {
                labirinto->pos_inicial_linha = i;
                labirinto->pos_inicial_coluna = j;
            }
        }
    }
    fclose(arquivo);
    return 1;  
}

int movimenta_estudante(Labirinto *labirinto, int linha, int coluna, int *movimentos, int *max_recursao, int nivel_atual) {
    if (linha < 0 || coluna < 0 || linha >= labirinto->linhas || coluna >= labirinto->colunas || labirinto->matriz[linha][coluna] == 2 || labirinto->matriz[linha][coluna] == -1) {
        return 0; 
    }

    if (linha == 0) {
        labirinto->pos_final_coluna = coluna;
        labirinto->posicoes_visitadas[labirinto->total_movimentos++] = (Posicao){linha, coluna}; // Registra posição final
        return 1; 
    }

    labirinto->matriz[linha][coluna] = -1;
    labirinto->posicoes_visitadas[labirinto->total_movimentos++] = (Posicao){linha, coluna};

    if (ANALISE && nivel_atual > *max_recursao) *max_recursao = nivel_atual;

    int sucesso = movimenta_estudante(labirinto, linha - 1, coluna, movimentos, max_recursao, nivel_atual + 1) ||
                  movimenta_estudante(labirinto, linha + 1, coluna, movimentos, max_recursao, nivel_atual + 1) ||
                  movimenta_estudante(labirinto, linha, coluna - 1, movimentos, max_recursao, nivel_atual + 1) ||
                  movimenta_estudante(labirinto, linha, coluna + 1, movimentos, max_recursao, nivel_atual + 1);
    
    if (sucesso) {
        (*movimentos)++;
        return 1; 
    }

    labirinto->matriz[linha][coluna] = 1;
    labirinto->total_movimentos--; 
    return 0; }

void exibir_caminho(Labirinto *labirinto) {
    printf("Caminho percorrido:\n");
    for (int i = 0; i < labirinto->total_movimentos; i++) {
        printf("Linha: %d Coluna: %d\n", labirinto->posicoes_visitadas[i].linha, labirinto->posicoes_visitadas[i].coluna);
    }
    //printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha.\n", labirinto->total_movimentos, labirinto->pos_final_coluna);
}

void liberar_labirinto(Labirinto *labirinto) {
    for (int i = 0; i < labirinto->linhas; i++) {
        free(labirinto->matriz[i]);
    }
    free(labirinto->matriz);
    free(labirinto->posicoes_visitadas);
}
