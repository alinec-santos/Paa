#include <stdlib.h>
#include <stdio.h>
#include "../headers/gerador_labirinto.h"
#include "../headers/labirinto.h"


void pausar() {
    printf("\nPressione Enter para voltar ao menu...");
    getchar(); getchar();
}

// Função para exibir o menu e permitir ao usuário gerar e salvar o labirinto
void exibirmenu() {
    int opcao,opcaoso;
    Labirinto labirinto;
    int labirinto_carregado = 0;
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║ Para que sua experiência na nossa biblioteca ║\n");
    printf("║ seja ainda mais completa, nos diga:          ║\n");
    printf("║ Qual é o seu sistema operacional?            ║\n");
    printf("║ 1- Linux                                     ║\n");
    printf("║ 2- Windows                                   ║\n");
    printf("║ 3- Outros                                    ║\n");
    printf("╠══════════════════════════════════════════════╣\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoso);

    char *clear_cmd = (opcaoso == 1) ? "clear" : "cls";
    while (1) {
        system(clear_cmd);  
        printf("\n");
        printf("╔════════════════════════════════════════════════════════════════╗\n");
        printf("║                      PROGRAMA LABIRINTO                        ║ \n");
        printf("║═══════════════════════════════════════════════════════════════ ║\n");
        printf("║                       OPÇÕES DO PROGRAMA                       ║\n");
        printf("║════════════════════════════════════════════════════════════════║\n");
        printf("║1) Carregar novo arquivo de dados                               ║\n");
        printf("║2) Exibir resultados                                            ║\n");
        printf("║3) Caminho Percorrido                                           ║\n");
        printf("║4) Gerar labirinto aleatório                                    ║\n");
        printf("║5) Sair do programa                                             ║\n");
        printf("╠════════════════════════════════════════════════════════════════╣\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Por favor digite o nome do arquivo: ");
                char nome_arquivo[100];
                scanf("%s", nome_arquivo);
                if (carregar_labirinto(&labirinto, nome_arquivo)) {
                    labirinto_carregado = 1;
                    printf("Labirinto carregado com sucesso.\n");
                } else {
                    printf("Erro ao carregar o arquivo.\n");
                }
                pausar();
                break;

            case 2:
                if (!labirinto_carregado) {
                    printf("Por favor, carregue antes um arquivo de dados!\n");
                } else {
                    int movimentos = 0, max_recursao = 0;
                    if (!movimenta_estudante(&labirinto, labirinto.pos_inicial_linha, labirinto.pos_inicial_coluna, &movimentos, &max_recursao, 1)) {
                        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n", movimentos);
                    } else {
                        printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha.\n", movimentos, labirinto.pos_final_coluna);
                        if (ANALISE) printf("Nivel maximo de recursão: %d\n", max_recursao);
                    }
                }
                pausar();
                break;

            case 3:
                if (!labirinto_carregado) {
                    printf("Por favor, carregue antes um arquivo de dados!\n");
                } else {
                    exibir_caminho(&labirinto);
                }
                pausar();
                break;

            case 4:
                printf("* Digite o tamanho do labirinto (linhas = colunas): ");
                int tamanho;
                scanf("%d", &tamanho);
                printf("* Digite o número de chaves: ");
                int num_chaves;
                scanf("%d", &num_chaves);

                gerar_labirinto_aleatorio(&labirinto, tamanho, num_chaves);
                labirinto_carregado = 1;
                printf("Labirinto gerado com sucesso.\n");

                printf("* Digite o nome do arquivo para salvar o labirinto: ");
                char nome_arquivo_salvar[100];
                scanf("%s", nome_arquivo_salvar);
                salvar_labirinto_em_arquivo(&labirinto, nome_arquivo_salvar);
                pausar();
                break;

            default:
                if (labirinto_carregado) {
                    liberar_labirinto(&labirinto);
                }
                printf("Programa encerrado.\n");
                return;
        }
    }
}