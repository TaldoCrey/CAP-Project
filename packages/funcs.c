#include <stdio.h>
#include <string.h>


int cod = 0;
int user_id = 0;

/*
    Container que armazena a informação de um Produto!

    @param nome: Nome do Protudo!
    @param preco: Preço do Produto!
    @param codigo: Código deidentificação do protudo!
    @param quantidade: Quantidade do Produto no estoque!
*/
typedef struct Produto {
    char nome[50];
    double preco;
    int codigo;
    int quantidade;
} prod;

/*
    Container que armazena a informação de um usuário.
    OBS: Todo usuário cadastrado é considerado um administrador do sistema!

    @param login: Nome de Login do Usuário!
    @param password: Senha de Login do Usuário!
    @param userID: ID de usuário (Utilitário para o banco de dados!)
*/
typedef struct User {
    char login[100];
    char password[20];
    int userID;
} user;

/*
    Função que cria um novo produto no sistema!

    @param nome: Nome do Produto!
    @param preco: Preço do Produto!
    @param quantidade: Quantidade do Produto em Estoque!

    @returns Um container contendo todas as informações do Produto!
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

/*
    Função que cria um novo usuário no sistema!

    @param login: Login de Usuário no sistema!
    @param senha: Senha para login de Usuário no sistema!

    @return Um container contendo todas as informações do usuário!
*/
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

    @param qtd: (Quantidade) Contabiliza quantos produtos foram de fato adicionados ao sistema!

    @returns Uma lista contendo conteineres de todos os produtos adicionados!
*/
struct Produto* adicionar_produtos(int *qtd) {
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
        *qtd += 1;
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

/*
    Mostra todos os produtos em estoque!

    @param qtd:(Quantidade) Informa a quantidade atual de produtos no estoque!
    @param produtos: Lista que contém os conteineres de cada produto!
*/
void mostrar_produtos(int qtd, struct Produto* produtos) {
    printf("Mostrando todos os produtos!\n");

    for(int j = 0; j < qtd; j++) {
        struct Produto prod = produtos[j];
        printf("-----------------------------------------------\n");
        printf("Nome: %s\nPreco: R$%.2lf\nQtd.: %d\nCod.: %d\n", prod.nome, prod.preco, prod.quantidade, prod.codigo);
        printf("-----------------------------------------------\n");
    }
}
