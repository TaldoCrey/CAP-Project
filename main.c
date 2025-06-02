#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "packages/funcs.c"
#include <stdbool.h>

int main() {
    int capacidade = 5;
    struct Produto *produtos = NULL;
    produtos = malloc(capacidade * sizeof(struct Produto));
    if (produtos == NULL) {
        perror("Erro ao alocar a memória!");
        return -1;
    }
    adicionar_produtos(produtos, 2);

    mostrar_produtos(produtos);
}