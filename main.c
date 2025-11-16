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
        printf("Encontrado. Classe %d\n", nodo->classe);
      else
        printf("Não Encontrado.\n");
      break;
    }
    case 'l':
      imprimirLarguraKD(*raiz);
      break;
    case 'z':
    {
      size_t z = 0;
      scanf(" %zu", &z);
      float ponto[raiz->k];

      for (size_t i = 0; i < raiz->k; i++)
        scanf(" %f", &ponto[i]);

      struct nodoDist **melhores = zVizinhosKD(*raiz, ponto, z);

      printf("Vizinhos mais proximos:\n");
      if (melhores == NULL)
        break;
      ;

      for (size_t i = 0; i < z; i++)
      {
        if (melhores[i])
        {
          imprimirNodo(*raiz, *melhores[i]->nodo);
          printf(", dist = %f", melhores[i]->dist);
          printf("\n");
        }
        else
        {
          printf("\nZ maior que quantidade de nodos na árvore");
        }
        free(melhores[i]);
      }
      free(melhores);
      printf("\n");

      break;
    }
    default:
      printf("Opcao Invalida\n");
      break;
    }
    scanf(" %c", &op);
  }

  posOrdemFree(raiz->raiz);
  free(raiz);
  return 0;
}