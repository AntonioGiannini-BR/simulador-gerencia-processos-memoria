#ifndef MEMORIA_H
#define MEMORIA_H

/*
 * memoria.h
 * ------------------------------------------------------------
 * Responsável pela gerência da RAM simulada.
 * O projeto pede um array de 1024 posições representando 1KB.
 */

#include "processo.h"

#define TAM_RAM 1024

void inicializar_memoria(int ram[]);
int alocar_first_fit(int ram[], PCB* processo);
void desalocar_memoria(int ram[], int pid);
void imprimir_mapa_memoria(int ram[]);
void salvar_log_memoria_final(int ram[], const char* nome_arquivo);

#endif
