#include <stdlib.h>
#include <stdio.h>
#include "avl.c"

int main(){

    struct no* arvore = NULL;

    int opcao;

    int cresceu;

    while (1==1) {

        scanf("%d", &opcao);
        switch (opcao) {

            int n;

            case 1:
                scanf("%d", &n);
                arvore = Inserir(arvore, n, &cresceu);
                break;
            case 2:
                pre_order(arvore);
                printf("\n");
                break;
            case 3:
                scanf("%d", &n);
                arvore = Remover(arvore, n, &cresceu, 0);
                break;
            case 999:
                exit(0);
        }
    }
}

