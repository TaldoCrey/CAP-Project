#include <stdio.h>
#include <string.h>

int cod = 0;

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

