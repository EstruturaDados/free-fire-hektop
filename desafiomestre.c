#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 💡 Conceito Adicionado: Enumeração para os critérios de ordenação
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// Definindo a estrutura (com Prioridade)
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade; // Novo campo (1 a 5)
} Item;

#define CAPACIDADE_MAXIMA 10
Item mochila[CAPACIDADE_MAXIMA];
int totalItens = 0;
bool isOrdenadaPorNome = false; // Controle de estado para a busca binária

// --- Funções Auxiliares (Novas/Modificadas) ---

// 1. Adicionar Item (Modificado para incluir prioridade)
void adicionarItem() {
    if (totalItens >= CAPACIDADE_MAXIMA) {
        printf("\n🚫 A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    scanf(" %49[^\n]", mochila[totalItens].nome);
    printf("Tipo do item: ");
    scanf(" %49[^\n]", mochila[totalItens].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    
    // Novo: Prioridade
    do {
        printf("Prioridade (1=Baixa a 5=Alta): ");
        scanf("%d", &mochila[totalItens].prioridade);
        if (mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5) {
            printf("⚠️ Prioridade deve ser um valor entre 1 e 5.\n");
        }
    } while (mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5);

    totalItens++;
    isOrdenadaPorNome = false; // Qualquer adição desordena a lista por nome
    printf("\n✅ Item adicionado com sucesso!\n");
}

// 2. Listar Itens (Modificado para incluir prioridade)
void listarItens() {
    // ... (o mesmo código do Novato, mas com uma coluna extra para Prioridade)
    if (totalItens == 0) {
        printf("\n⏳ A mochila está vazia.\n");
        return;
    }

    printf("\n--- Inventário Atual (%d/%d) ---\n", totalItens, CAPACIDADE_MAXIMA);
    printf("+--------------------------------------------------------------------+\n");
    printf("| %-20s | %-15s | %-10s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("+----------------------+-----------------+------------+------------+\n");

    for (int i = 0; i < totalItens; i++) {
        printf("| %-20s | %-15s | %-10d | %-10d |\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
    printf("+----------------------+-----------------+------------+------------+\n");
}

// 5. Ordenação (Insertion Sort)
long long ordenarMochila(CriterioOrdenacao criterio) {
    long long comparacoes = 0;
    Item chave;
    int j;
    
    for (int i = 1; i < totalItens; i++) {
        chave = mochila[i];
        j = i - 1;

        // Comparações baseadas no critério escolhido
        while (j >= 0) {
            comparacoes++; // Contador de comparações
            bool trocaNecessaria = false;

            if (criterio == ORDENAR_NOME) {
                if (strcmp(mochila[j].nome, chave.nome) > 0) {
                    trocaNecessaria = true;
                }
            } else if (criterio == ORDENAR_TIPO) {
                if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                    trocaNecessaria = true;
                }
            } else if (criterio == ORDENAR_PRIORIDADE) {
                // Ordena Prioridade de forma decrescente (maior prioridade primeiro)
                if (mochila[j].prioridade < chave.prioridade) {
                    trocaNecessaria = true;
                }
            }

            if (trocaNecessaria) {
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
    
    // Atualiza o estado para busca binária
    isOrdenadaPorNome = (criterio == ORDENAR_NOME);
    return comparacoes;
}

// 6. Busca Binária por Nome
void buscaBinariaPorNome() {
    if (!isOrdenadaPorNome) {
        printf("\n❌ Erro: A busca binária requer que a mochila esteja ordenada por **Nome**.\n");
        printf("Por favor, ordene a mochila por nome (Opção 5) antes de buscar.\n");
        return;
    }
    
    char nomeBuscar[50];
    printf("\n--- Busca Binária por Nome ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %49[^\n]", nomeBuscar);

    int esquerda = 0;
    int direita = totalItens - 1;
    bool encontrado = false;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBuscar);

        if (comparacao == 0) {
            // Item encontrado
            printf("\n🔎 Item Encontrado (Busca Binária):\n");
            printf("| Nome: %s\n", mochila[meio].nome);
            printf("| Tipo: %s\n", mochila[meio].tipo);
            printf("| Quantidade: %d\n", mochila[meio].quantidade);
            printf("| Prioridade: %d\n", mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (comparacao < 0) {
            // Nome procurado está à direita (maior)
            esquerda = meio + 1;
        } else {
            // Nome procurado está à esquerda (menor)
            direita = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na lista ordenada.\n", nomeBuscar);
    }
}



// --- Menu Principal (Completo) ---
int main() {
    int escolha;
    int crit_ord;
    long long comparacoes;

    do {
        printf("\n\n=== 🧠 NÍVEL MESTRE - MOCHILA TOTAL ===\n");
        printf("1. Adicionar Item (com Prioridade)\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Listar Itens (com Prioridade)\n");
        printf("4. **Ordenar Mochila**\n");
        printf("5. **Busca Binária por Nome**\n");
        printf("0. Sair\n");
        printf("Status: Mochila Ordenada por Nome: %s\n", isOrdenadaPorNome ? "✅ SIM" : "❌ NÃO");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarItem();
                break;
            case 2:
                // removerItem(); // Chamar a função de remoção
                break;
            case 3:
                listarItens();
                break;
            case 4:
                printf("\n--- Critério de Ordenação ---\n");
                printf("1. Por Nome\n");
                printf("2. Por Tipo\n");
                printf("3. Por Prioridade (Decrescente)\n");
                printf("Escolha o critério: ");
                scanf("%d", &crit_ord);
                
                if (crit_ord >= 1 && crit_ord <= 3) {
                    comparacoes = ordenarMochila((CriterioOrdenacao)crit_ord);
                    printf("\n🎉 Mochila ordenada com sucesso!\n");
                    printf("📊 Comparações realizadas durante a ordenação: %lld\n", comparacoes);
                } else {
                    printf("\n⚠️ Critério de ordenação inválido.\n");
                }
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\n👋 Missão concluída! Sobrevivência total garantida.\n");
                break;
            default:
                printf("\n⚠️ Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}