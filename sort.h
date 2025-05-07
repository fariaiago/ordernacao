#ifndef SORT_H
#define SORT_H
#include <stddef.h>

typedef struct
{
    size_t n_comparacoes;
    size_t n_trocas;
}
Dados;

Dados bubble_sort(int *vetor, size_t vetor_len);

Dados selection_sort(int *vetor, size_t vetor_len);

Dados insertion_sort(int *vetor, size_t vetor_len);

Dados merge_sort(int *vetor, size_t vetor_len);

Dados quick_sort(int *vetor, size_t vetor_len);

Dados heap_sort(int *vetor, size_t vetor_len);

#endif