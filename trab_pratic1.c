
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo os limites
#define TAMANHO_PALAVRA 60
#define TAMANHO_LINHA 500
#define TAMANHO_DICIONARIO 500


// Criando o Nó
typedef struct No {
    int linha;
    int frequencia;
    struct No* prox;
} No;

typedef struct Palavra {
    char palavra[TAMANHO_PALAVRA];
    No* lista;
} Palavra;

Palavra dicionario[TAMANHO_DICIONARIO];
int n_palavras_dicionario = 0;

// Essa função cria um novo Nó
No* criarNo (int linha) {
    No* novo = (No*) malloc(sizeof(No));
    novo -> linha = linha;
    novo -> frequencia = 1;
    novo -> prox = NULL;
    return novo;
}

// Função para encontrar uma palavra no dicionario
int encontrarPalavra (const char* palavra) {
    for (int i = 0; i < n_palavras_dicionario; i++) {
        if (strcmp(dicionario[i].palavra, palavra) == 0) {
            return i; // Retorna o indice no dicionário
        }
    }
    return -1; // Retorna quando a palavra não é encontrada
}

// Função para adicionar ou atualizar uma palavra no dicionario
void adicionarPalavra(const char* palavra, int linha) {
    int indice = encontrarPalavra(palavra);
    if (indice == -1) { 
        // Adiciona uma nova palavra no dicionario
        strcpy(dicionario[n_palavras_dicionario].palavra, palavra);
        dicionario[n_palavras_dicionario].lista = criarNo(linha);
        n_palavras_dicionario++ ;
    }else {
        // Atualiza a lista encadeada
        No* atual = dicionario[indice].lista;
        while (atual != NULL) {
            if (atual -> linha == linha) {
                atual -> frequencia++ ;
                return;
            }
            if (atual -> prox == NULL) break;
            atual = atual -> prox;
        }
        atual -> prox = criarNo(linha);
    }
}

// Função apara exibir o dicionario invertido
void exibirIndiceInvertido() {
    for (int i = 0; i < n_palavras_dicionario; i++) {
        printf("%s: ", dicionario[i].palavra);
        No* atual = dicionario[i].lista;
        while (atual != NULL) {
            printf("(%d, %d)", atual -> linha, atual -> frequencia);
            if (atual -> prox != NULL) printf(", ");
            atual = atual -> prox;
        }
        printf("\n");
    }
}

int main() {
    char linha[TAMANHO_LINHA];
    char delimitadores[] = " ,.-\n";

    FILE* file  = fopen("pratica.txt", "r");
    if (file == NULL) {
        printf("Arquivo nao encontrado.\n");
        return 1;
    }

    int numero_linha = 1;

    while (fgets(linha, sizeof linha, file) != NULL) {
        char* palavra = strtok(linha, delimitadores);
        while (palavra != NULL) {
            adicionarPalavra(palavra, numero_linha);
            palavra = strtok(NULL, delimitadores);
        }
        numero_linha++ ;
    }

    fclose(file);

    printf("Indice Invertido:\n");
    exibirIndiceInvertido();
   

    system ("pause");
    return 0;
}