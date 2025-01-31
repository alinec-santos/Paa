#include <stdio.h>
#include "../headers/tempo.h"

// Implementação da função para Linux/macOS (POSIX)
#ifndef _WIN32
void medir_tempo_posix(void (*funcao_busca)(const char *, const char *), const char *input_file, const char *pattern) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // Tempo inicial
    funcao_busca(input_file, pattern);
    clock_gettime(CLOCK_MONOTONIC, &end);   // Tempo final
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Tempo de execução: %.9f segundos\n", elapsed_time);
}
#endif

// Implementação da função para Windows
#ifdef _WIN32
void medir_tempo_posix(void (*funcao_busca)(const char *, const char *), const char *input_file, const char *pattern) {
    printf("medir_tempo_posix não é suportado no Windows.\n");
}

void medir_tempo_windows(void (*funcao_busca)(const char *, const char *), const char *input_file, const char *pattern) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start); // Tempo inicial
    funcao_busca(input_file, pattern);
    QueryPerformanceCounter(&end);   // Tempo final
    double elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Tempo de execução: %.9f segundos\n", elapsed_time);
}
#endif
