#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { VERMELHO, PRETO } Cor;

typedef struct No {
    int dado; // Agora representa o SCORE (Pontuação) do jogador
    char nome[50]; // Nome do jogador
    Cor cor;
    struct No *esquerdo, *direito, *pai;
} No;

// Ponteiro global
No* raiz = NULL;

// --- FUNÇÕES AUXILIARES DE ROTAÇÃO ---
void rotacionarEsquerda(No *X) {
    No *Y = X->direito;
    X->direito = Y->esquerdo;
    
    if (Y->esquerdo != NULL)
        Y->esquerdo->pai = X;
        
    Y->pai = X->pai;
    
    if (X->pai == NULL)
        raiz = Y;
    else if (X == X->pai->esquerdo)
        X->pai->esquerdo = Y;
    else
        X->pai->direito = Y;
        
    Y->esquerdo = X;
    X->pai = Y;
}

void rotacionarDireita(No *Y) {
    No *X = Y->esquerdo;
    Y->esquerdo = X->direito;
    
    if (X->direito != NULL)
        X->direito->pai = Y;
        
    X->pai = Y->pai;
    
    if (Y->pai == NULL)
        raiz = X;
    else if (Y == Y->pai->esquerdo)
        Y->pai->esquerdo = X;
    else
        Y->pai->direito = X;
        
    X->direito = Y;
    Y->pai = X;
}

// --- BALANCEAMENTO DA INSERÇÃO (5 CASOS) ---
void repararInsercao(No *N) {
    if (N->pai == NULL) {
        N->cor = PRETO;
        return;
    }

    if (N->pai->cor == PRETO) {
        return;
    }

    No *P = N->pai;
    No *GG = P->pai;
    No *U = (P == GG->esquerdo) ? GG->direito : GG->esquerdo;

    if (U != NULL && U->cor == VERMELHO) {
        P->cor = PRETO;
        U->cor = PRETO;
        GG->cor = VERMELHO;
        repararInsercao(GG);
        return;
    }
    
    if (P == GG->esquerdo) {
        if (N == P->direito) {
            rotacionarEsquerda(P);
            N = P; 
            P = N->pai;
        }
        P->cor = PRETO;
        GG->cor = VERMELHO;
        rotacionarDireita(GG);
    } 
    else {
        if (N == P->esquerdo) {
            rotacionarDireita(P);
            N = P;
            P = N->pai;
        }
        P->cor = PRETO;
        GG->cor = VERMELHO;
        rotacionarEsquerda(GG);
    }
}

// --- INSERÇÃO MODIFICADA PARA RECEBER NOME ---
No* criarNo(int dado, const char* nome) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dado = dado;
    strcpy(novo->nome, nome); // Copia o nome informado para o nó
    novo->cor = VERMELHO;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->pai = NULL;
    return novo;
}

void inserir(int dado, const char* nome) {
    No *novo = criarNo(dado, nome);
    
    if (raiz == NULL) {
        raiz = novo;
        repararInsercao(novo);
        return;
    }

    No *atual = raiz;
    No *paiAux = NULL;

    while (atual != NULL) {
        paiAux = atual;
        // A ordenação da árvore é baseada na pontuação (dado)
        if (novo->dado < atual->dado)
            atual = atual->esquerdo;
        else
            atual = atual->direito;
    }

    novo->pai = paiAux;

    if (novo->dado < paiAux->dado)
        paiAux->esquerdo = novo;
    else
        paiAux->direito = novo;

    repararInsercao(novo);
}

// --- EXIBIÇÃO EM-ORDEM (RANKING DA MENOR PONTUAÇÃO PARA A MAIOR) ---
void exibirRanking(No *raizAtual) {
    if (raizAtual == NULL) return;
    
    exibirRanking(raizAtual->esquerdo);
    printf("[%s] %s: %d pts\n", 
            (raizAtual->cor == VERMELHO) ? "V" : "P", 
            raizAtual->nome, 
            raizAtual->dado);
    exibirRanking(raizAtual->direito);
}

// --- FUNÇÃO PARA VISUALIZAR A ESTRUTURA DA ÁRVORE BALANCEADA ---
// Imprime a árvore deitada. Quanto mais para a direita na tela, mais profundo o nó está.
void exibirEstruturaArvore(No *raizAtual, int espaco) {
    if (raizAtual == NULL) return;

    // Aumenta a distância entre os níveis
    espaco += 8;

    // Exibe o lado direito primeiro
    exibirEstruturaArvore(raizAtual->direito, espaco);

    // Imprime o nó atual após os espaços necessários
    printf("\n");
    for (int i = 8; i < espaco; i++) {
        printf(" ");
    }
    
    // Imprime o nome, score e a cor do nó correspondente
    printf("%s(%d)[%s]\n", raizAtual->nome, raizAtual->dado, (raizAtual->cor == VERMELHO) ? "V" : "P");

    // Exibe o lado esquerdo
    exibirEstruturaArvore(raizAtual->esquerdo, espaco);
}

// --- MENU INTERATIVO ---
int main() {
    int opcao;
    int pontos;
    char nomeJogador[50];

    // Alguns dados iniciais para a árvore não começar vazia
    inserir(40, "Alice");
    inserir(20, "Bob");
    inserir(60, "Carlos");

    do {
        printf("\n======= SISTEMA DE PLACAR (RUBRO-NEGRA) =======\n");
        printf("1. Adicionar Novo Jogador\n");
        printf("2. Ver Ranking Geral (Em-Ordem)\n");
        printf("3. Visualizar Estrutura da Arvore (Balanceamento)\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                printf("\nDigite o nome do jogador: ");
                fgets(nomeJogador, 50, stdin);
                nomeJogador[strcspn(nomeJogador, "\n")] = 0; // Remove a quebra de linha do fgets

                printf("Digite a pontuacao: ");
                scanf("%d", &pontos);
                
                inserir(pontos, nomeJogador);
                printf("Jogador inserido e arvore rebalanceada!\n");
                break;

            case 2:
                printf("\n--- RANKING DE PONTUACAO ---\n");
                exibirRanking(raiz);
                printf("----------------------------\n");
                break;

            case 3:
                printf("\n--- ESTRUTURA ATUAL DA ARVORE (Gire a cabeca para a esquerda para ver o topo) ---\n");
                exibirEstruturaArvore(raiz, 0);
                printf("\n--------------------------------------------------------------------------------\n");
                break;

            case 4:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 4);

    return 0;
}