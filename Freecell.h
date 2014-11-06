/* 
 * File:   Freecell.h
 * Author: Wilker
 *
 * Created on 16 de Outubro de 2014, 20:49
 */

#ifndef FREECELL_H
#define	FREECELL_H
typedef struct freecell {
    TPilha **pNaipe; // Pilhas de 0 a 3
    TPilha **pCartas; // Pilhas de A a H
    TPilha **pReserva; // Pilhas de W a Z
}Freecell;

Freecell* inicializaFreecell();
void criaMesa (Freecell *freecell);
void preenchePilhaDeCartas(Freecell *freecell, char* caminho);
void imprimePilhas(Freecell *freecell);

#endif	/* FREECELL_H */