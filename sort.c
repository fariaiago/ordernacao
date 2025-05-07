#include "sort.h"
#include <stddef.h>
#include <stdbool.h>

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