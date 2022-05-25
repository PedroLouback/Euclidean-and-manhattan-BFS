#include "fila.h"
#include "pilha.h"

int main()
{
    int tam = 0, i = 0, j = 0, escolha = 0;
    int **matriz;

    FILE *arquivo;

    arquivo = fopen("matriz.txt", "r");

    if (arquivo == NULL)
    {
        printf("\nArquivo inválido.\n");
        return 0;
    }

    fscanf(arquivo, "%d", &tam);

    matriz = (int **)malloc(sizeof(int *) * tam);
    for (i = 0; i < tam; i++)
    {
        matriz[i] = (int *)malloc(sizeof(int) * tam);
    }

    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }

    fclose(arquivo);

    printf("\nA matriz gerada foi: \n");
    ImprimirMatriz(tam, matriz);

    while (escolha < 4)
    {
        printf("\nEscola qual método de busca deseja utilizar: ");
        printf("\n1 - BFS");
        printf("\n2 - DFS");
        printf("\nFaça sua escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1)
        {
            BFS(matriz, tam);
        }
        else if (escolha == 2)
        {
            DFS(matriz, tam);
        }
        else
        {
            printf("Opção inválida.");
            escolha = 4;
        }
    }

    BFS(matriz, tam);

    return 0;
}