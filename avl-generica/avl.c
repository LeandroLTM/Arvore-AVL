#include "avl.h"

Arvore *criar_arvore() {
    Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));

    arvore->raiz = NULL;

    return arvore;
}

No *criar_no(int chave) {
    No *n = (No *)malloc(sizeof(No));

    n->chave = chave;
    n->fator = 0;
    n->pai = NULL;
    n->esquerda = NULL;
    n->direita = NULL;
}

void inserir(Arvore *a,No *r,No *n,int *cresceu) {
    int novo_fator;

    if(n->chave < r->chave) {
        if(r->esquerda == NULL) {
            r->esquerda = n;
            n->pai = r;
        }else{
            inserir(a,r->esquerda,n,cresceu);
        }

        novo_fator = -1;
    }else{
        if(r->direita == NULL){
            r->direita = n;
            n->pai = r;
        }else{
            inserir(a,r->direita,n,cresceu);
        }

        novo_fator = +1;
    }

    if(*cresceu) {
        r->fator += novo_fator;
    }

    if(r->fator == 0) {
        *cresceu = 0;
    }else if(r->fator == -2) {
        if(r->esquerda->fator == -1) {

            rotate_rr(a,r->esquerda);
        }else{
            rotate_ll(a,r->esquerda->direita);
            rotate_rr(a,r->esquerda);
        }

        *cresceu = 0;
    }else if(r->fator == 2){

        if(r->direita->fator == 1) {
            rotate_ll(a,r->direita);
        }else{
           rotate_rr(a,r->direita->esquerda);
           rotate_ll(a,r->direita);
        }

        *cresceu = 0;
    }
}


void rotate_rr(Arvore *a,No *n) {
    No *tmp_direita = n->direita;
    No *pai = n->pai;
    No *vo = n->pai->pai;

    if(vo != NULL){
            if(vo->direita == pai){
                vo->direita = n;
            }else{
                vo->esquerda = n;
            }
    }

    n->direita = n->pai;
    n->pai = n->pai->pai;
    n->direita->pai = n;
    n->direita->esquerda = tmp_direita;

    if(pai->esquerda != NULL){
            pai->esquerda->pai = pai;
    }

    if(n->esquerda!= NULL && n->esquerda->fator == 0 && n->direita->esquerda != NULL){
        n->fator = 1;
        n->direita->fator = -1;
    }else{
        n->fator = 0;
        n->direita->fator = 0;
    }

    if(a->raiz == n->direita){
        a->raiz = n;
    }
}

void rotate_ll(Arvore *a,No *n) {
    No *tmp_esquerda = n->esquerda;
    No *pai = n->pai;
    No *vo = n->pai->pai;

    if(vo != NULL){
            if(vo->esquerda == pai){
                vo->esquerda = n;
            }else{
                vo->direita = n;
            }
    }

    n->esquerda = n->pai;
    n->pai = n->pai->pai;
    n->esquerda->pai = n;
    n->esquerda->direita = tmp_esquerda;

    if(pai->direita != NULL){
            pai->direita->pai = pai;
    }

    if(n->direita!= NULL && n->direita->fator == 0 && n->esquerda->direita != NULL){
        n->fator = -1;
        n->esquerda->fator = 1;
    }else{
        n->fator = 0;
        n->esquerda->fator = 0;
    }



    if(a->raiz == n->esquerda) {
        a->raiz = n;
    }
}

void pre_order_walk(No *n) {
    if(n!=NULL) {
        printf("%d (%d)\n",n->chave,n->fator);
        pre_order_walk(n->esquerda);
        pre_order_walk(n->direita);
    }
}

No *antecessor(No *n){

    No *aux = n;
    if(n->direita != NULL){
        aux = antecessor(n->direita);
    }else{
        return aux;
    }

}

void recalcula(No* n){
    if(n->pai != NULL){
        if(n->pai->direita == n){
            n->pai->fator -= 1;
        }else{
            n->pai->fator -= -1;
        }

        if(n->pai->fator == 0){
            recalcula(n->pai);
        }
    }

}


void removeNo(Arvore *a,No *n, int chave){

    if(chave == n->chave){
            if(n->direita == NULL && n->esquerda == NULL){
                    if(n != a->raiz){
                        recalcula(n);
                        if(n->pai->direita == n){
                            n->pai->direita = NULL;
                            n->pai = NULL;
                        }else{
                            n->pai->esquerda = NULL;
                            n->pai = NULL;
                        }
                    }else{
                        a->raiz = NULL;
                    }

            }else{
                if(n->esquerda != NULL){

                    No *aux = antecessor(n->esquerda);
                    recalcula(aux);
                    n->chave = aux->chave;
                    if(aux->pai->direita == aux){
                            aux->pai->direita = NULL;
                        }else{
                            aux->pai->esquerda = NULL;
                        }
                    free(aux);

                }else{
                    recalcula(n);
                    if(n->pai != NULL){
                        n->pai->direita = n->direita;
                        n->direita = n->pai;
                    }else{
                        a->raiz = n->direita;
                        n->direita->pai = NULL;
                    }
                }
            }

    }else if(chave < n->chave && n->esquerda != NULL){
        removeNo(a,n->esquerda,chave);

    }else if(chave > n->chave && n->direita != NULL){
        removeNo(a,n->direita,chave);
    }else{
        printf("Chave não existe na arvore \n");
    }

    if(n->fator == -2) {
        if(n->esquerda->fator == -1 || n->esquerda->fator == 0) {

            rotate_rr(a,n->esquerda);
        }else{
            rotate_ll(a,n->esquerda->direita);
            rotate_rr(a,n->esquerda);
        }
    }else if(n->fator == 2){

        if(n->direita->fator == 1 || n->direita->fator == 0) {
            rotate_ll(a,n->direita);
        }else{
           rotate_rr(a,n->direita->esquerda);
           rotate_ll(a,n->direita);
        }

    }

}

void pre_order_walkEscrever(No *n,FILE *f){
    if(n!=NULL) {
        fprintf(f,"%d\n",n->chave);
        pre_order_walkEscrever(n->esquerda,f);
        pre_order_walkEscrever(n->direita,f);
    }

}
