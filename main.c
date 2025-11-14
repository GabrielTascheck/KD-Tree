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
      if (nodo)
        printf("\nEncontrado. Classe %d", nodo->classe);
      else
        printf("\nNão Encontrado.");
      break;
    }
    case 'l':
      imprimirLarguraKD(*raiz);
      break;
    case 'z':
      size_t z = 9;
      float ponto[2] = {100, 100};
      struct nodo **melhores = zVizinhosKD(*raiz, ponto, z);
      for (size_t i = 0; i < z; i++)
        printf("\n%zu MELHOR: [%.2f, %.2f] (%c)", i, melhores[i]->coord[0], melhores[i]->coord[1], 'A' - 1 + melhores[i]->classe);

      break;
    default:
      printf("Opcao Invalida\n");
      break;
    }
    scanf(" %c", &op);
  }

  printf("\n");
  return 0;
}