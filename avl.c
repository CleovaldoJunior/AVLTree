

#include <stdlib.h>
#include <stdio.h>
#include "avl.h"


struct no* Inserir(struct no* raiz, int key, int *cresceu){
    if(raiz == NULL){
        struct no* novo = (struct no*)malloc(sizeof(struct no));
        novo->key = key;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->fatorB = 0;
        *cresceu = 1;
        return novo;
    }
    if(key > raiz->key){
        raiz->dir = Inserir(raiz->dir, key, cresceu);
        if(*cresceu){
            switch (raiz->fatorB){

                case -1:
                    raiz->fatorB = 0;
                    *cresceu = 0;
                    break;
                case 0:
                    raiz->fatorB = 1;
                    *cresceu = 1;
                    break;
                case 1:
                    raiz->fatorB = 2;
                    raiz = rotacionar(raiz);
                    *cresceu = 0;
                    break;
            }
        }
    } else{
        raiz->esq = Inserir(raiz->esq, key , cresceu);
        if(*cresceu){
            switch(raiz->fatorB){
                case -1:
                    raiz->fatorB = -2;
                    raiz = rotacionar(raiz);
                    *cresceu = 0;
                    break;
                case 0:
                    raiz->fatorB = -1;
                    *cresceu = 1;
                    break;
                case 1:
                    raiz->fatorB = 0;
                    *cresceu = 0;
                    break;
            }
        }
    }
    return raiz;
}

struct no* rotacionar(struct no* pivo){
    if(pivo->fatorB == -2 && (pivo->esq->fatorB == -1 || pivo->esq->fatorB == 0 )){
        return rotacao_simples_direita(pivo);
    }
    if(pivo->fatorB == 2 && (pivo->dir->fatorB == 1 || pivo->dir->fatorB == 0)){
        return rotacao_simples_esquerda(pivo);
    }
    if(pivo->fatorB == -2 && pivo->esq->fatorB == 1){
        return rotacao_dupla_direita(pivo);
    }
    if(pivo->fatorB == 2 && pivo->dir->fatorB == -1){
        return rotacao_dupla_esquerda(pivo);
    }
}

struct no* rotacao_simples_direita(struct no* pivo){
    struct no* u = pivo->esq;
    pivo->esq = u->dir;
    u->dir = pivo;
    if(u->fatorB == 0){
        u->fatorB = 1;
        pivo->fatorB = -1;
    } else{
        u->fatorB = 0;
        pivo->fatorB = 0;
    }
    return u;
}

struct no* rotacao_simples_esquerda(struct no* pivo){
    struct no* u = pivo->dir;
    pivo->dir = u->esq;
    u->esq = pivo;
    if(u->fatorB == 0){
        pivo->fatorB = 1;
        u->fatorB = -1;
    } else{
        u->fatorB = 0;
        pivo->fatorB  = 0;
    }
    return u;
}

struct no* rotacao_dupla_direita(struct no* pivo){
    struct no* u = pivo->esq;
    struct no* v = u->dir;
    switch (v->fatorB){
        case -1:
            pivo->esq = v->dir;
            u->dir = v->esq;
            v->dir = pivo;
            v->esq = u;
            u->fatorB = 0;
            v->fatorB = 0;
            pivo->fatorB = 1;
            return v;
        case 0:
            if(u->fatorB == 0){
                pivo->esq = v->dir;
                u->dir = v->esq;
                v->dir = pivo;
                v->esq = u;
                u->fatorB = -1;
                v->fatorB = -1;
                pivo->fatorB = 0;
                return v;
            }
            pivo->esq = v->dir;
            u->dir = v->esq;
            v->dir = pivo;
            v->esq = u;
            u->fatorB = 0;
            v->fatorB = 0;
            pivo->fatorB = 0;

            return v;
        case 1:
            pivo->esq = v->dir;
            u->dir = v->esq;
            v->dir = pivo;
            v->esq = u;
            u->fatorB = -1;
            v->fatorB = 0;
            pivo->fatorB = 0;
            return v;
    }
}

struct no* rotacao_dupla_esquerda(struct no* pivo){
    struct no* u = pivo->dir;
    struct no* v = u->esq;
    switch (v->fatorB){

        case -1:
            u->esq = v->dir;
            pivo->dir = v->esq;
            v->dir = u;
            v->esq = pivo;
            u->fatorB = 1;
            v->fatorB = 0;
            pivo->fatorB = 0;
            return v;
        case 0:
            if(u->fatorB == 0){
                u->esq = v->dir;
                pivo->dir = v->esq;
                v->dir = u;
                v->esq = pivo;
                u->fatorB = 1;
                v->fatorB = 1;
                pivo->fatorB = 0;
                return v;
            }
            u->esq = v->dir;
            pivo->dir = v->esq;
            v->dir = u;
            v->esq = pivo;
            u->fatorB = 0;
            v->fatorB = 0;
            pivo->fatorB = 0;
            return v;
        case 1:
            u->esq = v->dir;
            pivo->dir = v->esq;
            v->dir = u;
            v->esq = pivo;
            v->fatorB = 0;
            u->fatorB = 0;
            pivo->fatorB = -1;
            return v;

    }
}



struct no* Remover(struct no* raiz, int key, int *diminuiu, int pai_fb){
    if(raiz == NULL){
        *diminuiu = 0;
        return NULL;
    }

    if(raiz->key == key){
    
        if(raiz->dir == NULL && raiz->esq == NULL){

            switch (pai_fb){

                case 0:
                    *diminuiu = 0;
                    free(raiz);
                    return NULL;
                case -1:
                    *diminuiu = 1;
                    free(raiz);
                    return NULL;
                case 1:
                    *diminuiu = 1;
                    free(raiz);
                    return NULL;
            }
       
        if(raiz->dir == NULL && raiz->esq != NULL){
            *diminuiu = 1;
            free(raiz);
            return raiz->esq;
        }
        // key tem filho a direita.
        if(raiz->esq == NULL && raiz->dir != NULL){
            *diminuiu = 1;
            free(raiz);
            return raiz->dir;
        }
        //key tem dois filhos.
        if(raiz->dir != NULL && raiz->esq != NULL){
            switch (raiz->fatorB){
                // as duas sub_arvores sao iguais.
                case 0:
                    raiz->key = Maior(raiz->esq);
                    raiz->esq = Remover(raiz->esq, raiz->key, diminuiu, pai_fb);
                    if(*diminuiu){
                        raiz->fatorB = 1;
                    } else{
                        if(raiz->esq == NULL){
                            raiz->fatorB = 1;
                        } else{
                            raiz->fatorB = 0;
                        }
                    }
                    *diminuiu = 0;
                    break;
                //sub_arvore da direita é maior
                case 1:
                    raiz->key = Menor(raiz->dir);
                    raiz->dir = Remover(raiz->dir, raiz->key, diminuiu, pai_fb);
                    if(*diminuiu){
                        raiz->fatorB = 0;
                        *diminuiu = 1;
                    } else{
                        *diminuiu = 0;
                    }
                    break;
                // sub_arvore da esquerda é maior;
                case -1:
                    raiz->key = Maior(raiz->esq);
                    raiz->esq = Remover(raiz->esq, raiz->key, diminuiu, pai_fb);
                    if(*diminuiu){
                        raiz->fatorB = 0;
                        *diminuiu = 1;
                    } else{
                        *diminuiu = 0;
                    }
                    break;
            }
            return raiz;
        }

    }// PROCURA DIREITA.
    if(key > raiz->key){

        pai_fb = raiz->fatorB;
        raiz->dir = Remover(raiz->dir, key, diminuiu, raiz->fatorB);
        if(*diminuiu){
            // Pai se tornou folha.
            if(raiz->dir == NULL && raiz->esq == NULL){
                raiz->fatorB = 0;
                *diminuiu = 1;
            }
            // Remoção Direita NULL e tem sub_arvores a esquerda.
            if(raiz->dir == NULL && raiz->esq != NULL){
                switch (raiz->fatorB){
                    case 0:
                        raiz->fatorB = -1;
                        *diminuiu = 0;
                        break;
                    case -1:
                        raiz->fatorB = -2;
                        if(raiz->esq->fatorB == 0){
                            *diminuiu = 0;
                        } else{
                            *diminuiu = 1;
                        }

                        raiz = rotacionar(raiz);
                        break;
                }
                return raiz;

            }
            // Remoção Esquerda NULL e tem subarvore a direita;
            if(raiz->esq == NULL && raiz->dir != NULL){
                switch (raiz->fatorB){
                    case 0:
                        raiz->fatorB = 1;
                        *diminuiu = 0;
                        break;
                    case 1:
                        raiz->fatorB = 2;
                        *diminuiu = 1;
                        raiz = rotacionar(raiz);
                        break;

                }
                return raiz;

            }
            // REMOÇAO A DIREITA E ESQUERDA TEM AMBAS AS SUB_ARVORES
            if(raiz->dir != NULL && raiz->esq != NULL){

                switch (raiz->fatorB){
                    case 0:
                        raiz->fatorB = -1;
                        *diminuiu = 0;
                        break;
                    case 1:
                        raiz->fatorB = 0;
                        *diminuiu = 1;
                        break;
                    case -1:
                        raiz->fatorB = -2;
                        if(raiz->esq->fatorB == 0){
                            *diminuiu = 0;
                        } else{
                            *diminuiu = 1;
                        }
                        raiz = rotacionar(raiz);
                        break;
                }
                return raiz;


            }

            //NÃO DIMINUIU
        }else{
            if(raiz->dir != NULL && raiz->esq != NULL){
                ;
            }else{
                raiz->fatorB = -1;

            }
            *diminuiu = 0;
            return raiz;
        }

    }//PROCURA ESQUERDA
    else{
        pai_fb = raiz->fatorB;
        raiz->esq = Remover(raiz->esq, key, diminuiu, pai_fb);
        if(*diminuiu){
            // Pai se tornou folha.
            if(raiz->dir == NULL && raiz->esq == NULL){
                raiz->fatorB = 0;
                *diminuiu = 1;
            }
            // Remoção Direita NULL e tem sub_arvores a esquerda.
            if(raiz->dir == NULL && raiz->esq != NULL){
                switch (raiz->fatorB){
                    case 0:
                        raiz->fatorB = -1;
                        *diminuiu = 0;
                        break;
                    case -1:
                        raiz->fatorB = -2;
                        *diminuiu = 1;
                        raiz = rotacionar(raiz);
                        break;



                }
                return raiz;

            }
            // Remoção Esquerda NULL e tem subarvore a direita;
            if(raiz->esq == NULL && raiz->dir != NULL){
                switch (raiz->fatorB){
                    case 0:
                        raiz->fatorB = 1;
                        *diminuiu = 0;
                        break;
                    case 1:
                        raiz->fatorB = 2;
                        if(raiz->dir->fatorB == 0){
                            *diminuiu = 0;
                        } else{
                            *diminuiu = 1;
                        }
                        raiz = rotacionar(raiz);
                        break;

                }
                return raiz;

            }// REMOÇAO DA ESQUEDA E TEM AMBAS AS SUB-ARVORES.
            if(raiz->dir != NULL && raiz->esq != NULL){
                switch (raiz->fatorB){
                    case 0:
                        raiz->fatorB = 1;
                        *diminuiu = 0;
                        break;
                    case -1:
                        raiz->fatorB = 0;
                        *diminuiu = 1;
                        break;
                    case 1:
                        raiz->fatorB = 2;
                        *diminuiu = 1;
                        raiz = rotacionar(raiz);
                        break;


                }
                return raiz;

            }
        }
        //NÃO DIMINUIU
        else{
            if(raiz->esq != NULL && raiz->dir != NULL){
                ;
            }else{
                raiz->fatorB = 1;
            }
            *diminuiu = 0;
            return raiz;


        }
    }
    return raiz;
}


void pre_order(struct no *raiz){
    if(raiz == NULL){
        ;
    } else{
        printf("[%d,%d]", raiz->key, raiz->fatorB);
        pre_order(raiz->esq);
        pre_order(raiz->dir);

    }
}

void in_order(struct no *raiz){
    if(raiz == NULL){
        ;
    } else{
        in_order(raiz->esq);
        printf("[%d]", raiz->key);
        in_order(raiz->dir);

    }
}

void pos_order(struct no *raiz){
    if(raiz == NULL){
        ;
    } else{
        pos_order(raiz->esq);
        pos_order(raiz->dir);
        printf("[%d]", raiz->key);
    }

}

int altura_arvore(struct no* raiz){
    if(raiz == NULL){
        return -1;
    } else{
        int altura_esq = altura_arvore(raiz->esq);
        int altura_dir = altura_arvore(raiz->dir);
        if(altura_esq < altura_dir){
            return altura_dir+1;
        } else{
            return altura_esq+1;
        }
    }

}

int Maior(struct no *raiz){
    struct no *aux = raiz;
    if(aux == NULL){
        return 0;
    } else{
        while(aux->dir != NULL){
            aux = aux->dir;
        }
        return aux->key;

    }

}

int Maior_exibir(struct no *raiz){
    int maior = Maior(raiz);
    printf("[%d]", maior);
}

int Menor(struct no *raiz){
    struct no *aux = raiz;
    if(aux == NULL){
        return 0;
    }else{
        while(aux->esq != NULL){
            aux = aux->esq;
        }
        return aux->key;

    }
}

int Menor_exibir(struct no *raiz){
    int menor = Menor(raiz);
    printf("[%d]",menor);
}

