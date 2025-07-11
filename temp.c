#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "packages/funcs.c" // Keep this as is, or change to funcs.h if you compile separately

int main() {

    // ... (unchanged initial configuration logic for exec_mode.txt) ...

    char exec_mode = fgetc(exec_info_read);
    fclose(exec_info_read);
    
    if (exec_mode == 'c') { // Modo CAIXA
        system("clear");
        printf("Modo CAIXA!\n");

        int escolha = -1;
        // !!! IMPORTANT CHANGE: Loop condition to match 'Sair' as option 4
        while (escolha != 4) { 
            printf("---------------------------------------\n");
            // !!! IMPORTANT CHANGE: Updated menu option text
            printf("Selecione uma Opção:\n[1] Realizar compra\n[2] Ver e Remover Produtos do Carrinho\n[3] Editar Usuário\n[4] Sair\n");
            printf(">_: ");
            scanf("%d", &escolha);
            while (getchar() != '\n'); // Clear input buffer
            
            switch (escolha)
            {
            case 1:
                system("clear"); 

                int qtd = 0;
                struct Produto* produtos = loadProducts(&qtd);
                if (produtos == NULL || qtd == 0) {
                    printf("Nenhum produto cadastrado no sistema ou erro ao carregar produtos.\n");
                    if (produtos != NULL) free(produtos);
                    continue; 
                }

                int codigo;
                printf("\nDigite o codigo do produto (-1 para sair):\n> ");
                scanf("%d", &codigo);
                while (getchar() != '\n');
                printf("\n---------------------------------------\n");

                int sair_compra = 0;
                while (codigo != -1){
                    struct Produto produto_encontrado = buscar_produto_por_codigo(produtos, qtd, codigo);

                    while (produto_encontrado.codigo == -1) {
                        printf("\nProduto nao encontrado. Digite um codigo valido (ou -1 para cancelar):\n> ");
                        scanf("%d", &codigo);
                        while (getchar() != '\n');

                        if (codigo == -1) {
                            printf("Busca cancelada.\n");
                            sair_compra = 1;
                            break; 
                        }
                        produto_encontrado = buscar_produto_por_codigo(produtos, qtd, codigo);
                    }

                    if (sair_compra)
                        break;

                    if (produto_encontrado.codigo != -1) {
                        system("clear");

                        int quantidade_a_comprar;
                        printf("\n(%d)  %s  R$%.2f\n", produto_encontrado.codigo, produto_encontrado.nome, produto_encontrado.preco);
                        printf("Quantidade no estoque: %d\n\n", produto_encontrado.quantidade);
                        printf("Digite a quantidade de unidades a ser comprada:\n> ");
                        scanf("%d", &quantidade_a_comprar);
                        while (getchar() != '\n');

                        while (quantidade_a_comprar <= 0 || quantidade_a_comprar > produto_encontrado.quantidade){
                            if (quantidade_a_comprar <= 0) {
                                printf("\nQuantidade invalida. Digite um valor maior que zero:\n> ");
                            } else {
                                printf("\nExistem apenas %d unidades no estoque!", produto_encontrado.quantidade);
                                printf("\nPor favor, digite um valor válido:\n> ");
                            }
                            scanf("%d", &quantidade_a_comprar);
                            while (getchar() != '\n');
                        }

                        // !!! IMPORTANT CHANGE: Call adicionar_ao_carrinho without the stock pointer
                        adicionar_ao_carrinho(produto_encontrado.codigo, produto_encontrado.nome, quantidade_a_comprar, produto_encontrado.preco);
                        
                        printf("\nAdicionando %d unidades de %s ao carrinho...", quantidade_a_comprar, produto_encontrado.nome);
                        printf("\n---------------------------------------\n");
                    }
            
                    printf("\nDigite o codigo do proximo produto (-1 para sair):\n> ");
                    scanf("%d", &codigo);
                    while (getchar() != '\n');
                }
                free(produtos); // Free products after finishing the purchase session
                break;
            
            case 2:
                system("clear");
                // !!! IMPORTANT CHANGE: Call the new remover_do_carrinho function
                remover_do_carrinho(); 
                break;
            case 3:
                system("clear");
                editar_usuario();
                break;
            case 4:
                printf("Saindo do Modo CAIXA...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }
    // ... (unchanged Admin Mode logic) ...

    } else { // Admin Mode
        system("clear");
        printf("Modo ADMINISTRATIVO!\n"); 
        int c = -1;
        int qtd = 0;
        struct Produto* produtos = loadProducts(&qtd);

        while (c != 7) {
            printf("---------------------------------------\n");
            printf("Selecione uma Opção:\n[1] Adicionar Produtos\t[2] Adicionar Usuário\n[3] Editar Produto\t[4] Editar Usuário\n[5] Ver Todos os Produtos\t[6] Editar Usuário do Sistema\t[7] Sair\n");
            printf(">_: ");
            scanf("%d", &c);
            while (getchar() != '\n'); 
            
            if (c == 1) {
                system("clear");
                struct Produto* temp_added_prods = adicionar_produtos(&qtd); 
                if (temp_added_prods != NULL) {
                    free(temp_added_prods); 
                }
                free(produtos); 
                produtos = loadProducts(&qtd); 
            
            } else if (c == 5) {
            
                system("clear");
                free(produtos);
                produtos = loadProducts(&qtd);
                mostrar_produtos(qtd, produtos);
            } else if (c == 2){
                system("clear");
                adicionar_usuario();
            } else if (c == 6){
                system("clear");
                editar_usuario();
            } else if (c == 3){ 
                system("clear");
                printf("Funcionalidade 'Editar Produto' ainda não implementada.\n");
            } else if (c == 4){ 
                system("clear");
                printf("Funcionalidade 'Editar Usuário' (admin) ainda não implementada, use a opção 6.\n");
            } else if (c == 7) {
                printf("Saindo do Modo ADMINISTRATIVO. Até mais!\n");
            } else {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
        free(produtos);
    }
    return 0;
}