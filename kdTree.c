#include <stdio.h>
#include <stdlib.h>
#include "kdTree.h"

void matarProgramaFaltaMemoria()
{
    fprintf(stderr, "\nFalha ao alocar memoria.");
    exit(1);
}

struct nodo *criarNodoKD(size_t k)
{
    struct nodo *novo = malloc(sizeof(struct nodo));
    if (!novo)
        return NULL;
    novo->coord = malloc(sizeof(float) * k);
    if (!novo->coord)
        return NULL;
    novo->classe = 0;
    novo->fd = NULL;
    novo->fe = NULL;
    novo->pai = NULL;

    return novo;
}

struct tree *criarKD()
{
    size_t n = 0;
    size_t k = 0;

    printf("\nN: ");
    scanf("%zu", &n);
    printf("\nK: ");
    scanf("%zu", &k);

    if (n < 1 || k < 1)
        return NULL;

    struct nodo *primNodo = criarNodoKD(k);
    if (!primNodo)
        return NULL;

    for (size_t i = 0; i < k; i++)
    {
        fprintf(stderr, "\nCoord %zu: ", i);
        scanf(" %f", &primNodo->coord[i]);
    }
    fprintf(stderr, "\nClasse: ");

    scanf(" %d", &primNodo->classe);

    struct tree *tree = malloc(sizeof(struct tree));
    tree->raiz = primNodo;
    tree->k = k;

    for (size_t i = 1; i < n; i++)
    {
        fprintf(stderr, "\nNodo %zu", i);
        struct nodo *novo = criarNodoKD(tree->k);
        if (!novo)
        {
            return NULL;
            fprintf(stderr, "Erro criar novo na criar KD\n");
        }

        for (size_t j = 0; j < k; j++)
        {
            fprintf(stderr, "\nCoord %zu: ", j);
            scanf(" %f", &novo->coord[j]);
        }
        fprintf(stderr, "\nClasse: ");
        scanf(" %d", &novo->classe);

        fprintf(stderr, "Criado o nodo de classe %d\n", novo->classe);
        inserirKD(tree, novo);
    }

    return tree;
}

void inserirKD(struct tree *tree, struct nodo *novo)
{
    struct nodo *atual = tree->raiz;
    struct nodo *pai = NULL;
    size_t indexCoord = 0;
    size_t chave = indexCoord;

    while (atual)
    {
        pai = atual;
        if (novo->coord[indexCoord] < atual->coord[indexCoord])
            atual = atual->fe;
        else
            atual = atual->fd;
        chave = indexCoord;
        indexCoord = (indexCoord + 1) % tree->k;
    }
    novo->pai = pai;
    if (!pai)
        tree->raiz = novo;
    else
    {
        if (novo->coord[chave] < pai->coord[chave])
            pai->fe = novo;
        else
            pai->fd = novo;
    }
}
struct nodo *bucarKD(struct tree raiz, float *coord)
{
}

struct nodo **zVizinhosKD(struct tree raiz, float *coord, size_t z)
{
}

void imprimirLarguraKD(struct tree raiz)
{
}

void posOrdemFree(struct tree raiz)
{
}