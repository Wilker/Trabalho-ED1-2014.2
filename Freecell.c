#include "TPilha.h"
#include "Freecell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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



void criaMesa(Freecell *freecell) {
    int i;
    for (i = 0; i < TAM_PILHAS_CARTAS; i++) {
        freecell->cartas[i] = criaPilhaDeCartas();
    }
    for (i = 0; i < TAM_PILHAS_NAIPE; i++) {
        freecell->naipe[i] = criaPilhaDeCartas();
    }
    for (i = 0; i < TAM_PILHAS_RESERVA; i++) {
        freecell->reserva[i] = criaPilhaDeCartas();
    }
}

/**
 * Recebe uma String de movimentação com 2 caracteres, o primeiro é a pilha de origem
 * e o segundo a pilha de destino
 * --------------------------------------------------
 * Pilhas de A a H são as pilhas de Cartas
 * Pilhas de 0 a 3 são as pilhas agrupadas pelo naipe
 * Pilhas de W a Z são as pilhas reservas 
 * --------------------------------------------------
 * @param mover cadeia de Char de tam 2, onde o primeiro char é a pilha de origem e o segundo char é a pilha de destino
 * @param freecell strutuct do jogo. Contém as pilhas dos jogo.
 * @return 1 se foi possível realizar o movimento e 0 caso contrário e -1 caso a string seja
 * inválida
 */
int moveCartaDaPilha(char *mover, Freecell *freecell) {
    if (strlen(mover) < 2) return -1;
    char *tmp = (char *) malloc(3 * sizeof (char));
    //Esta parte resolve a pilha de origem
    if ((mover[0] >= 'A') && (mover[0] <= 'H')) {
        tmp = pop(freecell->cartas[mover[0] - 65]); // Código ASCII da Letra A é 65, descontando 65 dará a pilha correta que devera ser movida a carta
    }
    if ((mover[0] >= '0') && (mover[0] <= '3')) {
        tmp = pop(freecell->naipe[mover[0]]);
    }
    if ((mover[0] >= 'W') && (mover[0] <= 'Z')) { // Código ASCII da Letra A é  87, descontando 65 dará a pilha correta que devera ser movida a carta
        tmp = pop(freecell->reserva[mover[0] - 87]);
    }
    //Esta parte, resolve a pilha de destino
    //Rever esta parte, pois estou caindo de sono!!
    if ((mover[1] >= 'A') && (mover[1] <= 'H')) {
        pushCarta(freecell->cartas[mover[1] - 65], tmp[0], tmp[1]); // Código ASCII da Letra A é 65, descontando 65 dará a pilha correta que devera ser movida a carta
    }
    if ((mover[1] >= '0') && (mover[1] <= '3')) {
        pushCarta(freecell->naipe[mover[1]], tmp[0], tmp[1]);
    }
    if ((mover[1] >= 'W') && (mover[1] <= 'Z')) { // Código ASCII da Letra A é  87, descontando 65 dará a pilha correta que devera ser movida a carta
        pushCarta(freecell->reserva[mover[1 - 87]], tmp[0], tmp[1]);
    }
}

/**
 * Imprime estado atual do jogo, o topo das pilhas de cartas.
 * @param freecell 
 */
void imprimePilhas(Freecell *freecell) {
    int i;
    for (i = 0; i < TAM_PILHAS_CARTAS; i++) {
        if (!vazia(freecell->cartas[i])) { //verifica se a pilha está vazia
            printf("%c%c ", freecell->cartas[i]->prim->naipe, freecell->cartas[i]->prim->carta);
        } else
            printf(" Pilha Vazia  ");
        if (i == 7)printf("\n");
    }
}

/**Le um arquivo com os comandos
 * @param arq ponteiro para o arquivo com os comandos
 * @param freecell instancia do jogo sobre qual serao realizados os comandos
 */
void play(FILE *arq, Freecell *freecell) {
    //Teste apenas para ver se todas as pilhas estão com cartas.
    imprimePilhas(freecell);
    if (!arq) {
        printf("Erro na abertura do arquivo, tente novamente:");
        exit(1);
    }
    char comando[3];
    fscanf(arq, " %2[^\n]", comando);
    while (!feof(arq)) {
        if (comando[0] == '*') {// Se o primeiro caractere do comando for  *  entao sera um comando de impressao do estado atual;
            imprimePilhas(freecell);
        } else { //caso contrario sera um comando de movimentaçao
            int r = moveCartaDaPilha(comando, freecell);
            if (r == -1) scanf("Sting de comando Invalida");
            fscanf(arq, " %2[^\n]", comando);
        }
        fclose(arq);
    }
}

void preenchePilhaDeCartas(Freecell *freecell, char* caminho) {
    // O lance aqui é fazer um contador de 1 a 52, enqt cont <52 ele distrubui as cartas
    int cont = 0; //contador para a quantidade de cartas que será lida do arquivo
    int contPilha = 0; // contador para saber em qual pilha será inserida a carta
    FILE* fp = fopen(caminho, "r"); //abre o arquivo para leitura
    if (!fp) {
        printf("Erro na abertura do arquivo, tente novamente:");
        exit(1);
    }

    char tmp[3]; // Não sei o motivo mas têm que ser tamanho mínimo 3 e não 2. :s EDIT: AGORA LEMBREI QUE TEM Q TER O CARACTERE '\0' INDICANDO FIM DA LINHA
    fscanf(fp, " %2[^\n]", tmp); // lê até dois caracteres ou até um caractere de nova linha.
    while (!feof(fp) && cont < 52) {
        pushCarta(freecell->cartas[contPilha], tmp[0], tmp[1]);
        cont++;
        contPilha++;
        if (contPilha == 8) contPilha = 0;
        fscanf(fp, " %2[^\n]", tmp);
    }
    play(fp, freecell); //gambiarra para pegar o arquivo ja aberto apontando(eu espero) para a proxima linha onde começam o comandos no arquivo
    fclose(fp);
}

/**
 * Inicializa todos os vetores com NULL;
 * @param freecell
 */
Freecell* inicializaFreecell(void) {
    int i;
    Freecell* freecell = (Freecell*) malloc(sizeof (Freecell));
    //Aloca espaço TAM_PILAS_CARTAS ponteiros de pilhas de cartas
    freecell->cartas = (TPilha**) malloc(TAM_PILHAS_CARTAS * sizeof (TPilha*));
    if (freecell->cartas != NULL) {
        for (i = 0; i < TAM_PILHAS_CARTAS; i++) {
            freecell->cartas[i] = NULL;
            printf("%p\n", &freecell->cartas[i]); //Imprime na tela os endereços  dos ponteiros Cartas
        }printf("\n"); 
    } else {
        printf("Erro na alocação do vetor freecell->cartas");
        exit(10);
    }
    //Aloca espaço TAM_PILAS_NAIPE ponteiros de pilhas de naipe
    freecell->naipe = (TPilha**) malloc(TAM_PILHAS_NAIPE * sizeof (TPilha*));
    if (freecell->naipe != NULL) {
        for (i = 0; i < TAM_PILHAS_NAIPE; i++) {
            freecell->naipe[i] = NULL;
            printf("%p\n", &freecell->naipe[i]);
        }
        printf("\n"); 
    } else {
        printf("Erro na alocação do vetor freecell->naipe");
        exit(11);
    }
    //Aloca espaço TAM_PILAS_RESERVA ponteiros de pilhas de reserva
    freecell->reserva = (TPilha**) malloc(TAM_PILHAS_RESERVA * sizeof (TPilha*));
    if (freecell->reserva != NULL) {
        for (i = 0; i < TAM_PILHAS_RESERVA; i++) {
            freecell->reserva[i] = NULL;
            printf("%p\n", &freecell->reserva[i]);
        }printf("\n"); 
    } else {
        printf("Erro na alocação do vetor freecell->reserva");
        exit(12);
    }
    return freecell;
}