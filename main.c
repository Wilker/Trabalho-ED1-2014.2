/* 
 * File:   main.c
 * Author: Wilker
 *
 * Created on 14 de Setembro de 2014, 16:17
 */

#include <stdio.h>
#include <stdlib.h>
#include "TPilha.h"

/*
 * 
 */
int main(int argc, char** argv) {
    FILE* fp = fopen("C:\\Users\\Wilker\\Documents\\NetBeansProjects\\Trabalho-ED1-2014.2\\entrada.txt", "r");
    if (!fp) {
        printf("Erro na abertura do arquivo, tente novamente:");
        exit(1);
    }
    char tmp[3]; // Não sei o motivo mas têm que ser tamanho mínimo 3 e não 2. :s O que sei é q ele tá pegando o espaço :s
    //Para no linux ler direto do arquivo como se fosse do teclado, basta mudar o argumento "fp" para "stdin"
    fscanf(fp, " %2[^\n]", tmp); // lê até dois caracteres ou até um caractere de nova linha.
    while (!feof(fp)) {
        printf("=> %c_%c\n", tmp[0],tmp[1]); 
        fscanf(fp, " %2[^\n]", tmp);
    }
    system("pause");
    return (EXIT_SUCCESS);
}

