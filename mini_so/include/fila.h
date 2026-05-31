#ifndef FILA_H
#define FILA_H

/*
 * fila.h
 * ------------------------------------------------------------
 * Implementa uma fila circular simples para armazenar ponteiros
 * para processos PCB.
 *
 * Ela será usada como:
 * - fila de prontos;
 * - fila de espera por memória.
 */

#include "processo.h"

#define MAX_PROCESSOS 100

/* Estrutura da fila circular. */
typedef struct {
    PCB* dados[MAX_PROCESSOS]; /* Vetor de ponteiros para processos. */
    int inicio;                /* Índice do primeiro elemento. */
    int fim;                   /* Próxima posição livre para inserir. */
    int tamanho;               /* Quantidade atual de elementos. */
} Fila;

void inicializar_fila(Fila* fila);
int fila_vazia(const Fila* fila);
int fila_cheia(const Fila* fila);
int enfileirar(Fila* fila, PCB* processo);
PCB* desenfileirar(Fila* fila);
void imprimir_fila(const Fila* fila);


#endif
