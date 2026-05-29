#include <stdio.h>
#include "simulador.h"

/*
 * main.c
 * ------------------------------------------------------------
 * Ponto de entrada do programa.
 * Primeiro tenta ler data/processos.txt.
 * Se não encontrar, tenta processos.txt na pasta principal.
 * Se ainda assim não encontrar, permite digitação pelo teclado.
 */
int main(void) {
    PCB processos[MAX_PROCESSOS];

    int quantidade = carregar_processos("data/processos.txt", processos, MAX_PROCESSOS);

    if (quantidade == -1) {
        quantidade = carregar_processos("processos.txt", processos, MAX_PROCESSOS);
    }

    if (quantidade == -1) {
        quantidade = ler_processos_teclado(processos, MAX_PROCESSOS);
    }

    if (quantidade <= 0) {
        printf("Nenhum processo foi carregado.\n");
        return 1;
    }

    executar_simulacao(processos, quantidade);
    return 0;
}
