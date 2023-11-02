#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/include/mysql/mysql.h>

/* TODO */
/* - Carga dos dados a partir de um txt */
/* - Opcao para sair */ 

/* - Separar as operacoes em funcoes distintas */
/* - Proibir insercao de id repetido */
/* - Update dinamico */

/* - Interface Grafica (?) */

/* typedef struct produto{ */
/*     int id; */
/*     char nome[50]; */
/*     char categoria[50]; */
/*     double preco; */
/* }produto; */

/* int read(MYSQL *conn); */
/* int insert(produto, MYSQL *conn); */
/* int delete(int id, MYSQL *conn); */
/* int update(produto, MYSQL *conn); */

int main() {
	MYSQL *conn;
	
	MYSQL_RES *res;
	MYSQL_ROW row;
    MYSQL_FIELD *field;

	char *server = "localhost";
	char *user = "root";
	char *password = "Nobara38!";
	char *database = "loja";

    int input;
	
	conn = mysql_init(NULL);
	
    /* Conectando ao banco de dados */
    /* mysql_real_connect, se falhar ele retorna 0, e a condicao vira true pelo ! e imprime o erro */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
    while (true){   
        printf("--- SELECIONE UMA DAS OPCOES ---\n"); 
        printf("1- Select produtos\n");
        printf("2- Insert produtos\n");
        printf("3- Update produtos\n");
        printf("4- Delete produtos\n");
        printf("--------------------------------\n");
        scanf("%d",&input);

        switch (input){
            case 1:
                printf("-------LISTA DOS PRODUTOS-------\n");

                /* mysql_query retorna um valor diferente de 0 caso falhe */
                if (mysql_query(conn, "select * from produtos")) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    exit(1);
                }
               
                /* res pega o resultado da ultima query */
                res = mysql_store_result(conn);
                int num_fields = mysql_num_fields(res);
               
                while ((row = mysql_fetch_row(res)) != NULL){
                    for(int i = 0; i < num_fields; i++){
                        if(i == 0){
                            /* pega os metadados da coluna, imprime o header */ 
                            while(field = mysql_fetch_field(res)){
                                printf("%s ", field->name);
                            }
                            printf("\n");
                        }
                        /* operaror ternario (condition ? iftrue : iffalse) */
                        /* se row[i] existir imprime ela, se nao imprime NULL */
                        printf("%s ", row[i] ? row [i] : "NULL");
                    }
                }
                /* libera a memoria associada ao resultado */
                mysql_free_result(res);

                printf("\n--------------------------------\n");
                break;
            case 2:{
                printf("-----INSERINDO NOVO PRODUTO-----\n");
                char query[256];
                int id;
                char nome[50], categoria[50];
                double preco;
                printf("Digite o id: ");
                scanf("%d",&id);
                printf("Digite o nome: ");
                scanf("%s",nome);
                printf("Digite a categoria: ");
                scanf("%s",categoria);
                printf("Digite o preco: ");
                scanf("%lf",&preco);

                snprintf(query, sizeof(query), "INSERT INTO produtos (id, nome, categoria, preco) VALUES (%d, '%s', '%s', %lf)", id, nome, categoria, preco);

                if (mysql_real_query(conn, query, strlen(query)) != 0) {
                    fprintf(stderr, "Insertion failed: %s\n", mysql_error(conn));
                    exit(1);
                }
            }
                printf("\n--------------------------------\n");
                break;
            case 3:{
                printf("-----ATUALIZANDO UM PRODUTO-----\n");
                char query[200];
                int id, input;
                char nome[50], categoria[50];
                double preco;

                printf("Digite o id do item para atualizar: ");
                scanf("%d",&id);

                printf("Digite qual campo quer atualizar:\n");
                printf("1- Nome\n");
                printf("2- Categoria\n");
                printf("3- Preco\n");

                scanf("%d",&input);
                switch(input){
                    case 1:
                        printf("Digite o novo nome: ");
                        scanf("%s",nome);
                        snprintf(query, sizeof(query), "update produtos set nome = '%s' where id = %d ",nome,id);
                        break;
                    case 2:
                        printf("Digite a nova categoria: ");
                        scanf("%s",categoria);
                        snprintf(query, sizeof(query), "update produtos set categoria = '%s' where id = %d ",categoria,id);
                        break;
                    case 3:
                        printf("Digite o novo preco: ");
                        scanf("%lf",&preco);
                        snprintf(query, sizeof(query), "update produtos set preco = %lf where id = %d ",preco,id);
                        break;
                }

                if (mysql_real_query(conn, query, strlen(query)) != 0) {
                    fprintf(stderr, "Update failed: %s\n", mysql_error(conn));
                    exit(1);
                }
            }
                break;
            case 4:{
                printf("------REMOVENDO UM PRODUTO------\n");
                char query[200];
                int id;
                printf("Digite o id para deletar: ");
                scanf("%d",&id);
                snprintf(query, sizeof(query), "delete from produtos where id = %d",id);

                if (mysql_real_query(conn, query, strlen(query)) != 0) {
                    fprintf(stderr, "Insertion failed: %s\n", mysql_error(conn));
                    exit(1);
                }
                break;
            }
        }
    }
	/* fecha conexao */
	mysql_close(conn);
    return 0;
}

