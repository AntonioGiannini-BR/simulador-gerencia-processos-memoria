#include <stdio.h>
#include "processo.h"

/*
 * Converte o estado numérico do enum para texto.
 * Isso deixa a saída do console mais clara na apresentação.
 */
const char* nome_estado(EstadoProcesso estado) {
    switch (estado) {
        case NOVO: return "Novo";
        case PRONTO: return "Pronto";
        case EXECUTANDO: return "Executando";
        case ESPERANDO: return "Esperando";
        case ENCERRADO: return "Encerrado";
        default: return "Desconhecido";
    }
}

/*
 * Imprime um PCB completo.
 * Esta função é útil para depuração e para explicar em sala
 * quais dados o sistema guarda sobre cada processo.
 */
void imprimir_processo(const PCB* processo) {
    if (processo == NULL) {
        return;
    }

    printf("PID %d | Burst: %d | Restante: %d | Memoria: %dB | Prioridade: %d | Estado: %s\n",
           processo->pid,
           processo->burst_total,
           processo->tempo_restante,
           processo->memoria,
           processo->prioridade,
           nome_estado(processo->estado));
}
