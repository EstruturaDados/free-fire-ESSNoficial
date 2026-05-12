#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 10

// ==========================
// Struct Componente
// ==========================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Componente;

Componente mochila[MAX_COMPONENTES];
int totalComponentes = 0;
int ordenadoPorNome = 0;
long comparacoes = 0;

// ==========================
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

// ==========================
// Mostrar componentes (Tabela formatada conforme imagem)
// ==========================
void mostrarComponentes(Componente vetor[], int tamanho) {
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", tamanho, MAX_COMPONENTES);
    printf("---------------------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s | %s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("---------------------------------------------------------------------------\n");

    if (tamanho == 0) {
        printf("Inventario vazio.\n");
    } else {
        for (int i = 0; i < tamanho; i++) {
            printf("%-20s | %-15s | %-10d | %d\n",
                   vetor[i].nome,
                   vetor[i].tipo,
                   vetor[i].quantidade,
                   vetor[i].prioridade);
        }
    }
    printf("---------------------------------------------------------------------------\n");
}

// ==========================
// Adicionar componente
// ==========================
void adicionarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\nMochila cheia!\n");
        pausar();
        return;
    }

    Componente novo;
    printf("\n--- Coletando Novo Componente ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &novo.prioridade);

    mochila[totalComponentes] = novo;
    totalComponentes++;
    ordenadoPorNome = 0;

    printf("\nComponente '%s' adicionado!\n", novo.nome);
    mostrarComponentes(mochila, totalComponentes);
    pausar();
}

// ==========================
// Remover componente
// ==========================
void removerComponente() {
    char nome[30];
    int pos = -1;
    printf("\nDigite o nome do componente para descartar: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nComponente nao encontrado.\n");
    } else {
        for (int i = pos; i < totalComponentes - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalComponentes--;
        printf("\nComponente removido.\n");
    }
    mostrarComponentes(mochila, totalComponentes);
    pausar();
}

// ==========================
// Algoritmos de Ordenação
// ==========================
void bubbleSortNome(Componente vetor[], int tamanho) {
    comparacoes = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    ordenadoPorNome = 1;
}

void insertionSortTipo(Componente vetor[], int tamanho) {
    comparacoes = 0;
    for (int i = 1; i < tamanho; i++) {
        Componente chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        if (j >= 0) comparacoes++; 
        vetor[j + 1] = chave;
    }
    ordenadoPorNome = 0;
}

void selectionSortPrioridade(Componente vetor[], int tamanho) {
    comparacoes = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[menor].prioridade) {
                menor = j;
            }
        }
        Componente temp = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = temp;
    }
    ordenadoPorNome = 0;
}

// ==========================
// Organizar mochila (Menu atualizado)
// ==========================
void organizarMochila() {
    int opcao;
    char criterio[30];

    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    scanf("%d", &opcao);

    if (opcao == 0) return;

    switch(opcao) {
        case 1:
            bubbleSortNome(mochila, totalComponentes);
            strcpy(criterio, "NOME");
            break;
        case 2:
            insertionSortTipo(mochila, totalComponentes);
            strcpy(criterio, "TIPO");
            break;
        case 3:
            selectionSortPrioridade(mochila, totalComponentes);
            strcpy(criterio, "PRIORIDADE");
            break;
        default:
            printf("\nOpcao invalida.\n");
            return;
    }

    printf("\nMochila organizada por %s.\n", criterio);
    printf("Analise de Desempenho: Foram necessarias %ld comparacoes.\n", comparacoes);

    mostrarComponentes(mochila, totalComponentes);
    pausar();
}

// ==========================
// Busca binária (Alerta atualizado)
// ==========================
void buscarComponente() {
    if (!ordenadoPorNome) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a Opcao 4 para organizar a mochila primeiro.\n");
        pausar();
        return;
    }

    char nome[30];
    printf("\n--- Busca Binária por Componente-Chave ---");
    printf("\nNome do componente a buscar: ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = totalComponentes - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, nome);
        if (resultado == 0) {
            printf("\n--- COMPONENTE-CHAVE ENCONTRADO ---\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            pausar();
            return;
        }
        if (resultado < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    printf("\nComponente nao encontrado.\n");
    pausar();
}

// ==========================
// Menu Principal
// ==========================
void mostrarMenu() {
    printf("\n============================================================\n");
    printf("    PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("============================================================\n");
    printf("Itens na Mochila: %d/%d\n", totalComponentes, MAX_COMPONENTES);
    printf("Status da Ordenacao por Nome: %s\n\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
    printf("1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("------------------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;
    do {
        mostrarMenu();
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: adicionarComponente(); break;
            case 2: removerComponente(); break;
            case 3: mostrarComponentes(mochila, totalComponentes); pausar(); break;
            case 4: organizarMochila(); break;
            case 5: buscarComponente(); break;
            case 0: printf("\nTorre ativada. Fuga iniciada!\n"); break;
            default: printf("\nOpcao invalida.\n"); pausar();
        }
    } while(opcao != 0);
    return 0;
}
