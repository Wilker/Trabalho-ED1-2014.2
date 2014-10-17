/* 
 * File:   TPilha.h
 * Author: Wilker
 *
 * Created on 14 de Setembro de 2014, 16:19
 */

#ifndef TPILHA_H
#define	TPILHA_H
#include "TNo.h"

typedef struct pilha{
    TNo *prim;
}TPilha;

int vazia(TPilha *p);
TPilha *criaPilhaDeCartas (void);
void pushCarta(TPilha *p, char naipe, char carta);
char* pop(TPilha *p);
void libera (TPilha *p);

#endif	/* TPILHA_H */

