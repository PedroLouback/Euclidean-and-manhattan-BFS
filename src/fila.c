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

	aux = f->first;
	while (aux->prox != NULL)
	{
		printf("%f \n", aux->pos.distancia);
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
	int i = 0;
	float vetor[tam * tam];
	int k, j;
	float aux1;
	Block *aux;

	for (i = 0; i < (tam * tam); i++)
	{
		vetor[i] = 0;
	}
	i = 0;
	aux = fila_distancia->first->prox;
	while (aux != NULL)
	{
		vetor[i] = aux->pos.distancia;
		i++;
		aux = aux->prox;
	}

	for (k = 0; k < i; k++)
	{
		for (j = k + 1; j < i; j++)
		{
			if (vetor[j] > vetor[k])
			{
				aux1 = vetor[j];
				vetor[j] = vetor[k];
				vetor[k] = aux1;
			}
		}
	}
	FFVazia(fila_distancia);
	j = 0;
	aux = fila_distancia->first;
	while (j < i)
	{
		aux->pos.distancia = vetor[j];
		Enfileira(fila_distancia, aux->pos);
		j++;
		aux = aux->prox;
	}
	return *fila_distancia;
}

bool Busca_A(Fila *fila_distancia, int pos_atual_x, int pos_atual_y, int tam, int escolha)
{
	int pos_final_x = tam - 1;
	int pos_final_y = tam - 1;
	float distancia_euclidiana = 0, distancia_manhattan = 0;
	Item aux;

	if (escolha == 1)
	{
		distancia_euclidiana = sqrt(pow(pos_atual_x - pos_final_x, 2) + pow(pos_atual_y - pos_final_y, 2));

		if (pos_atual_x == 0 && pos_atual_y == 0)
		{
			aux.distancia = distancia_euclidiana;
			Enfileira(fila_distancia, aux);
			return true;
		}
		else
		{
			aux.distancia = distancia_euclidiana;
			Enfileira(fila_distancia, aux);
			OrdenaFila(fila_distancia, tam);
			if (distancia_euclidiana <= fila_distancia->last->pos.distancia)
			{
				return true;
			}
		}
		return false;
	}
	if (escolha == 2){

		distancia_manhattan = (abs(pos_atual_x - pos_final_x) + abs(pos_atual_y - pos_final_y));

		if (pos_atual_x == 0 && pos_atual_y == 0)
		{
			aux.distancia = distancia_manhattan;
			Enfileira(fila_distancia, aux);
			return true;
		}
		else
		{
			aux.distancia = distancia_manhattan;
			Enfileira(fila_distancia, aux);
			OrdenaFila(fila_distancia, tam);
			if (distancia_manhattan <= fila_distancia->last->pos.distancia)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

void BFS(int **matriz, int tam)
{
	Item aux;
	Fila f;
	FFVazia(&f);
	Fila fila_distancia;
	FFVazia(&fila_distancia);
	int i = 0, j = 0, aux_i = 0, aux_j = 0, count, count_caminho = 0, escolha = 0;

	printf("\nEscolha o método em que a matriz vai ser caminhada utilizando BFS: ");
	printf("\n1 - Distância Euclidiana");
	printf("\n2 - Distância de Manhattan");
	printf("\nFaça sua escolha: ");
	scanf("%d", &escolha);

	aux.x = i;
	aux.y = j;
	if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
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
				if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
				else
				{
					matriz[aux.x][aux.y] = 1;
				}
			}
			if (matriz[i][j + 1] == 0)
			{
				aux.x = i;
				aux.y = j + 1;
				if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
				else
				{
					matriz[aux.x][aux.y] = 1;
				}
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
				if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
				else
				{
					matriz[aux.x][aux.y] = 1;
				}
			}
			if (matriz[i][j + 1] == 0)
			{
				aux.x = i;
				aux.y = j + 1;
				if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
				}
				else
				{
					matriz[aux.x][aux.y] = 1;
				}
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
					if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
					{
						Enfileira(&f, aux);
						count_caminho++;
						if (matriz[i][j] != 1)
						{
							Desenfileira(&f, &aux);
						}
					}
					else
					{
						matriz[aux.x][aux.y] = 1;
					}
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
				if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
					if (matriz[i][j] != 1)
					{
						Desenfileira(&f, &aux);
					}
				}
				else
				{
					matriz[aux.x][aux.y] = 1;
				}
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
					if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
					{
						Enfileira(&f, aux);
						count_caminho++;
						if (matriz[i][j] != 1)
						{
							Desenfileira(&f, &aux);
						}
					}
					else
					{
						matriz[aux.x][aux.y] = 1;
					}
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
				if (Busca_A(&fila_distancia, aux.x, aux.y, tam, escolha) == true)
				{
					Enfileira(&f, aux);
					count_caminho++;
					if (matriz[i][j] != 1)
					{
						Desenfileira(&f, &aux);
					}
				}
				else
				{
					matriz[aux.x][aux.y] = 1;
				}
			}

			count_caminho++;
			i = tam;
			j = tam;
		}
	}
	printf("\nPara chegar ao final da matriz usando o metodo BFS, foi realizado um total de %d interacoes!\n", count_caminho);
}
