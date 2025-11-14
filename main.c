#include <stdio.h>
#include <stdlib.h>
#include "kdTree.h"

int main()
{
  struct tree *raiz = criarKD();
  if (!raiz)
    return 1;
  char op;
  scanf(" %c", &op);

  while (op != 'f')
  {
    switch (op)
    {
    case 'b':
    {
      float coords[raiz->k];
      for (size_t i = 0; i < raiz->k; i++)
      {
        scanf(" %f", &coords[i]);
      }
      struct nodo *nodo = buscarKD(*raiz, raiz->raiz, coords, 0);
      if(nodo)
        printf("\nEncontrado. Classe %d",nodo->classe);
      else
        printf("\nNão Encontrado.");
      break;
    }
    case 'l':
      imprimirLarguraKD(*raiz);
      break;
    case 'z':
      printf("\nOP Z\n");
      float ponto[2] = {75,25};
      struct nodo **melhores = zVizinhosKD(*raiz, ponto, 1);
      printf("\nMELHOR: [%.2f, %.2f] (%d)",melhores[0]->coord[0], melhores[0]->coord[1], melhores[0]->classe);

      break;
    default:
      printf("Opcaoo Invalida\n");
      break;
    }
    scanf(" %c", &op);
  }

  return 0;
}