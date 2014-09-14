#include "TPilha.h"
#include <stdio.h>
#include <stdlib.h>

TPilha *cria(void) {
    TPilha *p = (TPilha*) malloc(sizeof (TPilha));
    p->prim = NULL;
    return p;
}

int vazia(TPilha *p) {
    return p->prim == NULL;
}

void push(TPilha *p, int elem) {
    TNo *novo = (TNo*) malloc(sizeof (TNo));
    novo-> info = elem;
    novo-> prox = p->prim;
    p->prim = novo;
}

int pop(TPilha *p) {
    if (vazia(p)exit(1));
    int resp = p->prim->info;
    TNo *q = p->prim;
    p->prim = p->prim->prox;
    free(q);
    return resp;
}

void libera(TPilha *p) {
    TNo *q = p->prim;
    while (q) {
        TNo *r = q;
        q = q->prox;
        free(r);
    }
    free(p);
}