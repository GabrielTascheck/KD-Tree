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

struct tree *criarKD(size_t n, size_t k);

void inserirKD(struct tree *tree, struct nodo *novo);

struct nodo *bucarKD(struct tree tree, float *coord);

struct nodo **zVizinhosKD(struct tree tree, float *coord, size_t z);

void imprimirLarguraKD(struct tree tree);

void posOrdemFree(struct tree tree);


#endif
