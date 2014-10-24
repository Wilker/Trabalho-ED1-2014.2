/*  File: main.c Author: Wilker Created on 14 de Setembro de
   2014, 16:17 */

#include <stdio.h>
#include <stdlib.h>
#include "TPilha.h"
#include "Freecell.h"

/* 
 * 
 */
int main(int argc, char **argv)
{
	printf("%d\n", argc);
	printf("%s\n", argv[1]);
	if (argc < 2)
	{
		printf("Passe o arquivo via linha de comando!!");
		system("PAUSE");
		exit(1);
	}

	// Cria um ponteiro para uma strutct do jogo alocada dinamicamente

	printf("Antes do jogo");
	Freecell *jogo = (Freecell *) malloc(sizeof(Freecell));
   inicializaFreecell(jogo);
    // jogo->cartas[0]criaPilhaDeCartas

	// Cria a mesa do jogo;
	criaMesa(jogo);
	// Distribui a pilha de Cartas inicial com o caminho do arquivo passado
	// via linha de comando 
	//preenchePilhaDeCartas(jogo, argv[1]);
	//free(jogo);
	system("PAUSE");
	return 0;
}