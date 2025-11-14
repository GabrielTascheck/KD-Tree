#include <stdlib.h>
#include "kdTree.h"

#ifndef FPRIO_H
#define FPRIO_H

struct filaNodo
{
    struct nodo *nodo;
    float dist;
    struct filaNodo *prox;
    struct filaNodo *ant;
};

struct filaPrio
{
    struct filaNodo *prim;
    struct filaNodo *fim;
    size_t qtd;
};

struct filaPrio *fprio_criar();

int fprio_insere(struct filaPrio *fila, struct nodo *nodo, float dist);

void fprio_removeUltimo(struct filaPrio *fila);

struct filaPrio *fprio_destroi(struct filaPrio *f);

#endif