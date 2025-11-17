#include <stdio.h>
#include <string.h>
#include <stdbool.h> 


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

// --- Funções Auxiliares (Novas/Modificadas) ---

// 4. Buscar Item por Nome (Busca Sequencial)
void buscarItemPorNome() {
    if (totalItens == 0) {
        printf("\n⏳ A mochila está vazia. Nada para buscar.\n");
        return;
    }

    char nomeBuscar[50];
    bool encontrado = false; // Flag de controle

    printf("\n--- Buscar Item ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %49[^\n]", nomeBuscar);

    printf("\n🔎 Resultado da Busca Sequencial:\n");
    for (int i = 0; i < totalItens; i++) {
        // Conceito Adicionado: Comparação de strings (strcmp)
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("+--------------------------------------------------+\n");
            printf("| ✅ Item Encontrado! |\n");
            printf("+--------------------------------------------------+\n");
            printf("| Nome: %s\n", mochila[i].nome);
            printf("| Tipo: %s\n", mochila[i].tipo);
            printf("| Quantidade: %d\n", mochila[i].quantidade);
            printf("+--------------------------------------------------+\n");
            encontrado = true; // Define a flag como verdadeiro
            break; // Sai do loop após encontrar
        }
    }

    // Caso o item não seja encontrado após percorrer toda a lista
    if (!encontrado) {
        // Exibe mensagem de erro amigável
        printf("❌ Item '%s' não encontrado. Verifique a grafia.\n", nomeBuscar);
    }
}


void adicionarItem();
void listarItens();
void removerItem();


// --- Menu Principal (Modificado) ---
int main() {
    int escolha;

    do {
        printf("\n\n=== 🛡️ MOCHILA COM BUSCA - FREE FIRE ===\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. **Buscar Item por Nome**\n"); // Opção nova
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                // adicionarItem();
                break;
            case 2:
                // removerItem();
                break;
            case 3:
                // listarItens();
                break;
            case 4:
                buscarItemPorNome(); // Chamada para a nova funcionalidade
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