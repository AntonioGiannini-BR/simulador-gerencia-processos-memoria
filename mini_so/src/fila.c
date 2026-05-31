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
 * Mostra a fila no formato pedido no PDF:
 * [PID 3] -> [PID 1] -> ...
 */
void imprimir_fila(const Fila* fila) {
    if (fila_vazia(fila)) {
        printf("[vazia]");
        return;
    }

    for (int i = 0; i < fila->tamanho; i++) {
        int indice = (fila->inicio + i) % MAX_PROCESSOS;
        printf("[PID %d]", fila->dados[indice]->pid);

        if (i < fila->tamanho - 1) {
            printf(" -> ");
        }
    }
}

/**
 * Exibe todos os processos presentes na fila.
 * Cada processo é mostrado pelo seu PID.
 * A função é utilizada para visualizar o estado atual
 * da fila de prontos ou da fila de espera durante a simulação.
 */
void imprimirFilaColorida(Fila *fila)
{
    // Verifica se a fila está vazia
    if (fila == NULL || fila->inicio == NULL)
    {
        printf(VERMELHO "Vazia\n" RESET);
        return;
    }

    // Ponteiro utilizado para percorrer a fila
    No *atual = fila->inicio;

    // Percorre todos os elementos da fila
    while (atual != NULL)
    {
        // Exibe o PID do processo atual
        printf(VERDE "[PID %d]" RESET, atual->processo->pid);

        // Exibe a seta entre os elementos da fila
        if (atual->proximo != NULL)
        {
            printf(AMARELO " -> " RESET);
        }

        // Avança para o próximo nó da fila
        atual = atual->proximo;
    }

    // Quebra de linha ao final da impressão
    printf("\n");
}
