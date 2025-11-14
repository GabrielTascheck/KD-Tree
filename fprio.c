#include <stdlib.h>
#include <memory.h>
#include "fprio.h"

struct filaPrio *fprio_criar()
{
    struct filaPrio *fila = malloc(sizeof(struct filaPrio));

    if (!fila)
        return NULL;

    memset(fila, 0, sizeof(struct filaPrio));

    return fila;
}

int fprio_insere(struct filaPrio *fila, struct nodo *nodo, float dist)
{
    if (!fila || !nodo)
        return -1;

    struct filaNodo *novo = malloc(sizeof(struct filaNodo));
    if (!novo)
        return -1;

    novo->nodo = nodo;
    novo->dist = dist;
    novo->prox = NULL;
    novo->ant = NULL;

    if (fila->qtd == 0)
    {
        fila->prim = novo;
        fila->fim = novo;
    }
    else
    {
        if (dist < fila->prim->dist)
        {
            novo->prox = fila->prim;
            fila->prim->ant = novo;
            fila->prim = novo;
        }
        else if (dist >= fila->fim->dist)
        {
            fila->fim->prox = novo;
            novo->ant = fila->fim;
            fila->fim = novo;
        }
        else
        {
            struct filaNodo *aux;
            aux = fila->prim;
            while (dist >= aux->dist && aux->prox)
            {
                aux = aux->prox;
            }
            aux->ant->prox = novo;
            novo->ant = aux->ant;
            novo->prox = aux;
            aux->ant = novo;
        }
    }

    fila->qtd++;
    return fila->qtd;
}

struct nodo *fprio_removeUltimo(struct filaPrio *fila)
{
    if (!fila || fila->qtd == 0)
        return NULL;

    struct filaNodo *itemFila = fila->fim;
    struct nodo *nodo = itemFila->nodo;

    if (fila->qtd == 1)
    {
        fila->fim = NULL;
        fila->prim = NULL;
    }
    else
    {
        fila->fim = itemFila->ant;
        itemFila->ant->prox = NULL;
    }

    free(itemFila);
    fila->qtd--;

    return nodo;
}

struct filaPrio *fprio_destroi(struct filaPrio *fila)
{
    if (!fila)
        return NULL;

    struct filaNodo *aux;

    while (fila->prim != NULL)
    {
        aux = fila->prim->prox;
        free(fila->prim);
        fila->prim = aux;
    }

    free(fila);
    return NULL;
}
