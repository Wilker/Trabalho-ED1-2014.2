/*  File: main.c Author: Wilker Created on 14 de Setembro de
   2014, 16:17 */

#include <stdio.h>
#include <stdlib.h>
#include "TPilha.h"
#include "Freecell.h"

/* 
 * 
 */
int main(int argc, char **argv) {
    printf("%d\n", argc);
    printf("%s\n", argv[1]);
    if (argc < 2) {
        printf("Passe o arquivo via linha de comando!!");
        system("PAUSE");
        exit(1);
    }
    Freecell* jogo = inicializaFreecell();
    preenchePilhaDeCartas(jogo, argv[1]);
    free(jogo);
    system("PAUSE");
    return 0;
}