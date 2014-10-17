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

void push(TPilha *p, char naipe, char carta) {
    TNo *novo = (TNo*) malloc(sizeof (TNo));
    novo-> naipe = naipe;
    novo->carta = carta;
    novo-> prox = p->prim;
    p->prim = novo;
}
/**
 * 
 * @param p
 * @return String de tam 2, onde primeiro char é o naipe e o segundo a carta
 */
char* pop(TPilha *p) {
    if (vazia(p)exit(1)); 
    char resp[2] = p->prim->naipe;
    strcat(resp,p->prim->carta); // concatena o char da carta no naipe para poder retornar;
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