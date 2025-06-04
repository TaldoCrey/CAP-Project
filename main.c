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
    fclose(exec_info);
    
    if (exec_mode == 'c') {
        printf("CAIXA\n");
    } else {
        int c = -1;
        int qtd = 0;
        struct Produto* produtos = loadProducts(&qtd);
        while (c != 6) {
            printf("---------------------------------------\n");
            printf("Selecione uma Opção:\n[1] Adicionar Produtos\t[2] Adicionar Usuário\n[3] Editar Produto\t[4] Editar Usuário\n[5] Ver Todos os Produtos\t[6] Sair\n");
            printf(">_: ");
            scanf("%d", &c);

            if (c == 1) {
                system("clear");
                produtos = adicionar_produtos(&qtd);
                saveProducts(produtos, qtd);
            } else if (c == 5) {
                system("clear");
                mostrar_produtos(qtd, produtos);
            }
        }
    }
}

