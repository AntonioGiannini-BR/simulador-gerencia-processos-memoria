#include <stdio.h>
#include "memoria.h"

/*
 * Preenche toda a RAM com zero.
 * Zero significa posição livre.
 * Um número diferente de zero representa o PID ocupando aquele byte.
 */
void inicializar_memoria(int ram[]) {
    for (int i = 0; i < TAM_RAM; i++) {
        ram[i] = 0;
    }
}

/*
 * Alocação First-Fit.
 * Procura o primeiro bloco livre contíguo com tamanho suficiente
 * para armazenar o processo.
 *
 * Retorna:
 * 1 -> conseguiu alocar;
 * 0 -> não encontrou espaço contíguo suficiente.
 */
int alocar_first_fit(int ram[], PCB* processo) {
    int livres = 0;
    int inicio = -1;

    for (int i = 0; i < TAM_RAM; i++) {
        if (ram[i] == 0) {
            if (livres == 0) {
                inicio = i;
            }

            livres++;

            if (livres == processo->memoria) {
                for (int j = inicio; j < inicio + processo->memoria; j++) {
                    ram[j] = processo->pid;
                }

                processo->inicio_memoria = inicio;
                return 1;
            }
        } else {
            livres = 0;
            inicio = -1;
        }
    }

    return 0;
}

/*
 * Libera todas as posições da RAM ocupadas pelo PID informado.
 * Essa função é chamada quando o processo termina.
 */
void desalocar_memoria(int ram[], int pid) {
    for (int i = 0; i < TAM_RAM; i++) {
        if (ram[i] == pid) {
            ram[i] = 0;
        }
    }
}

/*
 * Imprime um mapa visual compactado da RAM.
 * Em vez de mostrar 1024 posições uma por uma, agrupa blocos contíguos.
 */
void imprimir_mapa_memoria(int ram[]) {
    int i = 0;

    while (i < TAM_RAM) {
        int valor = ram[i];
        int inicio = i;

        while (i < TAM_RAM && ram[i] == valor) {
            i++;
        }

        int tamanho = i - inicio;

        if (valor == 0) {
            printf("[Livre: %dB]", tamanho);
        } else {
            printf("[P%d: %dB]", valor, tamanho);
        }
    }
}

/*
 * Salva o estado final da RAM em um arquivo .txt.
 * Esta implementação atende à Opção B do Módulo 3 do PDF: Arquivos/log.
 */
void salvar_log_memoria_final(int ram[], const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("Nao foi possivel criar o log final da memoria.\n");
        return;
    }

    fprintf(arquivo, "LOG FINAL DA MEMORIA RAM SIMULADA\n");
    fprintf(arquivo, "Tamanho total: %d bytes\n\n", TAM_RAM);

    int i = 0;
    while (i < TAM_RAM) {
        int valor = ram[i];
        int inicio = i;

        while (i < TAM_RAM && ram[i] == valor) {
            i++;
        }

        int tamanho = i - inicio;

        if (valor == 0) {
            fprintf(arquivo, "Livre: inicio=%d, tamanho=%dB\n", inicio, tamanho);
        } else {
            fprintf(arquivo, "PID %d: inicio=%d, tamanho=%dB\n", valor, inicio, tamanho);
        }
    }

    fclose(arquivo);
}
