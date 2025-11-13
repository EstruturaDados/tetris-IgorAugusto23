#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5 // tamanho fixo da fila

// Estrutura que representa uma peça
typedef struct {
    char nome;  // tipo da peça ('I', 'O', 'T', 'L')
    int id;     // identificador único
} Peca;

// Estrutura da fila de peças
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// ---------- Funções de manipulação da fila ----------

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4]; // escolhe aleatoriamente o tipo
    nova.id = id;
    return nova;
}

// Insere uma nova peça no final da fila (enqueue)
void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n  A fila está cheia! Não é possível adicionar mais peças.\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->pecas[f->tras] = p;
    f->tamanho++;
}

// Remove a peça da frente da fila (dequeue)
void desenfileirar(Fila *f) {
    if (filaVazia(f)) {
        printf("\n  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    printf("\n Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila de peças vazia!\n");
        return;
    }

    printf("\nFila de peças:\n");
    int i, indice;
    for (i = 0; i < f->tamanho; i++) {
        indice = (f->frente + i) % TAM_FILA;
        printf("[%c %d] ", f->pecas[indice].nome, f->pecas[indice].id);
    }
    printf("\n");
}

// ---------- Função principal ----------
int main() {
    Fila fila;
    int opcao, contador = 0;

    srand(time(NULL));
    inicializarFila(&fila);

    // Inicializa com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(contador++));
    }

    do {
        exibirFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar(&fila);
                break;
            case 2:
                enfileirar(&fila, gerarPeca(contador++));
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\n  Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
