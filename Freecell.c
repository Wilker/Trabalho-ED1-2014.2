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
 * @return 1 se foi possível realizar o movimento, 0 caso contrário e -1 caso a string seja
 * inválida
 */
int moveCartaDaPilha(char *mover, Freecell *freecell) {
    if (strlen(mover) < 2) return -1;
    char *tmp = (char *) malloc(3 * sizeof (char));
    tmp[2] = '\0';
    int posOrigem = 666;
    char pilhaOrigem = ' ';
    //Esta parte resolve a pilha de origem
    if ((mover[0] >= 'A') && (mover[0] <= 'H')) { //Se estiver neste intervalo é a pilha de Cartas
        //Se não estiver vazia, realiza o pop!
        if (!vazia(freecell->pCartas[mover[0] - 65])) {
            tmp = pop(freecell->pCartas[mover[0] - 65]); // Código ASCII da Letra A é 65, descontando 65 dará a pilha correta que devera ser movida a carta
            posOrigem = mover[0] - 65;
            pilhaOrigem = 'c';
        }
    }
    if ((mover[0] >= '0') && (mover[0] <= '3')) { //Se estiver neste intervalo é a pilha de naipe
        //Se não tiver vazia realiza o pop!
        if (!vazia(freecell->pNaipe[mover[0]])) {
            tmp = pop(freecell->pNaipe[mover[0]]);
            posOrigem = mover[0] - 48;
            pilhaOrigem = 'n';
        }
    }
    if ((mover[0] >= 'W') && (mover[0] <= 'Z')) { //Se estiver neste intervalo é a pilha de naipe
        //Se não tiver vazia realiza o pop!
        if (!vazia(freecell->pReserva[mover[0] - 87])) {
            tmp = pop(freecell->pReserva[mover[0] - 87]); // Código ASCII da Letra W é  87, descontando 65 dará a pilha correta que devera ser movida a carta
            posOrigem = mover[0] - 87;
            pilhaOrigem = 'r';
        }
    }

    //Esta parte, resolve a pilha de destino
    if ((mover[1] >= 'A') && (mover[1] <= 'H')) {
        /*Significa que a pilha de destino é alguma das pilhas de cartas
         1º Verificar se a carta que está no topo permite a movimentação. Pela seguinte regra:
        A inserção de cartas nas pilhas A, ..., H deve respeitar a ordem
        decrescente e ainda duas cartas adjacentes não devem ter a mesma cor:
        preta (paus e espada) e vermelha (ouro e copas). Como exemplo, a
        seguinte ordem de cartas é aceita: Rei de paus (K), Dama de ouro (Q),
        Valete de espada (J), 10 de ouro, 9 de espada, 8 de copas. Assim a última
        carta colocada na pilha é 8 de copas. Se a pilha estiver vazia, qualquer
        carta é aceita;
         */
        //tmp[0] => naipe // tmp[1]=> carta
        if ((vazia(freecell->pCartas[tmp[0]])) || //verifica se pilha está vazia
                ((tmp[0] == '0' || tmp[0] == '2') && // Verifica se o naipe é de cor diferente
                (freecell->pCartas[mover[1] - 65]->prim->naipe == '1') || (freecell->pCartas[mover[1] - 65]->prim->naipe == '3')) ||
                ((tmp[0] == '1' || tmp[0] == '3')) &&
                (freecell->pCartas[mover[1] - 65]->prim->naipe == '0') || (freecell->pCartas[mover[1] - 65]->prim->naipe == '1') || // Fim da verificação da cor do naipe
                (tmp[1] < freecell->pCartas[mover[1] - 65]->prim->carta))//vefica se está em ordem decrescente
        {
            pushCarta(freecell->pCartas[mover[1] - 65], tmp[0], tmp[1]); // Código ASCII da Letra A é 65, descontando 65 dará a pilha correta que devera ser movida a carta
            return 1;
        } else { // Caso não seja possível colocar na pilha de destino. Devolve à pilha de origem.
            if (pilhaOrigem == 'c')
                pushCarta(freecell->pCartas[posOrigem], tmp[0], tmp[1]);
            else if (pilhaOrigem == 'n')
                pushCarta(freecell->pNaipe[posOrigem], tmp[0], tmp[1]);
            else if (pilhaOrigem == 'r')
                pushCarta(freecell->pReserva[posOrigem], tmp[0], tmp[1]);
            return 0;
        }
    }


    if ((mover[1] >= '0') && (mover[1] <= '3')) {
        /*Significa que a pilha de destino é uma das pilhas agrupadas pelo naipe e a regra para inserçao é:
         *  Em cada uma das pilhas 0, ..., 3 deve haver apenas cartas de mesmo
            naipe e em ordem crescente: por exemplo, na pilha 0, primeiro deve-se
            colocar um ás de copas, depois, sobre o ás de copas, deve-se colocar um
            2 de copas, e assim por diante;
         */
        //tmp[0] => naipe // tmp[1]=> carta
        if (vazia(freecell->pNaipe[mover[1] - 48]) && (tmp[1] == 'A')) {// se estiver vazia e a carta for um AS, insere
            pushCarta(freecell->pNaipe[mover[1] - 48], tmp[0], tmp[1]);
            return 1;
        } else
            if (!vazia(freecell->pNaipe[mover[1] - 48])) {//Quebrar esse if em vários para ver qual está causando o bug!
            printf("%c", freecell->pNaipe[mover[1] - 48]->prim->carta);
            if (tmp[1] == freecell->pNaipe[mover[1] - 48]->prim->carta - 1)
                if (tmp[0] == freecell->pNaipe[mover[1] - 48]->prim->naipe) { //se a pilha não estiver vazia e carta for maior que a do topo da pilha por 1 unidade e do memso naipe, insere
                    pushCarta(freecell->pNaipe[mover[1] - 48], tmp[0], tmp[1]);
                    return 1;
                }
        }
        if (pilhaOrigem == 'c')
            pushCarta(freecell->pCartas[posOrigem], tmp[0], tmp[1]);
        else if (pilhaOrigem == 'n')
            pushCarta(freecell->pNaipe[posOrigem], tmp[0], tmp[1]);
        else if (pilhaOrigem == 'r')
            pushCarta(freecell->pReserva[posOrigem], tmp[0], tmp[1]);
        return 0;
    }


    if ((mover[1] >= 'W') && (mover[1] <= 'Z')) { // Código ASCII da Letra W é  87, descontando 87 dará a pilha correta que devera ser movida a carta
        /*Esta parte significa que a pilha de destino é a reserva. Regra: 
        Cada espaço W, ..., Z pode armazenar no máximo uma carta;
         */
        if (vazia(freecell->pReserva[mover[1] - 87])) {
            pushCarta(freecell->pReserva[mover[1] - 87], tmp[0], tmp[1]);
            return 1;
        }
        if (pilhaOrigem == 'c')
            pushCarta(freecell->pCartas[posOrigem], tmp[0], tmp[1]);
        else if (pilhaOrigem == 'n')
            pushCarta(freecell->pNaipe[posOrigem], tmp[0], tmp[1]);
        else if (pilhaOrigem == 'r')
            pushCarta(freecell->pReserva[posOrigem], tmp[0], tmp[1]);
    }
}

/**
 * Imprime estado atual do jogo, o topo das pilhas de cartas.
 * @param freecell 
 */
void imprimePilhas(Freecell *freecell) {
    int i;
    for (i = 0; i < TAM_PILHAS_CARTAS; i++) {
        if (!vazia(freecell->pCartas[i])) { //verifica se a pilha está vazia
            printf("%c%c ", freecell->pCartas[i]->prim->naipe, freecell->pCartas[i]->prim->carta);
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

    while (!feof(arq)) {

        fscanf(arq, " %2[^\n]", comando);
        if (comando[0] == '*') {// Se o primeiro caractere do comando for  *  entao sera um comando de impressao do estado atual;
            imprimePilhas(freecell);
        } else { //caso contrario sera um comando de movimentaçao
            int r = moveCartaDaPilha(comando, freecell);
            if (r == -1) scanf("Sting de comando Invalida");

        }
    }
    fclose(arq);
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
    while (!feof(fp) && cont < 52) {
        fscanf(fp, " %2[^\n]", tmp); // lê até dois caracteres ou até um caractere de nova linha.
        pushCarta(freecell->pCartas[contPilha], tmp[0], tmp[1]);
        cont++;
        contPilha++;
        if (contPilha == 8) contPilha = 0;
        //  fscanf(fp, " %2[^\n]", tmp);
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
    freecell->pCartas = (TPilha**) malloc(TAM_PILHAS_CARTAS * sizeof (TPilha*));
    if (freecell->pCartas != NULL) {
        for (i = 0; i < TAM_PILHAS_CARTAS; i++) {
            freecell->pCartas[i] = criaPilhaDeCartas();
            printf("%p\n", &freecell->pCartas[i]); //Imprime na tela os endereços  dos ponteiros Cartas
        }
        printf("\n");
    } else {
        printf("Erro na alocação do vetor freecell->cartas");
        exit(10);
    }
    //Aloca espaço TAM_PILAS_NAIPE ponteiros de pilhas de naipe
    freecell->pNaipe = (TPilha**) malloc(TAM_PILHAS_NAIPE * sizeof (TPilha*));
    if (freecell->pNaipe != NULL) {
        for (i = 0; i < TAM_PILHAS_NAIPE; i++) {
            freecell->pNaipe[i] = criaPilhaDeCartas();
            printf("%p\n", &freecell->pNaipe[i]);
        }
        printf("\n");
    } else {
        printf("Erro na alocação do vetor freecell->naipe");
        exit(11);
    }
    //Aloca espaço TAM_PILAS_RESERVA ponteiros de pilhas de reserva
    freecell->pReserva = (TPilha**) malloc(TAM_PILHAS_RESERVA * sizeof (TPilha*));
    if (freecell->pReserva != NULL) {
        for (i = 0; i < TAM_PILHAS_RESERVA; i++) {
            freecell->pReserva[i] = criaPilhaDeCartas();
            printf("%p\n", &freecell->pReserva[i]);
        }
        printf("\n");
    } else {
        printf("Erro na alocação do vetor freecell->reserva");
        exit(12);
    }
    return freecell;
}