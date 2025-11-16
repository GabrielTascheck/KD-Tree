#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <math.h>
#include "kdTree.h"
#include "fprio.h"

void matarProgramaFaltaMemoria()
{
    fprintf(stderr, "\nFalha ao alocar memoria.");
    exit(1);
}

void imprimirNodo(struct tree tree, struct nodo nodo)
{
    if (tree.k == 0 || nodo.coord == NULL)
        return;
    size_t i;
    for (i = 0; i < tree.k - 1; i++)
    {
        printf("%.2f, ", nodo.coord[i]);
    }
    printf("%.2f", nodo.coord[i]);
    printf(" (classe %d)", nodo.classe);
}

struct nodo *criarNodoKD(size_t k)
{
    struct nodo *novo = malloc(sizeof(struct nodo));
    if (!novo)
        matarProgramaFaltaMemoria();
    novo->coord = malloc(sizeof(float) * k);
    if (!novo->coord)
        matarProgramaFaltaMemoria();
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

    printf("Insira N e K.\n");
    scanf("%zu %zu", &n, &k);

    if (n < 1 || k < 1)
        return NULL;

    struct nodo *primNodo = criarNodoKD(k);
    if (!primNodo)
        return NULL;

    printf("Insira os pontos.\n");
    for (size_t i = 0; i < k; i++)
    {
        // fprintf(stderr, "\nCoord %zu: ", i);
        scanf(" %f", &primNodo->coord[i]);
    }
    // fprintf(stderr, "\nClasse: ");

    scanf(" %d", &primNodo->classe);

    struct tree *tree = malloc(sizeof(struct tree));
    if (!tree)
        matarProgramaFaltaMemoria();
    tree->raiz = primNodo;
    tree->k = k;

    for (size_t i = 1; i < n; i++)
    {
        // fprintf(stderr, "\nNodo %zu", i);
        struct nodo *novo = criarNodoKD(tree->k);
        if (!novo)
        {
            return NULL;
            // fprintf(stderr, "Erro criar novo na criar KD\n");
        }

        for (size_t j = 0; j < k; j++)
        {
            // fprintf(stderr, "\nCoord %zu: ", j);
            scanf(" %f", &novo->coord[j]);
        }
        // fprintf(stderr, "\nClasse: ");
        scanf(" %d", &novo->classe);

        // fprintf(stderr, "Criado o nodo de classe %d\n", novo->classe);
        inserirKD(tree, novo);
    }

    printf("Arvore construida.\n");
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
struct nodo *buscarKD(struct tree tree, struct nodo *raiz, float *coord, size_t indexCoord)
{
    if (tree.k == 0 || raiz == NULL)
        return NULL;

    size_t i = 0;
    for (i = 0; i < tree.k; i++)
        if (raiz->coord[i] != coord[i])
            break;

    if (i == tree.k)
        return raiz;

    if (raiz->coord[indexCoord] > coord[indexCoord])
        return buscarKD(tree, raiz->fe, coord, (indexCoord + 1) % tree.k);

    return buscarKD(tree, raiz->fd, coord, (indexCoord + 1) % tree.k);
}

float distEuclidiana(float *coord1, float *coord2, size_t k)
{
    float dist = 0;
    for (size_t i = 0; i < k; i++)
        dist = dist + (coord1[i] - coord2[i]) * (coord1[i] - coord2[i]);
    dist = sqrt(dist);
    return dist;
}

void zVizinhosKDWrapped(struct tree tree, struct nodo *raiz, size_t coord, float *ponto, size_t z, struct filaPrio *fila)
{
    if (!raiz || tree.k == 0)
        return;

    float dist = distEuclidiana(raiz->coord, ponto, tree.k);
    if (raiz->fe == NULL && raiz->fd == NULL) // raiz é folha
    {
        if (fila->qtd < z || dist < fila->fim->dist)
        {
            fprio_insere(fila, raiz, dist);
            if (fila->qtd > z)
                fprio_removeUltimo(fila);
        }
        return;
    }
    struct nodo *prim, *sec;
    if (ponto[coord] < raiz->coord[coord])
    {
        prim = raiz->fe;
        sec = raiz->fd;
    }
    else
    {
        prim = raiz->fd;
        sec = raiz->fe;
    }

    zVizinhosKDWrapped(tree, prim, (coord + 1) % tree.k, ponto, z, fila);

    if (fila->qtd < z || dist < fila->fim->dist)
    {
        fprio_insere(fila, raiz, dist);
        if (fila->qtd > z)
            fprio_removeUltimo(fila);
    }

    if (fila->qtd < z || fabs(raiz->coord[coord] - ponto[coord]) < fila->fim->dist)
        zVizinhosKDWrapped(tree, sec, (coord + 1) % tree.k, ponto, z, fila);
}

struct nodoDist **zVizinhosKD(struct tree tree, float *ponto, size_t z)
{
    if (z == 0)
        return NULL;
    struct filaPrio *fila = fprio_criar();
    if (!fila)
        return NULL;

    zVizinhosKDWrapped(tree, tree.raiz, 0, ponto, z, fila);

    struct nodoDist **melhores = malloc(sizeof(struct nodoDist *) * z);
    if (!melhores)
    {
        matarProgramaFaltaMemoria();
    }

    for (size_t i = 0; i < z; i++)
    {

        melhores[i] = malloc(sizeof(struct nodoDist));
        if (!melhores[i])
            matarProgramaFaltaMemoria();

        if (fila->qtd > 0)
        {
            melhores[i]->dist = fila->prim->dist;
            melhores[i]->nodo = fprio_removePrimeiro(fila);
        }

        else
            melhores[i] = NULL; // Preenche o resto com NULL
    }

    fprio_destroi(fila);
    return melhores;
}

struct nodo_fila
{
    struct nodo *nodo;
    size_t nivel;
    TAILQ_ENTRY(nodo_fila)
    entries;
};

TAILQ_HEAD(fila_head, nodo_fila);

void imprimirLarguraKD(struct tree tree)
{
    if (tree.raiz == NULL)
        return;

    struct fila_head fila;
    TAILQ_INIT(&fila);

    // Enfileira raiz (nível 0)
    struct nodo_fila *novo = malloc(sizeof(*novo));
    if (!novo)
        matarProgramaFaltaMemoria();

    novo->nodo = tree.raiz;
    novo->nivel = 0;
    TAILQ_INSERT_TAIL(&fila, novo, entries);

    size_t nivelAtual = 0;
    printf("[%zu] ", nivelAtual);

    while (!TAILQ_EMPTY(&fila))
    {
        struct nodo_fila *atual = TAILQ_FIRST(&fila);
        TAILQ_REMOVE(&fila, atual, entries);
        struct nodo *nodoAtual = atual->nodo;

        // nova linha se mudou de nível
        if (atual->nivel != nivelAtual)
        {
            nivelAtual = atual->nivel;
            printf("\n[%zu] ", nivelAtual);
        }

        // imprime coords, chave, e classe do pai
        if (nodoAtual->pai == NULL)
        {
            imprimirNodo(tree, *nodoAtual);
            printf(" [RAIZ]");
        }
        else
        {
            char lado;
            if (nodoAtual == nodoAtual->pai->fe)
                lado = 'e';
            else
                lado = 'd';
            imprimirNodo(tree, *nodoAtual);
            printf(" [%d%c]\t", nodoAtual->pai->classe, lado);
        }

        // filhos
        if (nodoAtual->fe != NULL)
        {
            struct nodo_fila *esq = malloc(sizeof(*esq));
            if (!esq)
                matarProgramaFaltaMemoria();
            esq->nodo = nodoAtual->fe;
            esq->nivel = atual->nivel + 1;
            TAILQ_INSERT_TAIL(&fila, esq, entries);
        }
        if (nodoAtual->fd != NULL)
        {
            struct nodo_fila *dir = malloc(sizeof(*dir));
            if (!dir)
                matarProgramaFaltaMemoria();
            dir->nodo = nodoAtual->fd;
            dir->nivel = atual->nivel + 1;
            TAILQ_INSERT_TAIL(&fila, dir, entries);
        }

        free(atual);
    }
    printf("\n");
}

void posOrdemFree(struct nodo *raiz)
{
    if (raiz == NULL)
        return;
    posOrdemFree(raiz->fe);
    posOrdemFree(raiz->fd);
    if (raiz->coord)
        free(raiz->coord);
    free(raiz);
}
