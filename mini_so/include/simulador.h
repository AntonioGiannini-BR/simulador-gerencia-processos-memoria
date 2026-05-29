#ifndef SIMULADOR_H
#define SIMULADOR_H

/*
 * simulador.h
 * ------------------------------------------------------------
 * Controla a execução geral do Mini-SO:
 * - leitura dos processos;
 * - admissão na memória;
 * - escalonamento Round-Robin;
 * - impressão do estado a cada unidade de tempo.
 */

#include "processo.h"
#include "fila.h"

#define QUANTUM 2

int carregar_processos(const char* nome_arquivo, PCB processos[], int limite);
int ler_processos_teclado(PCB processos[], int limite);
void executar_simulacao(PCB processos[], int quantidade);

#endif
