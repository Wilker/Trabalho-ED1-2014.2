/* 
 * File:   TNo.h
 * Author: Wilker
 *
 * Created on 14 de Setembro de 2014, 16:17
 */

#ifndef TNO_H
#define	TNO_H

typedef struct no{
    char naipe ;
    char carta;
    struct no *prox;
}TNo;

#endif	/* TNO_H */