# 🖥️ Mini-SO - Simulador de Gerência de Processos e Memória

##  Projeto de Infraestrutura de Software

Este projeto consiste na implementação de um **Mini Sistema Operacional (Mini-SO)** desenvolvido em linguagem **C**, capaz de simular conceitos fundamentais de Sistemas Operacionais, incluindo gerenciamento de processos, escalonamento de CPU e gerenciamento de memória RAM.

O sistema realiza a leitura de uma lista de processos, simula sua execução utilizando o algoritmo **Round-Robin** e gerencia a memória utilizando o algoritmo **First-Fit**, exibindo passo a passo o estado interno do sistema.

---

#  Objetivo

O objetivo principal deste projeto é demonstrar, de forma prática, conceitos estudados na disciplina de Infraestrutura de Software, tais como:

* Process Control Block (PCB);
* Escalonamento de Processos;
* Algoritmo Round-Robin;
* Gerência de Memória;
* Alocação Contígua;
* Algoritmo First-Fit;
* Filas de Processos;
* Estados dos Processos;
* Simulação de CPU.

---

#  Conceitos Implementados

## PCB (Process Control Block)

Cada processo é representado por uma estrutura contendo:

* PID (Identificador do Processo)
* Tempo Total de Execução
* Tempo Restante
* Prioridade
* Tamanho da Memória Necessária
* Estado Atual
* Endereço Inicial na Memória

---

## Escalonamento Round-Robin

O escalonamento da CPU é realizado através do algoritmo Round-Robin.

### Funcionamento:

1. Cada processo recebe um Quantum fixo.
2. O processo executa até consumir o Quantum.
3. Caso termine sua execução, é encerrado.
4. Caso ainda possua tempo restante, retorna ao final da fila de prontos.
5. O próximo processo é escalonado.

### Exemplo

Quantum = 2

Processo P1 = 10 unidades

Execução:

P1 → 2s → volta para fila

P1 → 2s → volta para fila

P1 → 2s → volta para fila

...

---

## Gerência de Memória

A memória RAM é simulada através de um vetor de:

1024 bytes

Cada processo solicita uma quantidade específica de memória.

---

## Algoritmo First-Fit

O sistema utiliza o algoritmo First-Fit para encontrar espaço disponível na memória.

### Funcionamento:

1. Percorre a memória do início ao fim.
2. Procura o primeiro espaço livre suficiente.
3. Caso encontre:

   * Aloca o processo.
4. Caso não encontre:

   * Processo vai para a fila de espera.

---

#  Estrutura do Projeto

```text
mini_so/
│
├── include/
│   ├── fila.h
│   ├── memoria.h
│   ├── processo.h
│   └── simulador.h
│
├── src/
│   ├── fila.c
│   ├── main.c
│   ├── memoria.c
│   ├── processo.c
│   └── simulador.c
│
├── processos.txt
├── Makefile
├── README.md
└── mini_so.exe
```

---

# 📄 Arquivo de Entrada

O programa lê os processos a partir do arquivo:

```text
processos.txt
```

Formato:

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

Onde:

| Campo          | Descrição                  |
| -------------- | -------------------------- |
| PID            | Identificador do Processo  |
| TEMPO_EXECUCAO | Tempo total necessário     |
| MEMORIA        | Quantidade de RAM em bytes |
| PRIORIDADE     | Prioridade do processo     |

---

#  Estados dos Processos

Durante a simulação um processo pode assumir os seguintes estados:

| Estado     | Descrição           |
| ---------- | ------------------- |
| Novo       | Processo criado     |
| Pronto     | Aguardando CPU      |
| Executando | Utilizando CPU      |
| Esperando  | Aguardando memória  |
| Encerrado  | Processo finalizado |

---

# ⚙️ Como Compilar e Executar

## Método 1 - MSYS2 UCRT64

### Passo 1

Abrir:

```text
MSYS2 UCRT64
```

---

### Passo 2

Entrar na pasta do projeto:

```bash
cd "/c/Users/Antonio/OneDrive/Área de Trabalho/mini_so"
```

---

### Passo 3

Verificar GCC:

```bash
gcc --version
```

---

### Passo 4

Compilar:

```bash
gcc src/*.c -Iinclude -o mini_so
```

---

### Passo 5

Executar:

```bash
./mini_so
```

---

## Método 2 - Utilizando Makefile

Compilar:

```bash
make
```

Executar:

```bash
./mini_so
```

Limpar arquivos compilados:

```bash
make clean
```

---

#  Exemplo de Saída

```text
--------------------------------------------------
Tempo Atual: 04 s

CPU:
Executando PID 2

Tempo Restante:
2 segundos

Fila de Prontos:
[PID 3] -> [PID 1]

Fila de Espera:
Vazia

Mapa da RAM:
[P1:200B][P2:100B][Livre:724B]
--------------------------------------------------
```

---

#  Fluxo de Funcionamento

1. Leitura do arquivo processos.txt.
2. Criação dos PCBs.
3. Tentativa de alocação na memória.
4. Inserção na fila de prontos.
5. Escalonamento Round-Robin.
6. Atualização dos estados.
7. Liberação de memória ao finalizar.
8. Impressão do estado do sistema.
9. Encerramento da simulação.

---

#  Memória RAM

Capacidade total:

```text
1024 bytes
```

A memória é simulada por um vetor.

Exemplo:

```text
[P1][P1][P1][P2][P2][LIVRE][LIVRE]
```

Ao término de um processo:

```text
[P1][P1][LIVRE][LIVRE][P2][P2]
```

---

#  Caso de Teste

Arquivo:

```text
1 10 200 2
2 4 100 1
3 6 512 3
4 2 128 2
```

Executar:

```bash
gcc src/*.c -Iinclude -o mini_so
./mini_so
```

---

#  Possíveis Problemas

## gcc: command not found

Solução:

Abrir o terminal:

```text
MSYS2 UCRT64
```

Verificar:

```bash
gcc --version
```

---

## No such file or directory

Verificar o caminho:

```bash
pwd
```

Entrar na pasta correta:

```bash
cd "/c/Users/Antonio/OneDrive/Área de Trabalho/mini_so"
```

---

## processos.txt não encontrado

Certifique-se que a estrutura esteja:

```text
mini_so/
├── processos.txt
├── src/
├── include/
└── README.md
```

---

#  Aprendizados Obtidos

Este projeto permite compreender na prática:

* Estruturas de Dados
* Sistemas Operacionais
* Escalonamento de Processos
* Gerência de Memória
* Filas
* Modularização em C
* Organização de Projetos

---

#  Autores

Antonio Giannini
Cecilia Galindo 

Disciplina: Infraestrutura de Software

Professora: Monique Soares

---

#  Conclusão

O Mini-SO simula de forma simplificada o comportamento de um Sistema Operacional real, demonstrando como processos são escalonados, como a memória é gerenciada e como diferentes componentes do sistema trabalham em conjunto.

O projeto atende aos requisitos propostos para a disciplina, implementando conceitos fundamentais de Sistemas Operacionais de forma prática, modular e didática.
