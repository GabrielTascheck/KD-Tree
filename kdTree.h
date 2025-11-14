#include <stdlib.h>

#ifndef KDTREE_H
#define KDTREE_H

struct nodo
{
  float *coord;
  int classe;
  struct nodo *fe;
  struct nodo *fd;
  struct nodo *pai;
};

struct tree
{
  size_t k;
  struct nodo *raiz;
};

struct nodoDist{
  struct nodo *nodo;
  float dist;
};

struct tree *criarKD();

void inserirKD(struct tree *tree, struct nodo *novo);

struct nodo *buscarKD(struct tree tree, struct nodo *raiz, float *coord, size_t indexCoord);

struct nodoDist **zVizinhosKD(struct tree tree, float *ponto, size_t z);

void imprimirLarguraKD(struct tree tree);

void imprimirNodo(struct tree tree, struct nodo nodo);

void posOrdemFree(struct nodo *raiz);


#endif
