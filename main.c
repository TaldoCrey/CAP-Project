#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "packages/funcs.c"

int main() {
    FILE *exec_info = fopen(".//exec_mode.txt", "r");
    if (exec_info == NULL) {
        exec_info = fopen(".//exec_mode.txt", "w");
        if (exec_info == NULL) {
            perror("Erro ao abrir arquivo vital!");
            return -1;
        }

        int mode;
        printf("Em qual modo o sistema deve operar nessa máquina?\n[1] Administrativo\n[2] Caixa\n> ");
        scanf("%d", &mode);

        if (mode == 1) {
            fprintf(exec_info, "a");
            printf("Sistema configurado para rodar no modo ADMINISTRATIVO nesta máquina!\n");
        } else {
            fprintf(exec_info, "c");
            printf("Sistema configurado para rodar no modo CAIXA nesta máquina!\n");
        }

        fclose(exec_info);
        return 1;
    }

    char exec_mode = fgetc(exec_info);
    fclose(exec_info);

    if (exec_mode == 'c') {
        printf("Modo CAIXA!\n");

        int escolha = -1;
        while (escolha != 4) {
            printf("---------------------------------------\n");
            printf("Selecione uma Opção:\n[1] Realizar compra\n[2] Ver carrinho de compra\n[3] Acessar conta do cliente\n[4] Sair\n");
            printf(">_: ");
            scanf("%d", &escolha);                
            switch (escolha) {
                case 1: {
                    system("clear"); 
                    int qtd = 0;
                    struct Produto* produtos = loadProducts(&qtd);
                    mostrar_produtos(qtd, produtos);

                    if (produtos == NULL && qtd == 0) {
                        printf("Nenhum produto cadastrado no sistema.\n");
                        continue; 
                    }

                    int codigo;
                    printf("\nDigite o codigo do produto (-1 para sair):\n> ");
                    scanf("%d", &codigo);
                    while (getchar() != '\n');

                    int sair_compra = 0;
                    while (codigo != -1) {
                        if (produtos != NULL) free(produtos);
                        produtos = loadProducts(&qtd); 
                        if (produtos == NULL || qtd == 0) {
                            printf("Erro ao carregar produtos ou nenhum produto cadastrado. Saindo da compra.\n");
                            sair_compra = 1;
                            break; 
                        }

                        struct Produto produto_encontrado = buscar_produto_por_codigo(produtos, qtd, codigo);
                        if (produto_encontrado.codigo == -1) {
                            printf("\nProduto nao encontrado. ");
                        } else if (produto_encontrado.quantidade == 0){
                            printf("\n%s está fora de estoque! Não é possível adicionar mais.\n", produto_encontrado.nome);
                        } else {
                            int quantidade_a_comprar;
                            printf("\n(%d)  %s  R$%.2f\n", produto_encontrado.codigo, produto_encontrado.nome, 
                                produto_encontrado.valor_promo > 0 ? produto_encontrado.valor_promo : produto_encontrado.preco);
                            printf("Quantidade no estoque: %d\n\n", produto_encontrado.quantidade);
                            printf("Digite a quantidade de unidades a ser comprada:\n> ");
                            scanf("%d", &quantidade_a_comprar);

                            while (quantidade_a_comprar <= 0 || quantidade_a_comprar > produto_encontrado.quantidade) {
                                if (quantidade_a_comprar <= 0)
                                    printf("\nQuantidade inválida. Digite um valor maior que zero:\n> ");
                                else {
                                    printf("\nExistem apenas %d unidades no estoque!", produto_encontrado.quantidade);
                                    printf("\nPor favor, digite um valor válido:\n> ");
                                }
                                scanf("%d", &quantidade_a_comprar);
                            }

                            adicionar_ao_carrinho(produto_encontrado.codigo, produto_encontrado.nome, quantidade_a_comprar, produto_encontrado.preco, produto_encontrado.valor_promo);
                            printf("\nAdicionando %d unidades de %s ao carrinho...\n", quantidade_a_comprar, produto_encontrado.nome);
                        }

                        printf("\nDigite o codigo do produto (-1 para sair):\n> ");
                        scanf("%d", &codigo);
                    }

                    if (produtos != NULL) free(produtos);
                    break;
                }
                case 2:
                    system("clear");
                    if (finalizar_compra()) {
                        remove("carrinho.txt");
                    }
                    break;
                case 3:
                    system("clear");
                    printf("Autenticação do Administrador requerida!\n");
                    if (login_admin()) {
                        conta_cliente();
                    } else {
                        printf("Falha na autenticação. Retornando ao menu.\n");
                    }
                    break;
                case 4:
                    printf("Encerrando aplicação...\n");
                    return 0;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }
        }
    //Modo Admin
    } else {
        int c = -1;
        int qtd = 0;
        struct Produto* produtos = loadProducts(&qtd);

        while (1) {
            printf("---------------------------------------\n");
            printf("Selecione uma Opcao:\n[1] Adicionar Produtos\t[2] Adicionar Usuario\n[3] Alterar estoque\t[4] Editar Produto\n[5] Editar Usuario\t[6] Ver Todos os Produtos\n[7] Editar Usuario do Sistema\t[8]Sair\n");
            printf(">_: ");
            scanf("%d", &c);
            
            if (c == 1) {
                system("clear");
                struct Produto* temp_prods = adicionar_produtos(&qtd); 
                if (temp_prods != NULL){
                    free(temp_prods); 
                }
                free(produtos); 
                produtos = loadProducts(&qtd); 
            } else if (c == 2){
                adicionar_usuario();
            } else if (c == 3){
                system("clear");

                int escolha_adm;
                printf("Cod##Nome do Produto ..... Quantidade\n");
                for (int index = 0; index < qtd; index++) {
                    printf("%d##%s .......... %d\n", produtos[index].codigo, produtos[index].nome, produtos[index].quantidade);
                }
                printf("Selecione uma Opcao:\n[1] Adicionar Produtos ao Estoque\n[2] Remover produtos ao Estoque\n[3] Voltar\n> ");
                scanf("%d", &escolha_adm);

                if (escolha_adm == 3) {
                    continue;
                }

                while (escolha_adm > 2 || escolha_adm < 1){
                    printf("Digite uma opcao valida!\n> ");
                    scanf("%d", &escolha_adm);
                }

                if (escolha_adm == 1) {
                    adicionar_quantidade_estoque_admin();
                } else {
                    remover_quantidade_estoque_admin();
                }

                produtos = loadProducts(&qtd);
            } else if (c == 4) {
                system("cls");
                editar_produto(&qtd);

            } else if (c == 6) {
            
                system("clear");
                free(produtos);
                produtos = loadProducts(&qtd);
                mostrar_produtos(qtd, produtos);
            
            } else if (c == 7){
                editar_usuario();
            } else if (c == 8) {
                printf("Encerrando Aplicação!\n");
                break;

            } else {
                printf("Digite uma opcao valida!\n");
            }
        }
        free(produtos);
    }
    
}