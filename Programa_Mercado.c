#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//simular carregamento na abertura do programa(nao essencial ao programa)
void carregando()
{
	int x, carregado = 0;

	while ( carregado != 106) {
    	system("clear");
    	printf("\tBEM VINDO!");
    	if (carregado <= 100) printf("\n\n\nCarregando: %d / 100.\n", carregado);
    	   else printf("\n\n\nCarregando: 100 / 100.\n");

        while (1) {
			if ( carregado < 90 ) x = rand() % 5000000;
			   else x = rand() % 18000000;
			if (x == 1){
				carregado++;
				break;
			}
        }
    }

}

//estrutura para dados dos produtos
typedef struct{
    int id;
    char nome[51];
    float preco;
} produto;

//funcao para ler os produtos ja cadastrados do arquivo
produto* ler_lista_produtos_txt (produto *vetor, int *n)
{
    int i = 0;
	produto auxiliar;

	FILE *f = fopen("ProdutosCadastrados.txt", "r");

	//caso arquivo nao exista cria um novo arquivo
	if (f == 0) {
		FILE *f = fopen("ProdutosCadastrados.txt", "w");
        f = f;
		return vetor;
	}

	while(fscanf(f, "%d\n%[^\n]\n%f\n", &auxiliar.id, auxiliar.nome, &auxiliar.preco) == 3) {

		//alocar memoria para ler os dados do arquivo
    	if ((*n) == 0) {
    		vetor = (produto*) malloc(sizeof(produto));
            if(vetor == 0) printf("Erro no malloc");
    	}	else {
    			vetor = (produto*) realloc(vetor, ((*n)+1) * sizeof(produto));
    			if(vetor == 0) printf("Erro no realloc");
    		}

		//copiar os dados do arquivo para os vetores
		vetor[i] = auxiliar;
    	i++;
    	(*n)++;
    }

	return vetor;
}

//funcao para passar os produtos no arquivo
void produto_para_arquivo(produto vetor[], int n)
{
	FILE *f = fopen("ProdutosCadastrados.txt", "w");
	int i;

	if (f == 0) {
      printf("** ERRO, Arquivo Inacessível! **");
	}

    for( i = 0; i < n; i++) {
		fprintf(f, "%d\n%s\n%f\n", vetor[i].id, vetor[i].nome, vetor[i].preco);
	}

	fclose(f);
}

//funcao para cadastra produto
produto* cadastra_produto (produto *p, int *n)
{
	system("clear");

	int i;
	produto auxiliar;
    printf("\t--CADASTRO DO PRODUTO--\n\n");
    printf("Insira a ID: ");
	scanf(" %d", &auxiliar.id);

	//impede que cadastre 2 produtos com o mesmo id
	for (i = 0; i < (*n); i++) {
		if (auxiliar.id == p[i].id) {
			printf("\n-----------------------\n");
			printf("Código ID já cadastrado!\n");
			printf("-----------------------\n");
			printf("\nPrecione ENTER para voltar\n");
			getchar();
			getchar();
			return p;
		}
	}

	printf("Insira o nome: ");
	scanf(" %50[^\n]", auxiliar.nome);
	printf("Insira o preco: ");
	scanf(" %f", &auxiliar.preco);

	//aloca memoria para escrever o produto
	if ((*n) == 0) {
		p = (produto *) malloc(sizeof(produto));
		(*n)++;
	}	else {
			p = (produto *) realloc(p, ((*n)+1) * sizeof(produto) );
			(*n)++;
			if(p == 0){
				printf("Erro no Realloc");
				return 0;
			}
		}

	p[(*n) - 1] = auxiliar;
	//atualiza o arquivo com o produto cadastrado
	produto_para_arquivo(p, (*n));

	return p;
}

//funcao para atualizar produto
void atualiza_produto (produto *p, int *n)
{
	 system("clear");
	 system("clear");

	 //caso o arquivo nao tenha nenhum produto cadastrado
	 if ((*n) == 0) {
		printf("--------------------------\n");
		printf("Nenhum Produto Registrado!");
		printf("\n--------------------------\n");
		printf("\nPrecione ENTER para voltar\n");
		getchar();
		getchar();
		return ;
	 }

	int i, aux, cont = 0;
	system("clear");
	system("clear");
    printf("Insira o Código ID do Produto: ");
    scanf("%d", &aux);

	for(i = 0; i < (*n); i++){
		//acha o produto pesquisado
		if (aux == p[i].id) {
            printf(" Nome: %s\n", p[i].nome );
    		printf(" Preco: RS %.2f\n", p[i].preco);
            printf("\nInsira o novo Nome do Produto: ");
            scanf("\n%50[^\n]", p[i].nome);
            printf("Insira o novo Preço do Produto: ");
    		scanf("%f", &p[i].preco);
    		cont++; //contador para testar se o id pesquisado existe
    	}
    }

	//atualiza os dados do produto no arquivo
    produto_para_arquivo(p, (*n));

    if (cont == 0) {
			printf("\n-----------------------\n");
			printf("Produto não Encontrado!\n");
	}	else {
		printf("\n-----------------------\n");
		printf("  Produto Atualizado!\n");
		}
    printf("-----------------------\n");
	printf("\nPrecione ENTER para voltar\n");
	getchar();
	getchar();
}

//funcao para remover produto
produto* remove_produto(produto *p, int *n)
 {
     system("clear");
	 system("clear");

	//caso o arquivo nao tenha nenhum produto cadastrado
	 if ((*n) == 0) {
		printf("--------------------------\n");
 		printf("Nenhum Produto Registrado!");
 		printf("\n--------------------------\n");
		printf("\nPrecione ENTER para voltar\n");
		getchar();
		getchar();
		return (p);
	 }

     int i, aux, cont = 0;
     printf("Insira o Código ID do Produto: ");
     scanf("%d", &aux);
     for (i = 0; i < (*n); i++) {
		 //acha o produto pesquisado
         if (aux == p[i].id) {
             printf(" Nome: %s\n", p[i].nome );
     		 printf(" Preco: RS %.2f\n", p[i].preco);
             p[i] = p[(*n) - 1];
             p = (produto*) realloc(p, (*n-1) * sizeof(produto));
             cont++; //contador para testar se o id pesquisado existe
         }
    }

    if (cont == 0) {
			printf("\n-----------------------\n");
			printf("Produto não Encontrado!\n");
	}	else {
		printf("\n-----------------------\n");
		printf("  Produto Removido!\n");
		}
    printf("-----------------------\n");
 	printf("\nPrecione ENTER para voltar\n");
 	getchar();
 	getchar();
    (*n)--;

	//remove os dados do produto no arquivo
    produto_para_arquivo(p, (*n));

     return (p);
}

//funcao para consultar produto
void consulta_produto (produto *p, int *n)
{

	int i, aux, cont = 0;
	system("clear");
	system("clear");

	//caso o arquivo nao tenha nenhum produto cadastrado
	if ((*n) == 0) {
		printf("--------------------------\n");
		printf("Nenhum Produto Registrado!");
		printf("\n--------------------------\n");
		printf("\nPrecione ENTER para voltar\n");
		getchar();
		getchar();
		return;
	}

    printf("Insira o Código ID do Produto: ");
    scanf("%d", &aux);

	for(i = 0; i < (*n); i++){
		//acha o produto pesquisado
		if (aux == p[i].id) {
            printf(" Nome: %s\n", p[i].nome );
    		printf(" Preco: RS %.2f\n", p[i].preco);
    		cont++; //contador para testar se o id pesquisado existe
        }
    }

    if (cont == 0) {
			printf("\n-----------------------\n");
			printf("Produto não Encontrado!\n");
	}

    printf("-----------------------\n");
	printf("\nPrecione ENTER para voltar\n");
	getchar();
	getchar();
}

//funcao para imprimir todos os produtos cadastrados
void imprime_produtos (produto *p, int *n)
{
	int i, j;
	system("clear");
	system("clear");

	//caso o arquivo nao tenha nenhum produto cadastrado
	if ((*n) == 0) {
		printf("--------------------------\n");
		printf("Nenhum Produto Registrado!");
		printf("\n--------------------------\n");
		printf("\nPrecione ENTER para voltar\n");
		getchar();
		getchar();
		return;
	}

	//organiza os produtos por ordem crescente de id
	produto aux;
	for(i = 0; i < (*n); i++) {
		for(j = 1; j < (*n); j++) {
			if (p[j].id < p[j-1].id) {
				aux = p[j-1];
				p[j-1] = p[j];
				p[j] = aux;
			}
		}
	}

	//imprime todos os produtos cadastrados
	printf("\t--LISTA DE PRODUTOS--\n\n--------------------------\n");
	for(i = 0; i < (*n); i++){
        		printf(" Id: %d\n", p[i].id);
        		printf(" Nome: %s\n", p[i].nome );
        		printf(" Preco: RS %.2f\n", p[i].preco);
        		printf("-----------------------\n");
    }

	printf("\nPrecione ENTER para voltar\n");
	getchar();
	getchar();
}

//funcao para imprimir o menu principal
void menu_principal ()
{
	system("clear");
	system("clear");
	printf("\t--MENU INICIAL--\t%s\n\n", __DATE__);
	printf(" [1] - Controle de Produtos.\n");
	printf(" [2] - Iniciar Compra.\n");
	printf(" [3] - Imprimir Relatorio de Vendas.\n");
	printf(" [9] - Encerrar Programa.\n");
	printf("\nO que deseja? ");
}

//funcao para imprimir o menu de produtos
void menu_produtos ()
{
	system("clear");
	system("clear");
	printf("\t--CONTROLE DE PRODUTOS--\t%s\n\n", __DATE__);
	printf(" [1] - Cadastrar Produto.\n");
	printf(" [2] - Atualizar Produto.\n");
	printf(" [3] - Remover Produto.\n");
	printf(" [4] - Consultar Produto.\n");
	printf(" [5] - Verificar Produtos Cadastrados.\n");
	printf(" [9] - Retornar ao Menu Inicial.\n");
	printf("\nO que deseja? ");
}

//funcao para imprimir funcionalidades ainda nao implementadas
void em_construcao()
{
	system("clear");
	system("clear");
	printf("----------------------------\n");
	printf("--Área em Desenvolvimento--");
	printf("\n----------------------------\n");
	printf("\nPrecione ENTER para voltar\n");
	getchar();
	getchar();
}

//funcao principal
int main()
{
	int opcao, qtd = 0;
	produto *mercadoria = 0;

    //carregando(); //nao estou utilizando devido ao tempo de espera que a funcao adiciona

	//le os dados do arquivo
	mercadoria = ler_lista_produtos_txt(mercadoria, &qtd);

	while (1) {
		system("clear");
    	menu_principal();
    	scanf("%d", &opcao);

    	switch (opcao) { //opcoes do menu principal
			case 1 :
				while (1) {
					system("clear");
					menu_produtos();
					scanf("%d", &opcao);

					switch (opcao) { //opcoes do menu de produtos

			    		case 1 :
			    			mercadoria = cadastra_produto(mercadoria, &qtd);
			    			break;

			            case 2 :
			        		atualiza_produto(mercadoria, &qtd);
			        		break;

			            case 3 :
			            	mercadoria = remove_produto(mercadoria, &qtd);
			            	break;

			            case 4 :
			        		consulta_produto(mercadoria, &qtd);
			        		break;

			    		case 5 :
			    			imprime_produtos(mercadoria, &qtd);
			    			break;

						case 9 :
							system("clear");
							//vai fazer o programa carregar novamente, nao acho q seja uma boa opçao
							//pensar em uma alternativa
							return main();
				    		break;

						default:
					    	system("clear");
					    	printf("\nOpção Inválida!\n");
					    	printf("\nPrecione ENTER para voltar\n");
					    	getchar();
					    	getchar();

					}
				}

			case 2 :
				system("clear");
				em_construcao();
				break;

			case 3 :
				system("clear");
				em_construcao();
				break;

    		case 9 :
				system("clear");
    			printf("Volte sempre!\n");
    			return 0;
    			break;

    		default:
	    		system("clear");
	    		printf("\nOpção Inválida!\n");
	    		printf("\nPrecione ENTER para voltar\n");
	    		getchar();
	    		getchar();

    	}
    }

    return 0;
}