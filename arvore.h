#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valor;
} tiporegistro;

typedef struct tipono* tipoapontador;

typedef struct tipono {
    tiporegistro reg;
    tipoapontador esq, dir;
    int peso;
} tipono;

void inicializa(tipoapontador* raiz) {
    *raiz = NULL;
}

void insere(tipoapontador* raiz, tiporegistro x) {
    if (*raiz == NULL) {
        *raiz = (tipoapontador) malloc(sizeof (tipono));
        (*raiz)->reg = x;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        return;
    }
    if (x.valor < (*raiz)->reg.valor) {
        insere(&(*raiz)->esq, x);
        return;
    }
    if (x.valor > (*raiz)->reg.valor) {
        insere(&(*raiz)->dir, x);
    } else {
        printf("Erro: Registro já existente na árvore!\n");
    }
}

void pesquisa(tipoapontador* raiz, tiporegistro* x) {
    if (*raiz == NULL) {
        printf("Erro: Registro não encontrado na arvore!\n");
        return;
    }
    if (x->valor < (*raiz)->reg.valor) {
        pesquisa(&(*raiz)->esq, x);
        return;
    }
    if (x->valor > (*raiz)->reg.valor) {
        pesquisa(&(*raiz)->dir, x);
    } else
        *x = (*raiz)->reg;
}

void antecessor(tipoapontador* raiz, tipoapontador q) {
    if ((*raiz)->dir != NULL) {
        antecessor(&(*raiz)->dir, q);
        return;
    }
    q->reg = (*raiz)->reg;
    q = *raiz;
    *raiz = (*raiz)->esq;
    free(q);
}

void retira(tipoapontador* raiz, tiporegistro x) {
    tipoapontador aux;
    if (*raiz == NULL) {
        printf("Erro: Registro não está presente na áervore\n");
        return;
    }
    if (x.valor < (*raiz)->reg.valor) {
        retira(&(*raiz)->esq, x);
        return;
    }
    if (x.valor > (*raiz)->reg.valor) {
        retira(&(*raiz)->dir, x);
        return;
    }
    if ((*raiz)->dir == NULL) {
        aux = *raiz;
        *raiz = (*raiz)->esq;
        free(aux);
        return;
    }
    if ((*raiz)->esq != NULL) {
        antecessor(&(*raiz)->esq, *raiz);
        return;
    }
    aux = *raiz;
    *raiz = (*raiz)->dir;
    free(aux);
}

void imprimircentral(tipoapontador* raiz) {
    if (*raiz == NULL) {
        return;
    }
    if ((*raiz)->esq != NULL) {
        imprimircentral(&(*raiz)->esq);
    }
    printf("%5d\n", (*raiz)->reg.valor);
    if ((*raiz)->dir != NULL) {
        imprimircentral(&(*raiz)->dir);
    }
}

void imprimirpre(tipoapontador* raiz) {
    if (*raiz != NULL) {
        printf("%5d\n", (*raiz)->reg.valor);
    }
    if ((*raiz)->esq != NULL) {
        imprimirpre(&(*raiz)->esq);
    }
    if ((*raiz)->dir != NULL) {
        imprimirpre(&(*raiz)->dir);
    } else {
        return;
    }
}

void imprimirpos(tipoapontador* raiz) {
    if (*raiz == NULL) {
        return;
    }
    if ((*raiz)->esq != NULL) {
        imprimirpos(&(*raiz)->esq);
    }
    if ((*raiz)->dir != NULL) {
        imprimirpos(&(*raiz)->dir);
    }
    printf("%5d\n", (*raiz)->reg.valor);
}

int getPeso(tipoapontador * raiz) {
    if (*raiz == NULL)
        return 0;
    else
        return (*raiz)->peso;
}

int maxPeso(int esqPeso, int dirPeso) {
    if (esqPeso > dirPeso)
        return esqPeso;
    else
        return dirPeso;
}

void rotacaosimplesdireita(tipoapontador * raiz) {
    tipoapontador aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    (*raiz)->peso = maxPeso(getPeso(&(*raiz)->esq), getPeso(&(*raiz)->dir)) + 1;
    aux->peso = maxPeso(getPeso(&aux->esq), (*raiz)->peso) + 1;
    *raiz = aux;
}

void rotacaosimplesesquerda(tipoapontador * raiz) {
    tipoapontador aux;

    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    (*raiz)->peso = maxPeso(getPeso(&(*raiz)->esq), getPeso(&(*raiz)->dir)) + 1;
    aux->peso = maxPeso(getPeso(&aux->dir), (*raiz)->peso) + 1;
    *raiz = aux;
}

void duplaesquerdadireita(tipoapontador * raiz) {
    rotacaosimplesesquerda(&(*raiz)->esq);
    rotacaosimplesdireita(raiz);
}

void dupladireitaesquerda(tipoapontador * raiz) {
    rotacaosimplesdireita(&(*raiz)->dir);
    rotacaosimplesesquerda(raiz);
}

void insereBalanceado(tipoapontador* raiz, tiporegistro x) {
    if (*raiz == NULL) {
        *raiz = (tipoapontador) malloc(sizeof (tipono));
        (*raiz)->reg = x;
        (*raiz)->peso = 0;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    } else if (x.valor < (*raiz)->reg.valor) {
        insereBalanceado(&(*raiz)->esq, x);

        if (getPeso(&(*raiz)->esq) - getPeso(&(*raiz)->dir) == 2) {
            if (x.valor < (*raiz)->esq->reg.valor)
                rotacaosimplesdireita(raiz);
            else
                duplaesquerdadireita(raiz);
        }
    } else if (x.valor > (*raiz)->reg.valor) {
        insereBalanceado(&(*raiz)->dir, x);

        if (getPeso(&(*raiz)->dir) - getPeso(&(*raiz)->esq) == 2) {
            if (x.valor > (*raiz)->dir->reg.valor)
                rotacaosimplesesquerda(raiz);
            else
                dupladireitaesquerda(raiz);
        }
    }
    (*raiz)->peso = maxPeso(getPeso(&(*raiz)->esq), getPeso(&(*raiz)->dir))+1;
}