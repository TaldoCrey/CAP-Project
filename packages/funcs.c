#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int user_id = 0;
int cod = 0;

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
    Função que armazena um produto no banco de dados!

    @param produtos: Lista contendo os produtos a serem armazenados!
*/
void saveProduct(struct Produto produto) {

    FILE * data_f = fopen(".//products.txt", "a");
    if (data_f == NULL) {
        FILE * data_f = fopen(".//products.txt", "w");
    }


    fprintf(data_f, "%s;%.2lf;%d;%d\n", produto.nome, produto.preco, produto.quantidade, produto.codigo);
    printf("{%s} foi adicionado ao banco de dados!\n", produto.nome);

    fclose(data_f);
}

/*
    Adiciona novos produtos até que o usuário deseje parar!

    @param qtd: (Quantidade) Contabiliza quantos produtos foram de fato adicionados ao sistema!

    @returns Uma lista contendo conteineres de todos os produtos adicionados!
*/
struct Produto* adicionar_produtos(int *qtd) {
    int capacidade = 1;
    struct Produto *add_produtos = NULL;
    add_produtos = malloc(capacidade * sizeof(struct Produto));
    if (add_produtos == NULL) {
        perror("Erro ao alocar a memória!");
        return NULL;
    }
    int i = 0;
    char n[50];
    while (1) {
        
        if (i == capacidade) {
            capacidade *= 2;
            struct Produto *temp = realloc(add_produtos, capacidade * sizeof(struct Produto));
            if (temp == NULL) {
                perror("Erro ao realocar a memória!");
                free(add_produtos);
                return NULL;
            }
            add_produtos = temp;
        }

        printf("Adicione um novo produto!\n");
        getchar();
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
        add_produtos[i] = novo_produto(n, p, q);

        saveProduct(add_produtos[i]);

        (*qtd) += 1;
        printf("-----------------------------------------------\n");
        printf("Deseja adicionar outro produto? [1] S \\ [2] N\n");
        printf("\n>_: ");
        int ram;
        scanf("%d", &ram);

        if (ram != 1) {
            break;
        }
        i++;
    }
    return add_produtos;
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

/*
    Função que carrega os produtos armazenados no arquivo

    @param qtd: Quantidade total de produtos
    @returns: Uma lista com todos o produtos já carregados
*/
struct Produto* loadProducts(int *qtd) {
    *qtd = 0;
    int capacidade = 2;
    struct Produto* prods = NULL;
    prods = malloc(capacidade * sizeof(struct Produto));
    if (prods == NULL) {
        perror("Erro ao alocar a memória!");
        return NULL;
    }

    FILE * data_f = fopen(".//products.txt", "r");

    if (data_f == NULL) {
        perror("Erro ao carregar produtos!");
        return prods;
    }

    char linha[200];
    const char del[] = ";";
    int maior_codigo = -1;
    while (fgets(linha, sizeof(linha), data_f) != NULL) {
        linha[strlen(linha) - 1] = '\0';
        if (strlen(linha) == 0) {
            continue;
        }
        if (*qtd == capacidade) {
            capacidade *= 2;
            struct Produto *temp = realloc(prods, capacidade * sizeof(struct Produto));
            if (temp == NULL) {
                perror("Erro ao realocar a memória!");
                free(prods);
                fclose(data_f);
                return NULL;
            }
            prods = temp;
        }
        
        char *it;
        char nome[50];
        double preco;
        int quant;
        int codigo_prod = -1;

        char temp_linha[200];
        strcpy(temp_linha, linha);

        it = strtok(temp_linha, del);

        if (it) 
            strcpy(nome, it); 
        else 
            continue;

        it = strtok(NULL, del); 

        if (it) 
            sscanf(it, "%lf", &preco); 
        else 
            continue;

        it = strtok(NULL, del); 
        
        if (it) 
            sscanf(it, "%d", &quant); 
        else 
            continue;

        it = strtok(NULL, del);

        if (it) 
            sscanf(it, "%d", &codigo_prod);
        else
            codigo_prod = cod;

        strcpy(prods[*qtd].nome, nome);
        prods[*qtd].preco = preco;
        prods[*qtd].quantidade = quant;
        prods[*qtd].codigo = codigo_prod;

        if (codigo_prod > maior_codigo) {
            maior_codigo = codigo_prod;
        }
        (*qtd)++;
    }
    cod = maior_codigo + 1;
    fclose(data_f);
    return prods;
}

/*
    Função que lê o código do produto e o associa ao preço e ao produto!

    @param lista: Lista contendo os conteiners de cada produto!
    @param qtd (Quantidade): Informa a quantidade de produtos que tem no estoque!
    @param codigo: Código de um produto!
    @returns produto: Retorna o produto referente ao código ou not_found caso nao encontre!
*/
struct Produto buscar_produto_por_codigo(struct Produto* lista, int qtd, int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (lista[i].codigo == codigo) {
            return lista[i];
        }
    }
    struct Produto not_found;
    strcpy(not_found.nome, "NAO ENCONTRADO");
    not_found.preco = 0;
    not_found.quantidade = 0;
    not_found.codigo = -1;
    return not_found;
}

/*
    Container que armazena a informação de um item no carrinho de compras!
*/
typedef struct CarrinhoItem {
    int codigo;
    char nome[50];
    int quantidade;
    double preco_unitario; 
} CarrinhoItem;

/*
    Função que recebe o pagamento do usuário e devolve o troco!

    @param total: Valor totoal da compra!
    @param pago: Valor pago pelo usuário!
    @returns: Valor do troco ou -1, caso o pagamento seja insuficiente!
*/
double devolve_troco (double pago, double total){
    // Verifica se o usuário fez o pagamento com um valor correto (maior ou igual ao valor da compra)
    if (pago < total){
        printf("\nPagamento insuficiente! O valor pago e menor que o total. \n");
        return -1;
    }

    // Calcula o troco e retorna
    double troco = pago - total;
    return troco;
}

/*
    Procedimento que atualiza a quantidade de um produto no arquivo products.txt.
    Lê todos os produtos, atualiza a quantidade do produto específico em memória,
    e depois reescreve todo o arquivo.
    
    @param codigo: Código do produto a ser atualizado.
    @param quantidade_alterada: A quantidade a ser adicionada ou removida do estoque.
*/

void atualizar_estoque(int codigo, int quantidade_alterada) { 
    int total_produtos_no_arquivo = 0;
    
    struct Produto* todos_produtos = loadProducts(&total_produtos_no_arquivo); 

    if (todos_produtos == NULL) {
        printf("Nao foi possivel carregar produtos!\n");
        return;
    }

    int produto_encontrado_no_array = 0;
    for (int i = 0; i < total_produtos_no_arquivo; i++) {
        if (todos_produtos[i].codigo == codigo) {
            todos_produtos[i].quantidade += quantidade_alterada; 
            
            if (todos_produtos[i].quantidade < 0) {
                todos_produtos[i].quantidade = 0; 
                printf("Estoque ajustado para 0.\n");
            }
            produto_encontrado_no_array = 1;
            break; 
        }
    }

    if (!produto_encontrado_no_array) {
        printf("Produto com codigo %d nao encontrado!\n", codigo);
        free(todos_produtos);
        return;
    }

    FILE *file = fopen("products.txt", "w"); 
    if (file == NULL) {
        perror("Erro ao reescrever o arquivo products.txt");
        free(todos_produtos);
        return;
    }

    for (int i = 0; i < total_produtos_no_arquivo; i++) {
        fprintf(file, "%s;%.2lf;%d;%d\n", todos_produtos[i].nome, todos_produtos[i].preco, 
                todos_produtos[i].quantidade, todos_produtos[i].codigo);
    }

    fclose(file);
    free(todos_produtos); 
}

/*
    Procedimento que adiciona os produtos ao carrinho de compra!
    Além disso, atualiza o valor do produto em products.txt!

    @param codigo: Código referente ao produto.
    @param nome: Nome do produto.
    @param quantidade: Quantidade do produto a ser adicionada ao carrinho.
    @param preco: Preço unitário do produto.
*/
void adicionar_ao_carrinho(int codigo, const char* nome, int quantidade, double preco) {
    FILE *file = fopen("carrinho.txt", "a"); 
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de carrinho!");
        return;
    }

    fprintf(file, "%d;%s;%d;%.2f\n", codigo, nome, quantidade, preco);
    fclose(file);  

    atualizar_estoque(codigo, -quantidade); 
    printf("\n-------------------------------------------\n");
    printf("(Qtd %d) %s adicionado ao carrinho!\n", quantidade, nome);
}

/*
    Função que exibe todos os produtos no carrinho de compras.

    @returns total_carrinho: Preço total da compra.
*/
double exibir_carrinho() {
    FILE *file = fopen("carrinho.txt", "r");
    if (file == NULL) {
        printf("Carrinho vazio!\n");
        return 0;
    }

    printf("\n\t\t--- SEU CARRINHO DE COMPRAS ---\n\n");
    char linha[200];
    int item_count = 0;
    double total_carrinho = 0.0;

    printf("%-5s %-30s %-10s %-10s %-10s\n", "Cod.", "Nome", "Preço Unit.", "Qtd", "Subtotal");
    printf("-------------------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = '\0'; 
        if (strlen(linha) == 0) continue;

        CarrinhoItem item;
        char *token;
        char temp_line[200]; 
        strcpy(temp_line, linha);

        token = strtok(temp_line, ";");

        if (token) 
            item.codigo = atoi(token); 
        else 
            continue;

        token = strtok(NULL, ";");

        if (token) 
            strcpy(item.nome, token); 
        else 
            continue;

        token = strtok(NULL, ";");

        if (token) 
            item.quantidade = atoi(token); 
        else 
            continue;

        token = strtok(NULL, ";");

        if (token) 
            item.preco_unitario = atof(token); 
        else 
            continue;
        
        double subtotal = item.quantidade * item.preco_unitario;
        total_carrinho += subtotal;
        item_count++;

        printf("%-5d %-30s R$%-9.2f %-10d R$%-9.2f\n", item.codigo, item.nome, item.preco_unitario, item.quantidade, subtotal);
    }
    printf("-------------------------------------------------------------------\n");
    printf("Total do Carrinho: R$%.2f\n", total_carrinho);
    printf("-------------------------------------------------------------------\n");
    
    fclose(file);
    if (item_count == 0) {
        printf("O carrinho está vazio!\n");
    }

    return total_carrinho;
}

/*
    Procedimento que remove ou diminui a quantidade de produtos do carrinho!
    Além disso, atualiza a quantidade em products.txt.
*/
void remover_produto() {
    int car_tam = 0;
    CarrinhoItem* car_item = NULL;
    int capacidade = 2; 
    car_item = malloc(capacidade * sizeof(CarrinhoItem));
    if (car_item == NULL) {
        perror("Erro ao alocar memória para itens do carrinho!");
        return;
    }

    FILE *file = fopen("carrinho.txt", "r");
    if (file == NULL) {
        printf("O carrinho esta vazio!\n");
        free(car_item);
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) == 0) continue;

        if (car_tam == capacidade) {
            capacidade *= 2;
            CarrinhoItem *temp = realloc(car_item, capacidade * sizeof(CarrinhoItem));
            if (temp == NULL) {
                perror("Erro ao realocar memoria para itens do carrinho!");
                free(car_item);
                fclose(file);
                return;
            }
            car_item = temp;
        }

        char *token;
        char temp_line[200];
        strcpy(temp_line, linha);

        token = strtok(temp_line, ";");

        if (token) 
            car_item[car_tam].codigo = atoi(token); 
        else 
            continue;

        token = strtok(NULL, ";");

        if (token)
            strcpy(car_item[car_tam].nome, token); 
        else 
            continue;

        token = strtok(NULL, ";");

        if (token) 
            car_item[car_tam].quantidade = atoi(token); 
        else 
            continue;

        token = strtok(NULL, ";");

        if (token) 
            car_item[car_tam].preco_unitario = atof(token); 
        else 
            continue;

        car_tam++;
    }
    fclose(file);

    if (car_tam == 0) {
        printf("O carrinho está vazio!\n");
        free(car_item);
        return;
    }

    int codigo_remover;
    printf("\nDigite o código do produto que deseja remover ou diminuir a quantidade (-1 para cancelar):\n> ");
    scanf("%d", &codigo_remover);

    if (codigo_remover == -1) {
        printf("Remoção cancelada.\n");
        free(car_item);
        return;
    }

    int item_index = -1;
    for (int i = 0; i < car_tam; i++) {
        if (car_item[i].codigo == codigo_remover) {
            item_index = i;
            break;
        }
    }

    if (item_index == -1) {
        printf("Produto com código %d não encontrado no carrinho!\n", codigo_remover);
        free(car_item);
        return;
    }

    int devolver_quantidade; 
    printf("%s encontrado.\n", car_item[item_index].nome);
    printf("Quantas unidades deseja remover do carrinho? (0 para remover todo o item):\n> ");
    scanf("%d", &devolver_quantidade);

    if (devolver_quantidade < 0) {
        printf("Quantidade inválida. Operação cancelada.\n");
        free(car_item);
        return;
    }

    if (devolver_quantidade >= car_item[item_index].quantidade || devolver_quantidade == 0) {
        int qtd_original = car_item[item_index].quantidade;
        
        for (int i = item_index; i < car_tam - 1; i++) {
            car_item[i] = car_item[i+1];
        }
        car_tam--; 
        printf("{%s} totalmente removido do carrinho.\n", car_item[item_index].nome);
        
        atualizar_estoque(codigo_remover, qtd_original); 
    } else {
        car_item[item_index].quantidade -= devolver_quantidade;
        printf("%d unidades de {%s} removidas do carrinho. Restam %d.\n", 
               devolver_quantidade, car_item[item_index].nome, car_item[item_index].quantidade);
        
        atualizar_estoque(codigo_remover, devolver_quantidade);
    }

    
    file = fopen("carrinho.txt", "w"); 
    if (file == NULL) {
        perror("Erro ao reescrever o arquivo de carrinho!");
        free(car_item);
        return;
    }

    for (int i = 0; i < car_tam; i++) {
        fprintf(file, "%d;%s;%d;%.2f\n", car_item[i].codigo, car_item[i].nome, 
                car_item[i].quantidade, car_item[i].preco_unitario);
    }
    fclose(file);
    free(car_item);
    printf("Carrinho atualizado com sucesso!\n");
}

/*
    Função para finalizar ou remover produto do carrinho.
    O programa retorna 1 se o usuário realizou o pagamento.
*/

int finalizar_compra(){



    double total = exibir_carrinho();
    
    if (total == 0)
        return 0;

    int escolha;
    printf("\n\nVoce deseja\n[1] Realizar o pagamento\n[2] Remover produto\n[3] Voltar> ");
    scanf("%d", &escolha);

    if (escolha == 3)
        return 0;

    while (escolha <= 1 && escolha >= 2){
        printf("\nPor favor, digite uma das opções válidas:\n> ");
        scanf("%d", &escolha);
    }

    if (escolha == 1){
        double valor_pago;

        printf("\nValor total R$ %.2f.\nDigite o valor a ser pago:\n> ", total);
        scanf("%lf", &valor_pago);

        double troco = devolve_troco(valor_pago, total);

        while (troco == -1){
            printf("\nDigite um valor valido:\n> ");
            scanf("%lf", &valor_pago);
            troco = devolve_troco(valor_pago, total);
        }
        
        system("clear");

        printf("\nProcessando o pagamento...\n");

        printf("O seu troco foi de R$ %.2f.\nVolte sempre!!\n\n", troco);
        return 1;
    }
    else
        remover_produto();
}

/*
    Procedimento para adicionar quantidades de um produto no modo administrador!
*/
void adicionar_quantidade_estoque_admin() {
    system("clear");
    printf("\n\t\t--- ADICIONAR QUANTIDADE AO ESTOQUE ---\n");

    int qtd_total_produtos = 0;
    struct Produto* produtos = loadProducts(&qtd_total_produtos); 

    if (produtos == NULL || qtd_total_produtos == 0) {
        printf("Nenhum produto cadastrado no sistema!\n");
        if (produtos != NULL) free(produtos);
        return;
    }

    int codigo_produto;
    printf("Digite o codigo do produto para adicionar estoque:\n> ");
    scanf("%d", &codigo_produto);

    struct Produto produto_encontrado = buscar_produto_por_codigo(produtos, qtd_total_produtos, codigo_produto);
    free(produtos); 

    if (produto_encontrado.codigo == -1) {
        printf("Produto com codigo %d nao encontrado.\n", codigo_produto);
        return;
    }

    int quantidade_a_adicionar;
    printf("Produto encontrado: {%s} (Estoque atual: %d)\n", produto_encontrado.nome, produto_encontrado.quantidade);
    printf("Digite a quantidade a ser adicionada ao estoque:\n> ");
    scanf("%d", &quantidade_a_adicionar);

    if (quantidade_a_adicionar <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    atualizar_estoque(codigo_produto, quantidade_a_adicionar);
    printf("Estoque do produto {%s} (codigo %d) atualizado. Quantidade adicionada: %d.\n", produto_encontrado.nome, codigo_produto, quantidade_a_adicionar);
}

/*  
    Procedimento que permite ao administrador remover uma quantidade do estoque de um produto existente,
    ou remover o produto completamente.
*/
void remover_quantidade_estoque_admin() {
    system("clear");
    printf("\n\t\t--- REMOVER QUANTIDADE DO ESTOQUE ---\n");

    int qtd_total_produtos = 0;
    struct Produto* produtos = loadProducts(&qtd_total_produtos); 

    if (produtos == NULL || qtd_total_produtos == 0) {
        printf("Nenhum produto cadastrado no sistema!\n");
        if (produtos != NULL) free(produtos);
        return;
    }

    int codigo_produto;
    printf("Digite o codigo do produto para remover do estoque (ou -1 para cancelar):\n> ");
    scanf("%d", &codigo_produto);

    if (codigo_produto == -1) {
        printf("Operacao cancelada!\n");
        free(produtos);
        return;
    }

    struct Produto produto_encontrado = buscar_produto_por_codigo(produtos, qtd_total_produtos, codigo_produto);

    if (produto_encontrado.codigo == -1) {
        printf("Produto com codigo %d nao encontrado!\n", codigo_produto);
        free(produtos);
        return;
    }

    int quantidade_a_remover;
    printf("Produto encontrado: %s (quantidade atual: %d)\n", produto_encontrado.nome, produto_encontrado.quantidade);
    printf("Quantas unidades deseja remover? (0 para remover todo o produto):\n> ");
    scanf("%d", &quantidade_a_remover);

    if (quantidade_a_remover < 0) {
        printf("Quantidade invalida!\n");
        free(produtos);
        return;
    }

    if (quantidade_a_remover == 0 || quantidade_a_remover >= produto_encontrado.quantidade) {
        printf("Removendo {%s} (codigo %d) completamente do estoque!\n", produto_encontrado.nome, codigo_produto);
        
        FILE *file = fopen("products.txt", "w"); 
        if (file == NULL) {
            perror("Erro ao reescrever o arquivo products.txt");
            free(produtos);
            return;
        }

        for (int i = 0; i < qtd_total_produtos; i++) {
            if (produtos[i].codigo != codigo_produto) { 
                fprintf(file, "%s;%.2lf;%d;%d\n", produtos[i].nome, produtos[i].preco, 
                        produtos[i].quantidade, produtos[i].codigo);
            }
        }
        fclose(file);
        printf("{%s} removido do estoque.\n", produto_encontrado.nome);

    } else {
        atualizar_estoque(codigo_produto, -quantidade_a_remover); 
        printf("Estoque do produto {%s} atualizado. Quantidade removida: %d.\n", produto_encontrado.nome, quantidade_a_remover);
    }
    
    free(produtos); 
}

/*
    Função que salva um usuário

    @param usuario: Container que contém as informações do usuário que será adicionado.
*/
void saveUser(struct User usuario) {
    FILE *file = fopen(".//users.txt", "a");
    if (file == NULL) {
        file = fopen(".//users.txt", "w");
        if (file == NULL) {
            perror("Erro ao criar arquivo de usuarios!");
            return;
        }
    }

    fprintf(file, "%s;%s;%d\n", usuario.login, usuario.password, usuario.userID);
    printf("Usuario {%s} foi salvo no banco de dados!\n", usuario.login);
    fclose(file);
}

// Carrega todos os usuários do arquivo
struct User* loadUsers(int *n) {
    FILE *file = fopen(".//users.txt", "r");
    if (file == NULL) {
        *n = 0;
        return NULL;
    }

    int capacidade = 4;
    struct User *usuarios = malloc(capacidade * sizeof(struct User));
    if (usuarios == NULL) {
        perror("Erro de memoria ao carregar usuarios!");
        return NULL;
    }

    char linha[150];
    int i = 0;

    while (fgets(linha, sizeof(linha), file)) {
        if (i == capacidade) {
            capacidade *= 2;
            struct User *temp = realloc(usuarios, capacidade * sizeof(struct User));
            if (temp == NULL) {
                perror("Erro ao realocar usuarios!");
                free(usuarios);
                fclose(file);
                return NULL;
            }
            usuarios = temp;
        }

        linha[strcspn(linha, "\n")] = '\0';
        char *login = strtok(linha, ";");
        char *senha = strtok(NULL, ";");
        char *id = strtok(NULL, ";");

        if (login && senha && id) {
            strcpy(usuarios[i].login, login);
            strcpy(usuarios[i].password, senha);
            sscanf(id, "%d", &usuarios[i].userID);
            i++;
        }
    }

    fclose(file);
    *n = i;
    return usuarios;
}

// Cria e adiciona um novo usuário
void adicionar_usuario() {
    char login[100];
    char senha[20];

    getchar();
    printf("Digite o login do novo usuario: ");
    fgets(login, sizeof login, stdin);
    login[strcspn(login, "\n")] = '\0';

    printf("Digite a senha: ");
    fgets(senha, sizeof senha, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    struct User novo = novo_usuario(login, senha);
    saveUser(novo);
}

// Edita senha de um usuário já existente
void editar_usuario() {
    int qtd;
    struct User *usuarios = loadUsers(&qtd);
    if (usuarios == NULL || qtd == 0) {
        printf("Nenhum usuário encontrado!\n");
        return;
    }

    printf("Usuários encontrados:\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] Login: %s | ID: %d\n", i, usuarios[i].login, usuarios[i].userID);
    }

    printf("Digite o numero do usuario que deseja editar: ");
    int escolha;
    scanf("%d", &escolha);
    getchar();

    if (escolha < 0 || escolha >= qtd) {
        printf("Usuario invalido!\n");
        free(usuarios);
        return;
    }

    printf("Digite a nova senha para o usuario %s: ", usuarios[escolha].login);
    fgets(usuarios[escolha].password, sizeof(usuarios[escolha].password), stdin);
    usuarios[escolha].password[strcspn(usuarios[escolha].password, "\n")] = '\0';

    // Sobrescreve o arquivo com todos os usuários atualizados
    FILE *file = fopen(".//users.txt", "w");
    if (file == NULL) {
        perror("Erro ao reescrever usuarios!");
        free(usuarios);
        return;
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(file, "%s;%s;%d\n", usuarios[i].login, usuarios[i].password, usuarios[i].userID);
    }

    fclose(file);
    printf("Senha atualizada com sucesso!\n");
    free(usuarios);
}

/*
    Função que edita qualquer informação de um produto desejado

    @param qtd: Parâmetro que indica a quantidade total de produtos.
*/

void editar_produto(int *qtd) {

    struct Produto* produtos = loadProducts(qtd);
    while (1) {
        printf("Cod.##Nome do Produto\n");
        for (int i = 0; i < *qtd; i++) {
            printf("%d##%s\n", produtos[i].codigo, produtos[i].nome);
        }

        printf("Digite o codigo do produto que voce deseja alterar: ");
        int edit_product_code;
        scanf("%d", &edit_product_code);
        struct Produto edit_product = buscar_produto_por_codigo(produtos, *qtd, edit_product_code);
        printf("---- Informacoes do Produto a ser Editado ----\n");
        printf("Nome | Preco ");
        printf("%s | %.2lf \n", edit_product.nome, edit_product.preco);
        printf("-----------------------------------\n");
        while (1) {
            printf("Informe qual informacao voce deseja alterar:\n[1] Nome\t[2] Preco\n");
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                char new_name[50];
                printf("Digite o novo nome do produto: ");
                getchar();
                fgets(new_name, sizeof(new_name), stdin);
                new_name[strcspn(new_name, "\n")] = '\0';
                strcpy(edit_product.nome, new_name);
                printf("Nome alterado com sucesso!\n");
            } else if (choice == 2) {
                double new_price;
                printf("Digite o novo preco do produto: ");
                scanf("%lf", &new_price);
                edit_product.preco = new_price;
                printf("Preço alterado com sucesso!\n");
            } else {
                printf("Escolha uma opcao valida!");
                continue;
            }

            printf("Voce deseja alterar alguma outra informacao? [1] S / [2] N\n");
            int choice_2;
            scanf("%d", &choice_2);
            if (choice_2 == 1) {
                continue;
            } else {
                break;
            }
        }
        for (int j = 0; j < *qtd; j++) {
            if (produtos[j].codigo == edit_product.codigo) {
                strcpy(produtos[j].nome, edit_product.nome);
                produtos[j].preco = edit_product.preco;
                break;
            }
        }
        printf("Voce deseja alterar a informacao de algum outro produto? [1] S / [2] N\n");
        int choice_3;
        scanf("%d", &choice_3);
        if (choice_3 == 1) {
            continue;
        } else {
            FILE *reset = fopen(".\\products.txt", "w");
            if (reset == NULL) {
                perror("Erro ao iniciar arquivo");
            }
            fprintf(reset, "");
            fclose(reset);
            
            for (int h = 0; h < *qtd; h++) {
                saveProduct(produtos[h]);
            }
            printf("Alteracoes salvas com sucesso!");
            break;
        }
    }
}