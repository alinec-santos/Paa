#ifndef CASAMENTO_H
#define CASAMENTO_H

void shift_and(const char *text, const char *pattern);
void kmp(const char *text, const char *pattern);
void compute_lps(const char *pattern, int m, int *lps);
void busca(const char *filename, const char *pattern, void (*search_func)(const char *, const char *));

#endif 
