#include <stdio.h>
#include <stdlib.h>

#define RED   1
#define BLACK 0

typedef struct arvoreRB {
    int info;
    int cor;
    struct arvoreRB *esq;
    struct arvoreRB *dir;
} ArvoreRB;

int buscar(ArvoreRB *a, int v) {
    if (a == NULL) { return 0; } /*Nao achou*/
    else if (v < a->info) {
        return buscar(a->esq, v);
    } else if (v > a->info) {
        return buscar(a->dir, v);
    } else { return 1; }
}

ArvoreRB *rot_esq(ArvoreRB *no) {
    ArvoreRB *x = no->dir;
    no->dir = x->esq;
    x->esq = no;
    x->cor = no->cor;
    no->cor = RED;
    return (x);
}

ArvoreRB *rot_dir(ArvoreRB *no) {
    ArvoreRB *x = no->esq;
    no->esq = x->dir;
    x->dir = no;
    x->cor = no->cor;
    no->cor = RED;
    return (x);
}

ArvoreRB *flip_cor(ArvoreRB *no) {
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
    return (no);
}

ArvoreRB *fix(ArvoreRB *a) {

        if ((a->esq == NULL && a->dir != NULL && a->dir->cor == RED) ||
            (a->esq != NULL && a->dir != NULL && a->dir->cor == RED && a->esq->cor == BLACK)) {
            a = rot_esq(a);
        }

        if (a->esq != NULL && a->esq->cor == RED && a->esq->esq != NULL && a->esq->esq->cor == RED) {
            a = rot_dir(a);

        }

        if (a->esq != NULL && a->esq->cor == RED && a->dir != NULL && a->dir->cor == RED) {
            a = flip_cor(a);
        }

    return a;
}

ArvoreRB *remover_aux(ArvoreRB *a, int x) {
    ArvoreRB *aux, *pai_aux;
    int filhos = 0, tmp;

    if (!a)
        return (NULL);

    if (a->info < x)
        a->dir = remover_aux(a->dir, x);
    else if (a->info > x)
        a->esq = remover_aux(a->esq, x);
    else {
        if (a->esq)
            filhos++;
        if (a->dir)
            filhos++;

        if (filhos == 0) {
            free(a);
            return (NULL);
        } else if (filhos == 1) {
            aux = a->esq ? a->esq : a->dir;
            free(a);
            return (aux);
        } else {
            aux = a->esq;
            pai_aux = a;
            while (aux->dir) {
                pai_aux = aux;
                aux = aux->dir;
            }
            tmp = a->info;
            a->info = aux->info;
            aux->info = tmp;
            pai_aux->dir = remover_aux(aux, tmp);
            a = fix(a);
            return (a);
        }
    }
    a = fix(a);
    return (a);
}

ArvoreRB *remover(ArvoreRB *a, int x) {
    a = remover_aux(a, x);
    if (a->esq != NULL && a->cor == RED && a->esq->cor == RED  && a->dir != NULL && a->dir->cor == BLACK){
        a->cor = BLACK;
    }
    return a;
}

ArvoreRB *inserir_aux(ArvoreRB *a, int v) {
    if (a == NULL) {
        a = (ArvoreRB *) malloc(sizeof(ArvoreRB));
        a->info = v;
        a->esq = a->dir = NULL;
        a->cor = RED;
        a = fix(a);
    } else if (v < a->info) {
        a->esq = inserir_aux(a->esq, v);
    } else {
        a->dir = inserir_aux(a->dir, v);
    }
    a = fix(a);
    return a;
}

ArvoreRB *inserir(ArvoreRB *a, int v) {
    a = inserir_aux(a, v);
    if (a->esq != NULL && a->cor == RED && a->esq->cor == RED  && a->dir != NULL && a->dir->cor == BLACK){
        a->cor = BLACK;
    }
    return a;
}

void in_order(ArvoreRB *a) {
    if (!a)
        return;
    in_order(a->esq);
    printf("%d ", a->info);
    in_order(a->dir);
}

void print(ArvoreRB *a, int spaces) {
    int i;
    for (i = 0; i < spaces; i++) printf(" ");
    if (!a) {
        printf("//\n");
        return;
    }

    printf("%d%s\n", a->info, a->cor == 1 ? "R" : "B");
    print(a->esq, spaces + 2);
    print(a->dir, spaces + 2);
}

int main() {
    ArvoreRB *a;
    a = inserir(NULL, 50);
    a = inserir(a, 30);
    a = inserir(a, 90);
    a = inserir(a, 20);
    a = inserir(a, 100);
    a = inserir(a, 80);
    a = inserir(a, 10);
    a = inserir(a, 35);
    a = inserir(a, 45);
    a = inserir(a, 37);
    a = inserir(a, 48);
    a = remover(a, 50);

    printf("\n");
    print(a, 0);
}

