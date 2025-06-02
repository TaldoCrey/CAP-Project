#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "packages/funcs.c"
#include <stdbool.h>

int main() {
    int capacidade = 5;
    struct Produto *produtos = NULL;
    produtos = malloc(capacidade * sizeof(struct Produto));
    if (produtos == NULL) {
        perror("Erro ao alocar a memória!");
        return -1;
    }
    int i = 0;
    char n[50];
    while (true) {
        
        if (i == capacidade) {
            capacidade *= 2;
            struct Produto *temp = realloc(produtos, capacidade * sizeof(struct Produto));
            if (temp == NULL) {
                perror("Erro ao realocar a memória!");
                free(produtos);
                return -1;
            }
            produtos = temp;
        }

        printf("Adicione um novo produto!\n");
        printf("Digite o nome do produto: \n");
        fgets(n, sizeof n - 1, stdin);
        n[strlen(n) - 1] = '\0';
        printf("Digite o preço do produto: R$");
        double p;
        scanf("%lf", &p);
        printf("\nDigite a quantidade em estoque do produto: ");
        int q;
        scanf("%d", &q);
        printf("\nProcesando Produto!\n");

        printf("-----------------------------------------------\n");
        printf("Produto adicionado!\n");
        produtos[i] = novo_produto(n, p, q);
        printf("-----------------------------------------------\n");
        printf("Deseja adicionar outro produto? [1] S \\ [2] N\n");
        printf("\n>_: ");
        int ram;
        scanf("%d", &ram);

        if (ram != 1) {
            break;
        }
        i++;
        getchar();
    }

    printf("Mostrando todos os produtos!\n");
    

    for(int j = 0; j < i + 1; j++) {
        struct Produto prod = produtos[j];
        printf("-----------------------------------------------\n");
        printf("Nome: %s\nPreco: R$%.2lf\nQtd.: %d\nCód.: %d\n", prod.nome, prod.preco, prod.quantidade, prod.codigo);
        printf("-----------------------------------------------\n");
    }
    free(produtos);
}