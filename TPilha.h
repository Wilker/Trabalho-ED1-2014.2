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
TPilha *cria (void);
void push(TPilha *p, int elem);
int pop(TPilha *p);
void libera (TPilha *p);

#endif	/* TPILHA_H */

