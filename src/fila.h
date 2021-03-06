#ifndef FILA_H 
#define FILA_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Item Item;
typedef struct Block Block;
typedef struct Fila Fila;

struct Item{
	int x;
	int y;
	float distancia;
};

struct Block{
	Item pos;
	Block *prox;
};

struct Fila{
	Block *first;
	Block *last;
};


void FFVazia(Fila *f);

void Enfileira(Fila *f, Item pos);

void Desenfileira(Fila *f, Item *pos);

void FImprime(Fila *f);

void ImprimirMatriz(int tam, int **matriz);

void BFS(int **matriz, int tam);

bool Busca_A(Fila *fila_distancia, int pos_atual_x, int pos_atual_y, int tam, int escolha);

Fila OrdenaFila(Fila *fila_distancia, int tam);

#endif