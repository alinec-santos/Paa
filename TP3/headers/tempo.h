#ifndef TEMPO_H
#define TEMPO_H

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

// Declaração de funções de medição de tempo
void medir_tempo_posix(void (*funcao_busca)(const char *, const char *), const char *input_file, const char *pattern);
void medir_tempo_windows(void (*funcao_busca)(const char *, const char *), const char *input_file, const char *pattern);

#endif // TEMPO_H
