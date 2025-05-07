#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define TAMANHO 4

typedef Dados (*SortFn)(int *, size_t);

void sort_todas_ordens(SortFn sort, char *sort_nome,
	int **entradas_ordenada, int **entradas_inversa, int **entradas_aleatoria);
void ordernar(SortFn sort, int **entradas, char *ordem_nome);

size_t vetores_tamanho[TAMANHO] = {1000, 10000, 50000, 100000};

int main(void)
{
	// Seed do rand()
	srand(time(NULL));

	// Vetores de vetores de entrada
	int *entradas_ordenada[TAMANHO];
	int *entradas_inversa[TAMANHO];
	int *entradas_aleatoria[TAMANHO];
	
	for (size_t i = 0; i < TAMANHO; i++)
	{
		entradas_ordenada[i] = malloc(vetores_tamanho[i] * sizeof(int));
		entradas_inversa[i] = malloc(vetores_tamanho[i] * sizeof(int));
		entradas_aleatoria[i] = malloc(vetores_tamanho[i] * sizeof(int));
		
		size_t vetor_len = vetores_tamanho[i];
		for (size_t j = 0; j < vetor_len; j++)
		{
			entradas_ordenada[i][j] = j + 1; // Gerar entradas ordenadas
			entradas_inversa[i][j] = vetor_len - j; // Gerar entradas inversamente ordenadas
			entradas_aleatoria[i][j] = rand(); // Gerar entradas aleatórias
		}
	}

	// Ordenar
	sort_todas_ordens(&bubble_sort, "Bubble sort", entradas_ordenada, entradas_inversa, entradas_aleatoria);
	sort_todas_ordens(&selection_sort, "Selection sort", entradas_ordenada, entradas_inversa, entradas_aleatoria);
	sort_todas_ordens(&insertion_sort, "Insertion sort", entradas_ordenada, entradas_inversa, entradas_aleatoria);
	sort_todas_ordens(&merge_sort, "Merge sort", entradas_ordenada, entradas_inversa, entradas_aleatoria);
	sort_todas_ordens(&quick_sort, "Quick sort", entradas_ordenada, entradas_inversa, entradas_aleatoria);
	sort_todas_ordens(&heap_sort, "Heap sort", entradas_ordenada, entradas_inversa, entradas_aleatoria);
}

void sort_todas_ordens(SortFn sort, char *sort_nome,
	int **entradas_ordenada, int **entradas_inversa, int **entradas_aleatoria)
{
	printf("%s:\n", sort_nome);
	ordernar(sort, entradas_ordenada, "Ordenada");
	ordernar(sort, entradas_inversa, "Inversamente ordenada");
	ordernar(sort, entradas_aleatoria, "Aleatória");
}

void ordernar(SortFn sort, int **entradas, char *ordem_nome)
{
	printf("\t%s\n", ordem_nome);
	for (size_t i = 0; i < TAMANHO; i++)
	{
		int *vetor_copia = malloc(vetores_tamanho[i] * sizeof(int));
		memcpy(vetor_copia, entradas[i], vetores_tamanho[i] * sizeof(int));

		clock_t inicio = clock();
		Dados dados = sort(vetor_copia, vetores_tamanho[i]);
		printf("\t\tTamanho: %ld\n\t\t\tTempo gasto: %ld\n\t\t\tN° de comparações: %ld\n\t\t\tN° de trocas: %ld\n",
			vetores_tamanho[i], clock() - inicio, dados.n_comparacoes, dados.n_trocas);

		free(vetor_copia);
	}
}