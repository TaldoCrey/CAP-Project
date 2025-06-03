#include <stdio.h>
#include <string.h>


int cod = 0;
int user_id = 0;
typedef struct Produto {
    char nome[50];
    double preco;
    int codigo;
    int quantidade;
} prod;

typedef struct User {
    char login[100];
    char password[20];
    int userID;
} user;

struct Produto novo_produto(char nome[50], double preco, int quantidade) {

    prod new_prod;
    strcpy(new_prod.nome, nome);
    new_prod.preco = preco;
    new_prod.quantidade = quantidade;
    new_prod.codigo = cod;
    cod++;
    return new_prod;

}

struct User novo_usuario(char login[100], char senha[20]) {

    user new_user;
    strcpy(new_user.login, login);
    strcpy(new_user.password, senha);
    new_user.userID = user_id;
    user_id++;
    return new_user;
}

/*
Adiciona novos produtos até que o usuário deseje parar!
*/
struct Produto* adicionar_produtos() {
    int capacidade = 1;
    struct Produto *produtos = NULL;
    produtos = malloc(capacidade * sizeof(struct Produto));
    if (produtos == NULL) {
        perror("Erro ao alocar a memória!");
        return NULL;
    }
    int i = 0;
    char n[50];
    while (1) {
        
        if (i == capacidade) {
            capacidade *= 2;
            struct Produto *temp = realloc(produtos, capacidade * sizeof(struct Produto));
            if (temp == NULL) {
                perror("Erro ao realocar a memória!");
                free(produtos);
                return NULL;
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
        printf("Digite a quantidade em estoque do produto: ");
        int q;
        scanf("%d", &q);
        printf("Procesando Produto!\n");

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
    return produtos;
}
