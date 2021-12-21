

#ifndef ARVOREAVL_AVL_H
#define ARVOREAVL_AVL_H

struct no{
    int key;
    struct no* esq;
    struct no* dir;
    int fatorB;
};

struct no* Inserir(struct no* raiz, int key, int *cresceu);

struct no* Remover(struct no* raiz, int key, int *diminuiu, int pai_fb);

void pre_order(struct no *raiz);

void in_order(struct no *raiz);

void pos_order(struct no *raiz);

int altura_arvore(struct no* raiz);

int Maior(struct no *raiz);

int Maior_exibir(struct no *raiz);

int Menor(struct no *raiz);

int Menor_exibir(struct no *raiz);

struct no* rotacionar(struct no* pivo);

struct no* rotacao_simples_direita(struct no* pivo);

struct no* rotacao_simples_esquerda(struct no* pivo);

struct no* rotacao_dupla_direita(struct no* pivo);

struct no* rotacao_dupla_esquerda(struct no* pivo);





#endif //ARVOREAVL_AVL_H
