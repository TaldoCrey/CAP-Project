#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "packages/funcs.c"

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
    fclose(exec_mode);
    
    if (exec_mode == 'c') {
        printf("CAIXA\n");
    } else {
        struct Produto* produtos = adicionar_produtos();
        printf("Mostrando todos os produtos!\n");

        for(int j = 0; j < sizeof(produtos); j++) {
            struct Produto prod = produtos[j];
            printf("-----------------------------------------------\n");
            printf("Nome: %s\nPreco: R$%.2lf\nQtd.: %d\nCod.: %d\n", prod.nome, prod.preco, prod.quantidade, prod.codigo);
            printf("-----------------------------------------------\n");
        }
    }
}
