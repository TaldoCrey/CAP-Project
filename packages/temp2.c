#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "packages/funcs.c" 

int main() {

    // ... (unchanged initial configuration logic for exec_mode.txt) ...

    char exec_mode = fgetc(exec_info_read);
    fclose(exec_info_read);
    
    if (exec_mode == 'c') { // Modo CAIXA
        system("clear");
        printf("Modo CAIXA!\n");

        int escolha = -1;
        while (escolha != 4) { 
            printf("---------------------------------------\n");
            printf("Selecione uma Opção:\n[1] Realizar compra\n[2] Ver e Remover Produtos do Carrinho\n[3] Editar Usuário\n[4] Sair\n");
            printf(">_: ");
            scanf("%d", &escolha);
            while (getchar() != '\n');
            
            switch (escolha)
            {
            case 1:
                system("clear"); 

                int qtd = 0;
                // Load products once at the start of the purchase session
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

                    // --- NEW LOGIC START ---
                    // Validate if product exists AND if it has stock BEFORE proceeding
                    if (produto_encontrado.codigo == -1) {
                        printf("\nProduto nao encontrado. ");
                    } else if (produto_encontrado.quantidade == 0) {
                        printf("\nProduto '%s' (codigo %d) esta fora de estoque! Nao e possivel adicionar mais.\n", 
                               produto_encontrado.nome, produto_encontrado.codigo);
                        // No need for a loop here, just inform and prompt for next product
                    } else {
                        // Product found and has stock, proceed with quantity selection
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

                        adicionar_ao_carrinho(produto_encontrado.codigo, produto_encontrado.nome, quantidade_a_comprar, produto_encontrado.preco);
                        
                        printf("\nAdicionando %d unidades de %s ao carrinho...", quantidade_a_comprar, produto_encontrado.nome);
                        printf("\n---------------------------------------\n");
                        
                        // !!! IMPORTANT: Directly update the in-memory quantity after a successful add
                        // This prevents the infinite loop for the current session.
                        // You need to find the product in the 'produtos' array and update its quantity.
                        for (int i = 0; i < qtd; i++) {
                            if (produtos[i].codigo == codigo) {
                                produtos[i].quantidade -= quantidade_a_comprar;
                                break;
                            }
                        }
                    }
                    // --- NEW LOGIC END ---
            
                    printf("Digite o codigo do proximo produto (-1 para sair):\n> ");
                    scanf("%d", &codigo);
                    while (getchar() != '\n');
                }
                if (produtos != NULL) { 
                    free(produtos); 
                    produtos = NULL; 
                }
                break;
            
            case 2:
                system("clear");
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
    // ... (rest of main.c code) ...