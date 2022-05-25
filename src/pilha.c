#include "pilha.h"


void FPVazia(Pilha *p){
	p->top   = 0;
	p->base  = 0;
}


void PUSH(Pilha *p, ItemPilha d){
	if (p->top >= MAXTAM){
		printf("PILHA CHEIA!\n");
	}else{
		p->vet[p->top] = d;
		p->top ++;
	}
}

void POP(Pilha *p, ItemPilha *d){
	if(p->base == p->top)
		printf("PILHA VAZIA!\n");
	else{
		p->top --;
		*d = p->vet[p->top];
	}
}

void PRemove(Pilha *p, ItemPilha d){
	Pilha aux;
	ItemPilha rem;

	FPVazia(&aux);

	if(p->base == p->top)
		printf("PILHA VAZIA!\n");
	else{
		while(p->top > p->base){
			POP(p, &rem);
			if(rem.x != d.x && rem.y != d.y)
				PUSH(&aux, rem);
		}

		while(aux.top > aux.base){
			POP(&aux, &rem);
			PUSH(p, rem);
		}
	}
}

void PImprime(Pilha *p){
	for(int i=p->top-1; i>=p->base; i--)
		printf("%d %d\n", p->vet[i].x, p->vet[i].y);
	printf("\n");
}

void DFS(int **matriz, int tam){
    ItemPilha aux;
    Pilha p;
    FPVazia(&p);
    int i = 0, j = 0;
    int count=0;
    aux.x=i;
    aux.y=j;
	matriz[j][i] = 1;
    PUSH(&p, aux);
	printf("Iniciando o percurso ate o destino em NxN - DFS... \n");
    while(matriz[tam-1][tam-1] != 1){
		if(j == 0){
			if(i < tam -1 && matriz[i + 1][j] == 0){
				i++;
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}
			else if(matriz[i][j + 1] == 0){
				j++; 
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}
			else if(matriz[i - 1][j] == 0){
				i--;
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}else {
				aux.x=i;
				aux.y=j;
				matriz[i][j] = 1;
				POP(&p, &aux);
				i--;
				count++;
			}
		}
		else if(i != tam -1 && j == tam -1){
			if(i < tam - 1 && matriz[i + 1][j] == 0){
				i++;
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}else if(i < tam - 1 && matriz[i][j - 1] == 0){
				j--;
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}else{
				aux.x=i;
				aux.y=j;
				matriz[i][j] = 2;
				POP(&p, &aux);
				count++;
			}
		}

		else{
			if(i < tam - 1 && matriz[i + 1][j] == 0){
				i++;
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}
			else if(matriz[i][j + 1] == 0){
				j++; 
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}
			else if(matriz[i][j - 1] == 0){
				j--;
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}
			else if(matriz[i - 1][j] == 0){
				i--;
				aux.x = i;
				aux.y = j;
				matriz[i][j] = 1;
				printf("%d  %d\n", i, j);
				PUSH(&p, aux);
				count++;
			}else{
				aux.x=i;
				aux.y=j;
				matriz[i][j] = 1;
				POP(&p, &aux);
				i--;
				count++;
			}
		}
    }
    printf("\nPara chegar ao final da matriz usando o metodo DFS, foi realizado um total de %d interacoes!\n", count);
}