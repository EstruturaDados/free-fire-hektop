#include <stdio.h>
#include <string.h>

// Definindo a estrutura para representar um item na mochila
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
} Item;

// Tamanho máximo do inventário
#define CAPACIDADE_MAXIMA 10

// Variáveis globais para o inventário
Item mochila[CAPACIDADE_MAXIMA];
int totalItens = 0;

// --- Funções Auxiliares ---

// 1. Adicionar Item
void adicionarItem() {
    if (totalItens >= CAPACIDADE_MAXIMA) {
        printf("\n🚫 A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    scanf(" %49[^\n]", mochila[totalItens].nome); // Leitura de string com espaço
    printf("Tipo do item (Ex: Consumível, Arma, Proteção): ");
    scanf(" %49[^\n]", mochila[totalItens].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;
    printf("\n✅ Item adicionado com sucesso!\n");
}

// 2. Listar Itens
void listarItens() {
    if (totalItens == 0) {
        printf("\n⏳ A mochila está vazia.\n");
        return;
    }

    printf("\n--- Inventário Atual (%d/%d) ---\n", totalItens, CAPACIDADE_MAXIMA);
    printf("+--------------------------------------------------+\n");
    printf("| %-20s | %-15s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("+----------------------+-----------------+------------+\n");

    for (int i = 0; i < totalItens; i++) {
        printf("| %-20s | %-15s | %-10d |\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("+----------------------+-----------------+------------+\n");
}

// 3. Remover Item
void removerItem() {
    if (totalItens == 0) {
        printf("\n⏳ A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeRemover[50];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item que deseja remover: ");
    scanf(" %49[^\n]", nomeRemover);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        // Busca simples (sem strcmp, conforme a simplicidade do nível novato)
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Item encontrado. Move os itens seguintes uma posição para trás
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            encontrado = 1;
            printf("\n🗑️ Item '%s' removido com sucesso!\n", nomeRemover);
            break; // Sai do loop após a remoção
        }
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeRemover);
    }
}

// --- Menu Principal ---
int main() {
    int escolha;

    do {
        printf("\n\n=== 🎮 INVENTÁRIO BÁSICO - FREE FIRE ===\n");
        printf("1. Adicionar Item à Mochila\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Listar Itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("\n👋 Sobrevivência concluída. Fechando inventário.\n");
                break;
            default:
                printf("\n⚠️ Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}