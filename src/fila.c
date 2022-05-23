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

Fila OrdenaFila(Fila *fila_distancia, int tam)
{
	int i=0;
	float vetor[tam*tam];
	int k, j, aux1;
	Block *aux;
	Block *aux2;
	aux = fila_distancia->first;
	while (aux != NULL)
	{
		aux2->pos.distancia = aux->pos.distancia;
		vetor[i] = aux2->pos.distancia;
		Desenfileira(fila_distancia, &aux2);
		i++;
		aux = aux->prox;
	}

	for (k = 1; k < i; k++)
	{
		for (j = 0; j < i - 1; j++)
		{
			if (vetor[j] > vetor[j + 1])
			{
				aux1 = vetor[j];
				vetor[j] = vetor[j + 1];
				vetor[j + 1] = aux1;
			}
		}
	}
	FFVazia(fila_distancia);
	for (j = 0; j < i; j++){
		aux->pos.distancia = vetor[j];
		Enfileira(fila_distancia, aux->pos);
	}
	return *fila_distancia;
}

bool Busca_A(int pos_atual_x, int pos_atual_y, int tam)
{
	int pos_final_x = tam - 1;
	int pos_final_y = tam - 1;
	float distancia_euclidiana = 0, menor_euclidiana = 0;
	Item aux;
	Fila fila_distancia;

	distancia_euclidiana = sqrt(pow(pos_atual_x - pos_final_x, 2) + pow(pos_atual_y - pos_final_y, 2));

	if (pos_atual_x == 0 && pos_atual_y == 0)
	{
		FFVazia(&fila_distancia);
		aux.distancia = distancia_euclidiana;
		Enfileira(&fila_distancia, aux);
		FImprime(&fila_distancia);
		return true;
	}
	else
	{
		aux.distancia = distancia_euclidiana;
		Enfileira(&fila_distancia, aux);
		OrdenaFila(&fila_distancia, tam);
		if (distancia_euclidiana <= menor_euclidiana)
		{
			printf("\nA menor distância na posição %d %d é: %f\n", pos_atual_x, pos_atual_y, menor_euclidiana);
			return true;
		}
	}
	return false;
}

void BFS(int **matriz, int tam)
{
	Item aux;
	Fila f;
	FFVazia(&f);
	int i = 0, j = 0, aux_i = 0, aux_j = 0, count, count_caminho = 0;
	aux.x = i;
	aux.y = j;
	if (Busca_A(aux.x, aux.y, tam) == true)
	{
		Enfileira(&f, aux);
	}
	printf("Iniciando o percurso ate o destino em NxN - BFS... ");
	while (i < tam && j < tam)
	{
		if (j == 0 && i == 0)
		{
			if (matriz[i + 1][j] == 0)
			{
				aux.x = i + 1;
				aux.y = j;
				if (Busca_A(aux.x, aux.y, tam) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
			}
			if (matriz[i][j + 1] == 0)
			{
				aux.x = i;
				aux.y = j + 1;
				if (Busca_A(aux.x, aux.y, tam) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
			}
			if (matriz[i][j] != 1)
			{
				aux.x = i;
				aux.y = j;
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
				if (Busca_A(aux.x, aux.y, tam) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
			}
			if (matriz[i][j + 1] == 0)
			{
				aux.x = i;
				aux.y = j + 1;
				if (Busca_A(aux.x, aux.y, tam) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
			}
			if (matriz[i][j] != 1)
			{
				aux.x = i;
				aux.y = j;
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
					if (Busca_A(aux.x, aux.y, tam) == true)
					{
						Enfileira(&f, aux);
						count_caminho++;
					}
				}
				if (matriz[i][j] != 1)
				{
					aux.x = i;
					aux.y = j;
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
				if (Busca_A(aux.x, aux.y, tam) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
			}
			if (matriz[i][j] != 1)
			{
				aux.x = i;
				aux.y = j;
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
					if (Busca_A(aux.x, aux.y, tam) == true)
					{
						Enfileira(&f, aux);
						count_caminho++;
					}
				}
				if (matriz[i][j] != 1)
				{
					aux.x = i;
					aux.y = j;
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
				if (Busca_A(aux.x, aux.y, tam) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
			}
			if (matriz[i][j] != 1)
			{
				aux.x = i;
				aux.y = j;
				Desenfileira(&f, &aux);
			}
			count_caminho++;
			i = tam;
			j = tam;
		}
	}
	printf("\nPara chegar ao final da matriz usando o metodo BFS, foi realizado um total de %d interacoes!\n", count_caminho);
}
