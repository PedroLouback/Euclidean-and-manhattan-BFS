#include "fila.h"

void FFVazia(Fila *f)
{
	f->first = (Block *)malloc(sizeof(Block));
	f->last = f->first;
	f->first->prox = NULL;
}

void Enfileira(Fila *f, Item pos)
{
	f->last->prox = (Block *)malloc(sizeof(Block));
	f->last = f->last->prox;
	f->last->pos = pos;
	f->last->prox = NULL;
}

void Desenfileira(Fila *f, Item *pos)
{
	Block *aux;

	if (f->first == f->last || f == NULL || f->first->prox == NULL)
	{
		printf("FILA VAZIA!\n");
		return;
	}

	aux = f->first->prox;
	f->first->prox = aux->prox;
	pos->x = aux->pos.x;
	pos->y = aux->pos.y;
	free(aux);
}

void FImprime(Fila *f)
{
	Block *aux;

	aux = f->first->prox;
	while (aux != NULL)
	{
		printf("%d %d\n", aux->pos.x, aux->pos.y);
		aux = aux->prox;
	}
}

void ImprimirMatriz(int tam, int **matriz)
{
	
	for (int i = 0; i < tam; i++)
	{
		printf("\n");
		for (int j = 0; j < tam; j++)
		{
			printf("%d\t", matriz[i][j]);
		}
	}
	printf("\n\n");
}

void BFS(int **matriz, int tam)
{
	Item aux;
	Fila f;
	FFVazia(&f);
	int i = 0, j = 0, aux_i = 0, aux_j = 0, count, count_caminho = 0;
	aux.x = i;
	aux.y = j;
	Enfileira(&f, aux);
	printf("Iniciando o percurso ate o destino em NxN - BFS... ");
	while (i < tam && j < tam)
	{

		if (j == 0 && i == 0)
		{
			if (matriz[i + 1][j] == 0)
			{
				aux.x = i + 1;
				aux.y = j;
				Enfileira(&f, aux);
				matriz[aux.x][aux.y] = 1;
				count_caminho++;
			}
			if (matriz[i][j + 1] == 0)
			{
				aux.x = i;
				aux.y = j + 1;
				Enfileira(&f, aux);
				matriz[aux.x][aux.y] = 1;
				count_caminho++;
			}
			if (matriz[i][j] != 1)
			{
				Desenfileira(&f, &aux);
			}

			i++;
		}
		if (i < tam - 1 && j == 0)
		{
			if (matriz[i + 1][j] == 0)
			{
				aux.x = i + 1;
				aux.y = j;
				Enfileira(&f, aux);
				matriz[aux.x][aux.y] = 1;
				count_caminho++;
			}
			if (matriz[i][j + 1] == 0)
			{
				aux.x = i;
				aux.y = j + 1;
				Enfileira(&f, aux);
				matriz[aux.x][aux.y] = 1;
				count_caminho++;
			}
			if (matriz[i][j] != 1)
			{
				Desenfileira(&f, &aux);
			}
			count = 0;
			while (aux_j != i)
			{
				if (count == 0)
				{
					aux_i = i;
					aux_j = j;
				}
				aux_i--;
				aux_j++;
				if (matriz[aux_i][aux_j + 1] == 0)
				{
					aux.x = aux_i;
					aux.y = aux_j + 1;
					Enfileira(&f, aux);
					matriz[aux.x][aux.y] = 1;
					count_caminho++;
				}
				if (matriz[i][j] != 1)
				{
					Desenfileira(&f, &aux);
				}
				count++;
			}
			i++;
		}
		if (i == tam - 1 && j != tam - 1)
		{
			aux_i = 0;
			aux_j = 0;
			if (matriz[i][j + 1] == 0)
			{
				aux.x = i;
				aux.y = j + 1;
				Enfileira(&f, aux);
				matriz[aux.x][aux.y] = 1;
				count_caminho++;
			}
			if (matriz[i][j] != 1)
			{
				Desenfileira(&f, &aux);
			}
			count = 0;
			while (aux_j != i - 1)
			{
				if (count == 0)
				{
					aux_i = i;
					aux_j = j;
				}
				aux_i--;
				aux_j++;
				if (matriz[aux_i][aux_j + 1] == 0)
				{
					aux.x = aux_i;
					aux.y = aux_j + 1;
					Enfileira(&f, aux);
					matriz[aux.x][aux.y] = 1;
					count_caminho++;
				}
				if (matriz[i][j] != 1)
				{
					Desenfileira(&f, &aux);
				}
				count++;
			}
			j++;
		}
		if (i == tam - 1 && j == tam - 2)
		{
			if (matriz[i][j + 1] == 2)
			{
				aux.x = i;
				aux.y = j + 1;
				Enfileira(&f, aux);
				matriz[aux.x][aux.y] = 1;
				count_caminho++;
			}
			if (matriz[i][j] != 1)
			{
				Desenfileira(&f, &aux);
			}
			count_caminho++;
			i = tam;
			j = tam;
		}
	}
	printf("\nPara chegar ao final da matriz usando o metodo BFS, foi realizado um total de %d interacoes!\n", count_caminho);
}
