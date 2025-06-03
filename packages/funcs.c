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

