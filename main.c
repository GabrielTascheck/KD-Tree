#include <stdio.h>
#include <stdlib.h>
#include "kdTree.h"

int main()
{
  struct tree *raiz = criarKD();
  if(!raiz)
    return 1;
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