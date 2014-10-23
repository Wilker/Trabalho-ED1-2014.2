#include "TPilha.h"
#include <stdio.h>
#include <stdlib.h>

TPilha *criaPilhaDeCartas(void) {
    TPilha *p = (TPilha*) malloc(sizeof (TPilha));
    p->prim = NULL;
    return p;
}

int vazia(TPilha *p) {
    return p->prim == NULL;
}

void pushCarta(TPilha *p, char naipe, char carta) {
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
    if (vazia(p))exit(1); 
    char *resp;
    resp[0]=p->prim->naipe;
    resp[1]=p->prim->carta;
    TNo *q = p->prim;
    p->prim = p->prim->prox;
    free(q);
    return resp; // Arrumar para retornar o conteúdo de resp.
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

//Falta implementar a impressão das pilhas de cartas, do estado atual do topo.