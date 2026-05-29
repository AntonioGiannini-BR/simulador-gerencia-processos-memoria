#ifndef PROCESSO_H
#define PROCESSO_H

/*
 * processo.h
 * ------------------------------------------------------------
 * Este arquivo define a estrutura PCB (Process Control Block),
 * que representa cada processo dentro do simulador Mini-SO.
 *
 * A professora pediu que cada processo tivesse:
 * - PID;
 * - tempo total de execução;
 * - prioridade;
 * - tamanho em memória;
 * - estado.
 */

/* Estados possíveis de um processo durante a simulação. */
typedef enum {
    NOVO,        /* Processo acabou de ser criado/carregado. */
    PRONTO,      /* Processo está na fila de prontos aguardando CPU. */
    EXECUTANDO,  /* Processo está usando a CPU. */
    ESPERANDO,   /* Processo está aguardando espaço na memória RAM. */
    ENCERRADO    /* Processo terminou sua execução. */
} EstadoProcesso;

/*
 * PCB - Process Control Block
 * Guarda todas as informações necessárias para o sistema operacional
 * simulado controlar um processo.
 */
typedef struct {
    int pid;              /* Identificador único do processo. */
    int burst_total;      /* Tempo total de execução solicitado. */
    int tempo_restante;   /* Tempo que ainda falta para terminar. */
    int prioridade;       /* Prioridade lida do arquivo. */
    int memoria;          /* Quantidade de bytes solicitada na RAM. */
    int inicio_memoria;   /* Posição inicial onde o processo foi alocado. */
    EstadoProcesso estado;/* Estado atual do processo. */
} PCB;

/* Retorna o nome textual de um estado. */
const char* nome_estado(EstadoProcesso estado);

/* Imprime as informações de um processo. */
void imprimir_processo(const PCB* processo);

#endif
