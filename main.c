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
    
    /**Menu no jogo
    */
 int escolha=1;
 // se a escolha for diferente de 5, ele continua... o que inicialmente é verdade
 // pois escolha é igual a 1
 while (escolha!=0)
 {printf("\n\n ----------------------- ");
  printf("\n 1 - Opcao 1 ");
  printf("\n 2 - Opcao 2 ");
  printf("\n 3 - Opcao 3 ");
  printf("\n 4 - Opcao 4 ");
  printf("\n 5 - Opcao 5 ");
  printf("\n 6 - Opcao 6 ");
  printf("\n 7 - Opcao 7 ");
  printf("\n 8 - Opcao 8 ");
  printf("\n 0 - Fechar Programa ");
  printf("\n\n Escolha uma opcao: ");
  scanf_s("%d",&escolha);

  // estrutura switch
  switch (escolha) {
  case 1:
   {
    break;
   }
  case 2:
   {
     break;
   }
  case 3:
   {
    break;
   }
  case 4:
   {
  break;
   }
  case 5:
   {
    break;
   }
  case 6:
   {
    break;
   }
  case 7:
   {  
    break;
   }
  case 8:
   {
    break;
   }
   // opção padrão
  default:
   {
    // se for escolhida a opção 0, ele pula o while utilizando continue para isso 
    if( escolha==0)
    {
     continue;
    }
    // caso o usuário digite um numero acima de 16, ele irá informar que nao existe essa opção
    printf("\n\n Nenhuma opcao foi escolhida ");
    break;
   }
  }
 }
 if( escolha==0)
 {
  printf("\n\n O Programa foi fechado");
  _getch(); 
 }
 return;
}
        
    //Daqui para baixo e teste para leitura do arquivo
    char tmp[3]; // Não sei o motivo mas têm que ser tamanho mínimo 3 e não 2. :s O que sei é q ele tá pegando o espaço :s
    //Para no linux ler direto do arquivo como se fosse do teclado, basta mudar o argumento "fp" para "stdin"
    fscanf(fp, " %2[^\n]", tmp); // lê até dois caracteres ou até um caractere de nova linha.
    while (!feof(fp)) {
        printf("=> %c_%c\n", tmp[0],tmp[1]); 
        fscanf(fp, " %2[^\n]", tmp);
    }
    fclose(fp);
    system("pause");
    return (EXIT_SUCCESS);
}
