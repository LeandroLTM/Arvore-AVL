#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no {
    struct no *esquerda;
    struct no *direita;
    struct no *pai;
    int chave;
    int fator;
} No;

typedef struct arvore {
    No *raiz;
}Arvore;

Arvore *criar_arvore();

No *criar_no(int chave);

void inserir(Arvore *a, No *r,No *n,int *cresceu);

void pre_order_walk(No *n);

void pre_order_walkEscrever(No *n,FILE *f);

void rotate_ll(Arvore *a,No *n);

void rotate_rr(Arvore *a,No *n);

void removeNo(Arvore *a,No *n, int chave);



#endif // AVL_H_INCLUDED
