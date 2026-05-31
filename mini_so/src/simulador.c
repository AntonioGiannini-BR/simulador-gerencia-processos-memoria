#include <stdio.h>
#include "simulador.h"
#include "fila.h"
#include "memoria.h"
#include "cores.h"

/*
 * Tenta mover processos da fila de espera para a fila de prontos.
 * Isso acontece sempre que algum processo termina e libera memória.
 */
static void tentar_admitir_processos(Fila* espera, Fila* prontos, int ram[]) {
    int tentativas = espera->tamanho;

    for (int i = 0; i < tentativas; i++) {
        PCB* processo = desenfileirar(espera);

        if (processo == NULL) {
            return;
        }

        if (alocar_first_fit(ram, processo)) {
            processo->estado = PRONTO;
            enfileirar(prontos, processo);
            printf("Admissao: PID %d alocado na RAM pelo First-Fit.\n", processo->pid);
        } else {
            processo->estado = ESPERANDO;
            enfileirar(espera, processo);
        }
    }
}

/*
 * Imprime o estado do Mini-SO a cada unidade de tempo.
 * Esta saída segue a sugestão do PDF: tempo, CPU, fila e mapa da RAM.
 */
void imprimirStatus(int tempoAtual, Processo *cpu, Fila *filaProntos, Fila *filaEspera) {
    printf(CIANO NEGRITO "\n==================================================\n" RESET);
    printf(FUNDO_AZUL BRANCO NEGRITO "           MINI-SO - STATUS DO SISTEMA           " RESET "\n");
    printf(CIANO NEGRITO "==================================================\n" RESET);

    printf(AMARELO NEGRITO "Tempo Atual: " RESET "%d s\n\n", tempoAtual);

    printf(AZUL NEGRITO "CPU: " RESET);

    if (cpu != NULL) {
        printf(VERDE "Executando PID %d " RESET, cpu->pid);
        printf("(Restam %d s)\n", cpu->tempoRestante);
    } else {
        printf(VERMELHO "Livre\n" RESET);
    }

    printf("\n" MAGENTA NEGRITO "Fila de Prontos: " RESET);

    if (filaVazia(filaProntos)) {
        printf(VERMELHO "Vazia\n" RESET);
    } else {
        imprimirFilaColorida(filaProntos);
    }

    printf(MAGENTA NEGRITO "Fila de Espera: " RESET);

    if (filaVazia(filaEspera)) {
        printf(VERMELHO "Vazia\n" RESET);
    } else {
        imprimirFilaColorida(filaEspera);
    }

    printf("\n" CIANO NEGRITO "Mapa da RAM:\n" RESET);
    imprimirMemoriaColorida();

    printf(CIANO NEGRITO "==================================================\n" RESET);
}

/*
 * Lê o arquivo de processos.
 * Cada linha deve seguir o modelo do PDF:
 * PID | Tempo de Execução | Espaço em RAM | Prioridade
 */
int carregar_processos(const char* nome_arquivo, PCB processos[], int limite) {
    FILE* arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        return -1;
    }

    int qtd = 0;

    while (qtd < limite &&
           fscanf(arquivo, "%d %d %d %d",
                  &processos[qtd].pid,
                  &processos[qtd].burst_total,
                  &processos[qtd].memoria,
                  &processos[qtd].prioridade) == 4) {

        processos[qtd].tempo_restante = processos[qtd].burst_total;
        processos[qtd].inicio_memoria = -1;
        processos[qtd].estado = NOVO;
        qtd++;
    }

    fclose(arquivo);
    return qtd;
}

/*
 * Entrada alternativa por teclado.
 * O PDF permite usar arquivo processos.txt ou receber os dados pelo teclado.
 */
int ler_processos_teclado(PCB processos[], int limite) {
    int qtd;

    printf("Arquivo de processos nao encontrado.\n");
    printf("Digite a quantidade de processos: ");
    scanf("%d", &qtd);

    if (qtd > limite) {
        qtd = limite;
    }

    for (int i = 0; i < qtd; i++) {
        printf("\nProcesso %d\n", i + 1);
        printf("PID: ");
        scanf("%d", &processos[i].pid);

        printf("Tempo de execucao: ");
        scanf("%d", &processos[i].burst_total);

        printf("Memoria em bytes: ");
        scanf("%d", &processos[i].memoria);

        printf("Prioridade: ");
        scanf("%d", &processos[i].prioridade);

        processos[i].tempo_restante = processos[i].burst_total;
        processos[i].inicio_memoria = -1;
        processos[i].estado = NOVO;
    }

    return qtd;
}

/*
 * Executa a simulação completa.
 * Fluxo principal:
 * 1. inicializa RAM e filas;
 * 2. tenta admitir processos na memória usando First-Fit;
 * 3. executa a CPU com Round-Robin;
 * 4. libera memória ao finalizar;
 * 5. salva log final.
 */
void executar_simulacao(PCB processos[], int quantidade) {
    int ram[TAM_RAM];
    Fila prontos;
    Fila espera;
    int finalizados = 0;
    int tempo = 0;

    inicializar_memoria(ram);
    inicializar_fila(&prontos);
    inicializar_fila(&espera);

    printf("\n===== MINI-SO: SIMULADOR DE PROCESSOS E MEMORIA =====\n");
    printf("Quantum definido: %d segundos\n", QUANTUM);
    printf("RAM simulada: %d bytes\n\n", TAM_RAM);

    /* Admissão inicial dos processos. */
    for (int i = 0; i < quantidade; i++) {
        if (processos[i].memoria > TAM_RAM) {
            processos[i].estado = ENCERRADO;
            finalizados++;
            printf("PID %d encerrado: memoria solicitada maior que a RAM.\n", processos[i].pid);
        } else if (alocar_first_fit(ram, &processos[i])) {
            processos[i].estado = PRONTO;
            enfileirar(&prontos, &processos[i]);
            printf("PID %d entrou na fila de prontos.\n", processos[i].pid);
        } else {
            processos[i].estado = ESPERANDO;
            enfileirar(&espera, &processos[i]);
            printf("PID %d ficou aguardando memoria.\n", processos[i].pid);
        }
    }

    /* Laço principal: termina quando todos os processos forem encerrados. */
    while (finalizados < quantidade) {
        PCB* cpu = desenfileirar(&prontos);

        if (cpu == NULL) {
            tempo++;
            tentar_admitir_processos(&espera, &prontos, ram);
            imprimir_status(tempo, NULL, &prontos, &espera, ram);
            continue;
        }

        cpu->estado = EXECUTANDO;

        /* Executa no máximo o tempo do quantum. */
        int tempo_executado = 0;
        while (tempo_executado < QUANTUM && cpu->tempo_restante > 0) {
            tempo++;
            cpu->tempo_restante--;
            tempo_executado++;
            imprimir_status(tempo, cpu, &prontos, &espera, ram);
        }

        if (cpu->tempo_restante == 0) {
            cpu->estado = ENCERRADO;
            desalocar_memoria(ram, cpu->pid);
            finalizados++;
            printf("Saida: PID %d finalizado e memoria liberada.\n\n", cpu->pid);
            tentar_admitir_processos(&espera, &prontos, ram);
        } else {
            cpu->estado = PRONTO;
            enfileirar(&prontos, cpu);
            printf("Troca de contexto: PID %d voltou para o final da fila.\n\n", cpu->pid);
        }
    }

    printf("===== SIMULACAO FINALIZADA =====\n");
    salvar_log_memoria_final(ram, "logs/log_memoria_final.txt");
}
