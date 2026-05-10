#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ==========================
// Definição da Struct Item
// ==========================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor da mochila
Item mochila[MAX_ITENS];
int totalItens = 0;

// ==========================
// Função pausa
// ==========================
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

// ==========================
// Listar itens
// ==========================
void listarItens() {

    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n",
           totalItens,
           MAX_ITENS);

    printf("--------------------------------------------------\n");
    printf("NOME               | TIPO           | QUANTIDADE\n");
    printf("--------------------------------------------------\n");

    if (totalItens == 0) {

        printf("Mochila vazia!\n");

    } else {

        for (int i = 0; i < totalItens; i++) {

            printf("%-18s | %-14s | %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
        }
    }

    printf("--------------------------------------------------\n");
}

// ==========================
// Inserir item
// ==========================
void inserirItem() {

    if (totalItens >= MAX_ITENS) {

        printf("\nMochila cheia!\n");
        pausar();
        return;
    }

    Item novo;

    printf("\nNome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("\nItem '%s' adicionado com sucesso!\n",
           novo.nome);

    listarItens();
    pausar();
}

// ==========================
// Remover item
// ==========================
void removerItem() {

    if (totalItens == 0) {

        printf("\nMochila vazia!\n");
        pausar();
        return;
    }

    char nome[30];
    int pos = -1;

    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    // Busca sequencial
    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {

        printf("\nItem nao encontrado!\n");

    } else {

        for (int i = pos; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        totalItens--;

        printf("\nItem '%s' removido com sucesso!\n",
               nome);
    }

    listarItens();
    pausar();
}

// ==========================
// Buscar item por nome
// ==========================
void buscarItem() {

    if (totalItens == 0) {

        printf("\nMochila vazia!\n");
        pausar();
        return;
    }

    char nome[30];
    int encontrado = 0;

    printf("\n--- Buscar Item na Mochila ---\n");

    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {

            encontrado = 1;

            printf("\n--- Item Encontrado! ---\n");

            printf("Nome: %s\n",
                   mochila[i].nome);

            printf("Tipo: %s\n",
                   mochila[i].tipo);

            printf("Quantidade: %d\n",
                   mochila[i].quantidade);

            printf("------------------------\n");

            break;
        }
    }

    if (!encontrado) {

        printf("\nResultado: Item '%s' NAO foi encontrado na mochila.\n",
               nome);
    }

    pausar();
}

// ==========================
// Menu
// ==========================
void mostrarMenu() {

    printf("\n=========================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("=========================================\n");

    printf("Itens na Mochila: %d/%d\n\n",
           totalItens,
           MAX_ITENS);

    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Buscar Item por Nome\n");
    printf("0. Sair\n");

    printf("-----------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// ==========================
// Main
// ==========================
int main() {

    int opcao;

    do {

        mostrarMenu();

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                inserirItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                pausar();
                break;

            case 4:
                buscarItem();
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }

    } while (opcao != 0);

    return 0;
}
