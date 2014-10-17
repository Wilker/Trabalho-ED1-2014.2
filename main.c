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
    char tmp[10];
    fscanf(fp, " %2[^\n]", tmp); // lê até dois caracteres ou até um caractere de nova linha.
    while (!feof(fp)) {
        printf("=> %s \n", tmp); 
        fscanf(fp, " %2[^\n]", tmp); // lê até dois caracteres ou até um caractere de nova linha.
    }
    system("pause");
    return (EXIT_SUCCESS);
}

