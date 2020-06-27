#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    No *temp;
    Arvore *a;
    char opt = 1;
    int n,cresceu;

    a = criar_arvore();

    FILE *f;

    f = fopen("AvlArquivo.txt","r");

    int fimArquivo, chaveArquivo;
    No *tempArq;
    while(1){
        fimArquivo = fscanf(f,"%d",&chaveArquivo);
        if(fimArquivo != 1) break;
        tempArq = criar_no(chaveArquivo);
        if(a->raiz == NULL) {
                a->raiz = tempArq;
        }else{
                cresceu = 1;
                inserir(a,a->raiz,tempArq,&cresceu);
        }
    }

    fclose(f);


    while(opt) {

        printf("opcoes: \t\n");
        printf("1 inserir: \t\n");
        printf("2 ver : \t\n");
        printf("3 remover: \t\n");
        printf("4 Sair e Arquivar: \t\n");

        scanf("%s",&opt);

        switch(opt) {
        case '1':
            printf("Informe o número: ");
            scanf("%d",&n);
            temp = criar_no(n);

            if(a->raiz == NULL) {
                a->raiz = temp;
            }else{
                cresceu = 1;
                inserir(a,a->raiz,temp,&cresceu);
            }
            break;
        case '2':
            if(a->raiz != NULL) {
                printf("==== Arvore em pre ordem ==== \n");
                pre_order_walk(a->raiz);
            }else{
                printf("Árvore sem raiz!\n");
            }
            break;
        case '3':
            printf("Informe o número a ser removido: ");
            scanf("%d",&n);
            if(a->raiz == NULL) {
                printf("Arvore sem elementos\n");
            }else{
                removeNo(a,a->raiz,n);
            }
            break;
        case '4':
            opt = 0;
            break;
        }
    }
    f = fopen("AvlArquivo.txt","w");
    if(a->raiz != NULL) {
            pre_order_walkEscrever(a->raiz,f);
    }
    fclose(f);
    return 0;
}
