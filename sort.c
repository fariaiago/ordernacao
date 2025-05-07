#include "sort.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Dados bubble_sort(int *vetor, size_t vetor_len)
{
	size_t n = vetor_len, n_comparacoes = 0, n_trocas = 0;
	bool trocado = false;
	do
	{
		trocado = false;
		for (size_t i = 1; i < n; i++)
		{
			if (vetor[i - 1] > vetor[i])
			{
				vetor[i - 1] = vetor[i - 1] ^ vetor[i];
				vetor[i] = vetor[i - 1] ^ vetor[i];
				vetor[i - 1] = vetor[i - 1] ^ vetor[i];
				trocado = true;
				n_trocas++;
			}
			n_comparacoes++;
		}
		n--;
	} while (trocado);
	return (Dados){ .n_comparacoes = n_comparacoes, .n_trocas = n_trocas};
}

Dados selection_sort(int *vetor, size_t vetor_len)
{
	size_t n_comparacoes = 0, n_trocas = 0;
	for (size_t i = 0; i < vetor_len - 1; i++)
	{
		size_t min_pos = i;
		for (size_t j = i + 1; j < vetor_len; j++)
		{
			if (vetor[j] < vetor[min_pos])
			{
				min_pos = j;
			}
			n_comparacoes++;
		}
		if (min_pos != i)
		{
			vetor[min_pos] = vetor[min_pos] ^ vetor[i];
			vetor[i] = vetor[min_pos] ^ vetor[i];
			vetor[min_pos] = vetor[min_pos] ^ vetor[i];
			n_trocas++;
		}
		n_comparacoes++;
	}
	return (Dados){ .n_comparacoes = n_comparacoes, .n_trocas = n_trocas};
}

Dados insertion_sort(int *vetor, size_t vetor_len)
{
	size_t n_comparacoes = 0, n_trocas = 0;
	for (size_t i = 0; i < vetor_len; i++)
	{
		for (size_t j = i; j > 0; j--)
		{
			if (!(vetor[j - 1] > vetor[j]))
			{
				break;
			}
			vetor[j - 1] = vetor[j - 1] ^ vetor[j];
			vetor[j] = vetor[j - 1] ^ vetor[j];
			vetor[j - 1] = vetor[j - 1] ^ vetor[j];
			n_comparacoes++;
			n_trocas++;
		}
	}
}

static void merge_sort_merge(int *aux, size_t inicio, size_t meio, size_t fim, int *vetor, Dados *dados)
{
	size_t ini_pos = inicio, meio_pos = meio;
	for (size_t i = inicio; i < fim; i++)
	{
		if (ini_pos < meio && (meio_pos >= fim || vetor[ini_pos] <= vetor[meio_pos]))
		{
			aux[i] = vetor[ini_pos];
			ini_pos++;
		}
		else
		{
			aux[i] = vetor[meio_pos];
			meio_pos++;
		}
		dados->n_comparacoes++;
		dados->n_trocas++;
	}
}

static void merge_sort_split(int *aux, size_t inicio, size_t fim, int *vetor, Dados *dados)
{
	if (fim - inicio <= 1)
	{
		dados->n_comparacoes++;
		return;
	}
	dados->n_comparacoes++;

	size_t meio = (fim + inicio) / 2;
	merge_sort_split(vetor, inicio, meio, aux, dados);
	merge_sort_split(vetor, meio, fim, aux, dados);

	merge_sort_merge(aux, inicio, meio, fim, vetor, dados);
}

Dados merge_sort(int *vetor, size_t vetor_len)
{
	Dados dados = { .n_comparacoes = 0, .n_trocas = 0};
	int *aux = malloc(vetor_len * sizeof(int));
	memcpy(aux, vetor, vetor_len * sizeof(int));
	merge_sort_split(vetor, 0, vetor_len, aux, &dados);
	free(aux);
	return (Dados) { .n_comparacoes = dados.n_comparacoes, .n_trocas = dados.n_trocas};
}

static void _quicksort(int *vetor, long inicio, long fim, Dados *dados)
{
	long ini_pos = inicio, fim_pos = fim;
	int pivo = vetor[(inicio + fim) / 2];
	while (ini_pos <= fim_pos)
	{
		while (vetor[ini_pos] < pivo)
		{
			ini_pos++;
		}
		while (vetor[fim_pos] > pivo)
		{
			fim_pos--;
		}
		if (ini_pos <= fim_pos)
		{
			int aux = vetor[ini_pos];
			vetor[ini_pos] = vetor[fim_pos];
			vetor[fim_pos] = aux;
			ini_pos++;
			fim_pos--;
			dados->n_trocas++;
		}
		dados->n_comparacoes++;
	}
	if (inicio < fim_pos)
	{
		_quicksort(vetor, inicio, fim_pos, dados);
	}
	if (ini_pos < fim)
	{
		_quicksort(vetor, ini_pos, fim, dados);
	}
	dados->n_comparacoes += 2;
}

Dados quick_sort(int *vetor, size_t vetor_len)
{
	Dados dados = { .n_comparacoes = 0, .n_trocas = 0};
	_quicksort(vetor, 0, vetor_len - 1, &dados);
	return (Dados) { .n_comparacoes = dados.n_comparacoes, .n_trocas = dados.n_trocas};
}

Dados heap_sort(int *vetor, size_t vetor_len)
{
	size_t n_comparacoes = 0, n_trocas = 0;
	size_t n = vetor_len, meio = vetor_len / 2, pai, filho;
	int aux;
	while (true)
	{
		if (meio > 0)
		{
			meio--;
			aux = vetor[meio];
		}
		else
		{
			n--;
			if (n <= 0)
			{
				n_comparacoes++;
				return (Dados) { .n_comparacoes = n_comparacoes, .n_trocas = n_trocas};
			}
			aux = vetor[n];
			vetor[n] = vetor[0];
			n_comparacoes++;
		}
		pai = meio;
		filho = meio * 2 + 1;
		while (filho < n)
		{
			if (filho + 1 < n && vetor[filho + 1] > vetor[filho])
			{
				filho++;
			}
			if (vetor[filho] > aux)
			{
				vetor[pai] = vetor[filho];
				pai = filho;
				filho = pai * 2 + 1;
			}
			else
			{
				break;
			}
			n_comparacoes += 2;
		}
		vetor[pai] = aux;
		n_comparacoes++;
		n_trocas++;
	}
}
