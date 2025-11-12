#include <stdio.h>
#include <stdlib.h>
#include "kdTree.h"

int main()
{

  size_t k, n;

  printf("\nN: ");
  scanf("%zu", &n);
  printf("\nK: ");
  scanf("%zu", &k);

  struct nodo *raiz = criarKD(n,k);
  char op;
  scanf(" %c", &op);

  while (op != 'f')
  {
    switch (op)
    {
    case 'b':
      printf("OP B\n");
      break;
    case 'l':
      printf("OP L\n");

      break;
    case 'z':
      printf("OP Z\n");

      break;
    default:
      printf("Opcaoo Invalida\n");
      break;
    }
    scanf(" %c", &op);
  }

  return 0;
}