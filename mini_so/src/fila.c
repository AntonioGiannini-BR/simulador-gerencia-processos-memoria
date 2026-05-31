#include <stdio.h>
#include "fila.h"
#include "cores.h"

/*
 * Inicializa a fila vazia.
 * inicio e fim começam em zero, e tamanho indica que não há elementos.
 */
void inicializar_fila(Fila* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
}

/* Retorna 1 se a fila não tiver processos. */
int fila_vazia(const Fila* fila) {
    return fila->tamanho == 0;
}

/* Retorna 1 se a fila chegou ao limite máximo. */
int fila_cheia(const Fila* fila) {
    return fila->tamanho == MAX_PROCESSOS;
}

/*
 * Insere um processo no final da fila.
 * O operador % permite que a fila seja circular.
 */
int enfileirar(Fila* fila, PCB* processo) {
    if (fila_cheia(fila)) {
        return 0;
    }

    fila->dados[fila->fim] = processo;
    fila->fim = (fila->fim + 1) % MAX_PROCESSOS;
    fila->tamanho++;
    return 1;
}

/*
 * Remove e retorna o primeiro processo da fila.
 * Se a fila estiver vazia, retorna NULL.
 */
PCB* desenfileirar(Fila* fila) {
    if (fila_vazia(fila)) {
        return NULL;
    }

    PCB* processo = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_PROCESSOS;
    fila->tamanho--;
    return processo;
}

/*
 * Mostra a fila no terminal com cores.
 * A estrutura original da fila foi mantida:
 * ela continua sendo uma fila circular baseada no vetor dados[],
 * usando os índices inicio, fim e tamanho.
 */
void imprimir_fila(const Fila* fila) {
    if (fila == NULL || fila_vazia(fila)) {
        printf(VERMELHO "[vazia]" RESET);
        return;
    }

    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->inicio + i) % MAX_PROCESSOS;

        printf(VERDE "[PID %d]" RESET, fila->dados[indice]->pid);

        if (i < fila->tamanho - 1) {
            printf(AMARELO " -> " RESET);
        }
    }
}

