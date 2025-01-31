#ifndef GERADOR_LABIRINTO_H
#define GERADOR_LABIRINTO_H

#include "labirinto.h"

void gerar_labirinto_aleatorio(Labirinto *labirinto, int tamanho, int chaves);
void salvar_labirinto_em_arquivo(Labirinto *labirinto, const char *nome_arquivo);

#endif 
