# Mini-SO — Simulador de Gerência de Processos e Memória

Projeto de Infraestrutura de Software — 2º GQ.

## O que o projeto faz

Este programa em C simula um pequeno Sistema Operacional, com:

- PCB para cada processo;
- escalonamento Round-Robin;
- quantum fixo de 2 segundos;
- RAM simulada com 1024 bytes;
- alocação contígua First-Fit;
- fila de prontos;
- fila de espera por memória;
- liberação de memória ao finalizar processos;
- impressão do estado a cada unidade de tempo;
- geração de log final da memória.

## Organização das pastas

```text
mini_so_organizado/
├── include/              # Arquivos .h com structs, constantes e protótipos
├── src/                  # Arquivos .c com a implementação do projeto
├── data/                 # Arquivo processos.txt usado como entrada
├── logs/                 # Log final gerado após executar a simulação
├── build/                # Executável gerado pela compilação
├── docs/                 # Roteiro de apresentação e explicação
├── Makefile              # Facilita compilação e execução
└── README.md             # Explicação do projeto
```

## Formato do arquivo de entrada

O arquivo `data/processos.txt` deve conter uma linha por processo:

```text
PID TEMPO_EXECUCAO MEMORIA PRIORIDADE
```

Exemplo:

```text
1 10 200 2
2 4 100 1
3 6 512 3
4 2 128 2
```

## Como compilar e executar

### Opção 1 — usando Makefile

```bash
make
make run
```

### Opção 2 — compilando manualmente

```bash
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/processo.c src/fila.c src/memoria.c src/simulador.c -o build/mini_so
./build/mini_so
```

## Observação

O log final será salvo em:

```text
logs/log_memoria_final.txt
```
