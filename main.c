#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "packages/funcs.c"
#include <stdbool.h>

/*
Adiciona novos produtos até que o usuário deseje parar!
*/
int adicionar_produtos() {
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
    return 0;
}





int main() {

    FILE *exec_info = fopen(".//exec_mode.txt", "r");
    if (exec_info == NULL) {

        FILE *exec_info = fopen(".//exec_mode.txt", "w");

        if (exec_info == NULL) {
            perror("Erro ao abrir arquivo vital!");
            return -1;
        }

        int mode;
        printf("Em qual modo o sistema deve operar nessa máquina?\n[1] Administrativo\n[2] Caixa\n");
        scanf("%d", &mode);

        if (mode == 1) {
            fprintf(exec_info, "a");
            printf("O sistema foi configurado para rodar no modo ADMINISTRATIVO nesta máquina!\n");
        } else {
            fprintf(exec_info, "c");
            printf("O sistema foi configurado para rodar no modo CAIXA nesta máquina!\n");
        }

        fclose(exec_info);
        return 1;
    }

    char exec_mode = fgetc(exec_info);
    
    if (exec_mode == 'c') {
        printf("CAIXA\n");
    } else {
        printf("ADMIN\n");
    }
}
