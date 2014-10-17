#include "TPilha.h"
#include <stdio.h>
#include <stdlib.h>
#define TAM_PILHAS_CARTAS 8
#define TAM_PILHAS_NAIPE 4
#define TAM_PILHAS_RESERVA 4


/* Os naipes estão separados da seguinte forma '0' = copas, '1' = paus, '2' = ouro, '3' = espada
 * As cartas estão separadas da seguinte forma ('A' = às, 'B' = 2, 'C' = 3, ..., 'J' = 10, 'K'
= Valete, 'L' = Dama, 'M' = Re
 * 
 * O Par '1K' referese à carta Valete de paus, deste modo, a codificação é a seguinte
 * 1º Caractere Naipe, 2º Caractere Carta
 */

/**Passo 1 Criar a mesa do jogo. 
 * Criar 3 vetores de pilhas
 * *cartas é o vetor de pilha guarda as cartas iniciais do jogo;
 * A o vetor de pilhas *naipe é onde as cartas podem ser agrupadas pelo naipe;
 * E a o vetor de pilhas *reserva é onde pode-se colocar uma carta de qualquer pilha.
 *
 * @param cartas
 * @param naipe
 * @param reserva
 */
void criaMesa(TPilha **cartas, TPilha **naipe, TPilha **reserva) {
    int i;
    for (i = 0; i < TAM_PILHAS_CARTAS; i++) {
        cartas[i] = criaPilhaDeCartas();
    }
    for (i = 0; i < TAM_PILHAS_NAIPE; i++) {
        naipe[i] = criaPilhaDeCartas();
    }
    for (i = 0; i < TAM_PILHAS_RESERVA; i++) {
        reserva[i] = criaPilhaDeCartas();
    }
}

void preenchePilhaDeCartas(TPilha **pilha, char* caminho) {
    // O lance aqui é fazer um contador de 1 a 52, enqt cont <52 ele distrubui as cartas
    int cont = 1; //contador para a quantidade de cartas que será lida do arquivo
    int contPilha = 0; // contador para saber em qual pilha será inserida a carta
    FILE* fp = fopen(caminho, "r"); //abre o arquivo para leitura
    if (!fp) {
        printf("Erro na abertura do arquivo, tente novamente:");
        exit(1);
    }

    char tmp[3]; // Não sei o motivo mas têm que ser tamanho mínimo 3 e não 2. :s
    fscanf(fp, " %2[^\n]", tmp); // lê até dois caracteres ou até um caractere de nova linha.
    while (!feof(fp)) {
        pushCarta(pilha[contPilha], tmp[0], tmp[1]);
        cont++;
        contPilha++;
        if (contPilha == 8) contPilha = 0;
    }
    fscanf(fp, " %2[^\n]", tmp);
    fclose(fp);
} 