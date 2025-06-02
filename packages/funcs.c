#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int cod = 0;

/*
    Container que armazena as informações dos produtos!

    @param nome Nome do Produto!
    @param preco Preço do Produto!
    @param codigo Código do Produto!
    @param quantidade Quantidade do Produto em Estoque!
*/
typedef struct Produto {
    
    char nome[50];
    double preco;
    int codigo;
    int quantidade;
} prod;

/*
    Container que armazena as informações dos usuários!

    @param login Nome de Login no sistema!
    @param password Senha de Login no sistema!
    @param userID ID de usuário - Utilitário para o banco de dados.
*/
typedef struct User {
    char login[100];
    char password[20];
    int userID;
} user;

/*
    Inicia um novo produto!

    @param nome Nome do Produto!
    @param preco Preço do Produto!
    @param quantidade Quantidade do Produto em Estoque!
    @returns Um container da classe Produto já iniciado e preenchido!
*/
struct Produto novo_produto(char nome[50], double preco, int quantidade) {

    prod new_prod;
    strcpy(new_prod.nome, nome);
    new_prod.preco = preco;
    new_prod.quantidade = quantidade;
    new_prod.codigo = cod;
    cod++;
    return new_prod;
}

void adicionar_produtos(struct Produto *all, int size) {
    int capacidade = 5;
    struct Produto *prods = NULL;
    prods = malloc(capacidade * sizeof(struct Produto));
    if (prods == NULL) {
        perror("Erro ao alocar a memória!");
        return;
    }
    int i = 0;
    char n[50];
    while (true) {
        
        if (i == capacidade) {
            capacidade *= 2;
            struct Produto *temp = realloc(prods, capacidade * sizeof(struct Produto));
           if (temp == NULL) {
                perror("Erro ao realocar a memória!");
                free(prods);
                return;
            }
            prods = temp;
        }

        printf("Adicione um novo produto!\n");
        printf("Digite o nome do produto: \n");
        fgets(n, sizeof n - 1, stdin);
        n[strlen(n) - 1] = '\0';
        printf("Digite o preço do produto: R$");
        double p;
        scanf("%lf", &p);
        printf("Digite a quantidade em estoque do produto: ");
        int q;
        scanf("%d", &q);
        printf("Procesando Produto!\n");

        printf("-----------------------------------------------\n");
        printf("Produto adicionado!\n");
        prods[i] = novo_produto(n, p, q);
        printf("-----------------------------------------------\n");
        printf("Deseja adicionar outro produto? [1] S \\ [2] N");
        printf("\n>_: ");
        int ram;
        scanf("%d", &ram);

        if (ram != 1) {
            break;
        }
        i++;
        getchar();
    }

    if (capacidade > size) {
        while (capacidade > size) {
            size *= 2;
        }

        struct Produto *alltemp = realloc(prods, size * sizeof(struct Produto));
        if (alltemp == NULL) {
            perror("Erro ao realocar a memória!");
            free(all);
            free(prods);
            return;
        }
        all = alltemp;
    } else {
        all = prods;
    }
    //free(prods);
}

void mostrar_produtos(struct Produto *produtos) {
    for (int i = 0; i < sizeof(produtos); i++) {
        printf("------------ #%d ------------\n", i);
        printf("Nome: %s\nPreço: R$%.2lf\nQuantidade: %d\nCódigo: %d\n", produtos[i].nome, produtos[i].preco, produtos[i].quantidade, produtos[i].codigo);
        printf("------------ === ------------\n");
    }
}

