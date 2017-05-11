/************************************************************************************************************                                                             
********AUTHOR: GABRIEL PEREIRA DA CRUZ***E-MAIL:GABRIEL.CRUZ116@GMAIL.COM***WHATSAPP:(61)9 9324-4898****************
********CURSO: SISTEMAS DE INFORMAÇÃO*****IES: UNIVERSIDADE CATÓLICA DE BRASÍLIA - UCB*******************************
********SEMESTRE: 4° SEMESTRE 1/2017******DATA DA ÚLTIMA MODIFICAÇÃO:10/05/2017**************************************
*********************************************************************************************************************
********OBJETIVO: CONSTRUIR UM SOFTWARE DE GESTÃO DE UMA BIBLIOTECA**************************************************
********FUNÇÕES: CADASTRAR.: LIVROS, LEITORES; LISTAR.: LIVROS, LEITORES; REALIZAR E CONSULTAR EMPRÉSTIMOS*********** 
*********************************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TS 30
#define TV 15

//Estrutras De Leitores
typedef struct Leitor{
	char nome[TS];
	int matricula;
}Leitor;

typedef struct NoLeitor{
	struct Leitor data;
	struct NoLeitor *prox;
}NoLeitor;

//Estrutras De Livros
typedef struct Livro {
	char nome[TS];
	int codLivro;
}Livro;

typedef struct NoLivro{
	struct Livro data;
	struct NoLivro *prox;
}NoLivro;

//Estrutras De Empréstimos
typedef struct Emprestimo{
	int codigo;
	int codigoLivro;
	char livroEmp[TS];
	int matricula;
	char leitor[TS];
}Emprestimo;

typedef struct NoEmprestimo{
	struct Emprestimo data;
	struct NoEmprestimo *prox;
}NoEmprestimo;


//Declaração de Protótipos das Funções
//====================================================================================================================//

// Desenhar Cabeçalho Do Sistema
void desenhaCabecalho(void);

//Cadastrar Leitor
struct Leitor recolheDadosLeitor(int *matricula);
void cadastraLeitor(struct NoLeitor  *novoLeitor, struct NoLeitor  *listaDeLeitores,  struct Leitor dadosLeitor);

//Cadastrar Livro
struct Livro recolheDadosLivro(int *codLivro);
void cadastraLivro(struct NoLivro  *novoLivro, struct NoLivro  *listaDeLivros, struct Livro dadosLivro);

//Realizar Emprestimo
struct Emprestimo recolheDadosEmprestimo(struct NoLeitor *listaDeLeitores, struct NoLivro *listaDeLivros);

char *retornaNome(struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitor, int matricula, int codLivro, int op);

void realizarEmprestimo(struct NoEmprestimo *listaDeEmprestimos,  struct Emprestimo dadosEmprestimo, int* codEmp);

void consultarEmprestimos(struct Emprestimo emprestimo[], int cEm);

//Listar Livros
//void listarLivros(struct Livro livro[], int ppli);
//Listar Leitores
void listarLivros(struct NoLivro *listaDeLivros);

//====================================================================================================================//

int main(void){
	
	//Declaração de variáveis primitivas
	   //Cont Cod Emprestimo  - Cont Matrícula - Cont Cod Livro - Variável Para Recolher Opção do Usuário 
	int  codEmp=1, 				matricula=1,     codLivro=1,      op=0;
	
	//Declaração de variáveis Personalizadas
	struct NoLeitor     *listaDeLeitores    = NULL, *novoLeitor     = NULL, *auxLeitor;
	struct NoLivro      *listaDeLivros      = NULL, *novoLivro      = NULL, *auxLivro;
	struct NoEmprestimo *listaDeEmprestimos = NULL, *novoEmprestimo = NULL;
	
	//Início do Ciclo DoWhile do Programa	
	do{	
		system("cls");
		desenhaCabecalho();//Chama a função que desenha o cabeçalho
		
		printf("1-CADASTRAR LEITOR    3-REALIZAR EMPRESTIMO     5-LISTAR LIVROS     7-ALTERA   9-SAIR\n");
		printf("2-CADASTRAR LIVRO     4-CONSULTAR EMPRESTIMOS   6-LISTAR LEITORES   8-EXCLUI\n\nOPCAO:");
		scanf("%i",&op);
		
		if(op==9)break;//Analisa se o usuário deseja finalizar o programa.
		
		else{// Caso não deseje, dá procedimento ao programa
		
			switch(op){
				case 1:
					
					system("cls");//limpa a Tela
					
					if((novoLeitor = (NoLeitor*) malloc(sizeof(struct NoLeitor))) == NULL){//Analiza Se Foi Alocado Corretamente Um Espaço Para O Novo Leitor  
						printf(" TEMOS UM NUMERO MUITO GRANDE DE LEITORES!\nPOR FAVOR, VOLTE MES QUE VEM!");
						system("pause");//Pausa o Sistema
					}else{
						cadastraLeitor(novoLeitor, listaDeLeitores, recolheDadosLeitor(&matricula));
						desenhaCabecalho();
						printf("CADASTRO DE LEITOR-\n");
						printf("-------------------\n\n");
						fflush(stdin);
						printf(" LEITOR                         MATRICULA\n");
						printf(" ------------------------------ ---------\n");
						printf(" %30s %9.09i\n\n\n",novoLeitor->data.nome, novoLeitor->data.matricula);
						system("pause");//Pausa o Sistema
					}
				break;
					
				case 2:
					system("cls");//limpa a Telas
					if((novoLivro = (NoLivro*) malloc(sizeof(struct NoLivro))) == NULL){//Analiza Se Foi Alocado Corretamente Um Espaço Para O Novo Livro 
						printf(" ESTOQUE MUITO CHEIO!\nPOR FAVOR, ESPERE AUMENTAR-MOS NOSSA ESTRUTURA!");
						system("pause");//Pausa o Sistema						
					}else{
						cadastraLivro(novoLivro, listaDeLivros, recolheDadosLivro(&codLivro));
						desenhaCabecalho();
						printf("CADASTRO DE LIVRO-\n");
						printf("-------------------\n\n");
						printf(" LIVRO CADASTRADO COM SUCESSO!\n\n");
						fflush(stdin);
						printf(" LIVRO                          COD.LIVRO\n");
						printf(" ------------------------------ ---------\n");
						printf(" %30s %9.09i\n\n\n",novoLivro->data.nome, novoLivro->data.codLivro);
						system("pause");//Pausa o Sistema.
					}
				break;
					
				case 3:
					system("cls");//lIMPA A TELA.
					if((listaDeLivros == NULL)||(listaDeLeitores == NULL)){
						desenhaCabecalho();
						printf("---ERRO: IMPOSSIVEL REALIZAR EMPRESTIMO---\n\n\n");
						printf(" O ERRO PODE SER CAUSADO POR:\n\n");
						printf("   1)FALTA DE ALUNOS CONSTANDO NA BASE DE DADOS\n\n");
						printf("   2)FALTA DE LIVROS CONSTANDO NA BASE DE DADOS\n\n");
						printf(" OBS: CONSERTE O ERRO, E TENTE NOVAMENTE!\n");
						printf("\n\n");
						system("pause");//PAUSA O SISTEMA.					
					}else{
						realizarEmprestimo(listaDeEmprestimos, recolheDadosEmprestimo(listaDeLeitores, listaDeLivros), &codEmp );
					}
				break;
				/*
				case 4:
					system("cls");
					if(qtdEmp>0){
						consultarEmprestimos(emprestimo, qtdEmp);
						printf("\n\n");
						system("pause");
					}else{
						printf("erro");
						system("pause");
					}
					
				break;
				
				case 5:
					system("cls");
					if(ppli<1){
						desenhaCabecalho();
						printf("---ERRO: IMPOSSIVEL LISTAR LIVROS---\n\n\n");
						printf(" NENHUM LIVRO CADASTRADO ATE O MOMENTO!\n\n");
						printf("\n\n");
						system("pause");//PAUSA O SISTEMA.					
					}else{
						desenhaCabecalho();
						listarLivros(livro, ppli);
						system("pause");
					}
				break;
				
				case 6:
					system("cls");
					if(pple<1){
						desenhaCabecalho();
						printf("---ERRO: IMPOSSIVEL LISTAR LEITORES---\n\n\n");
						printf(" NENHUM LEITOR CADASTRADO ATE O MOMENTO!\n\n");
						printf("\n\n");
						system("pause");//PAUSA O SISTEMA.					
					}else{
						desenhaCabecalho();
						listarLeitores(leitor, pple);
						system("pause");
					}
					
				break;	
				case 7:
					system("cls");
										
				break;	
				case 8:
					
				break;	*/		
				default:
					system("cls");//lIMPA A TELA.
					printf("OPCAO INVALIDA. TENTE NOVAMENTE\n");//CASO O O USUÁRIO DIGITE UM NUMERO DIFERENTES DOS PRÉ-DEFINIDOS.
					system("pause");//Pausa o Sistema
				break;
			}	
		}
	}while(op!=9);	
	
	novoLeitor = listaDeLeitores;
	while(novoLeitor != NULL){
		auxLeitor = novoLeitor;
		novoLeitor = novoLeitor->prox; 
		free(auxLeitor);
	}
	
	novoLivro = listaDeLivros;
	while(novoLivro != NULL){
		auxLivro = novoLivro;
		novoLivro = novoLivro->prox; 
		free(auxLivro);
	}
	
	
	return 0;
}

void desenhaCabecalho(void){// FUNÇÃO PARA DESENHAR O CABEÇALHO DO SISTEMA.
	printf("---------------------------------------------------------------------------------------\n");
	printf("-------------------------------SISTEMA DA BIBLIOTECA-----------------------------------\n");
	printf("---------------------------------------------------------------------------------------\n");
}

struct Leitor recolheDadosLeitor(int *matricula){
	struct Leitor leitor;
	fflush(stdin);//LIMPA O BUFFER DO TECLADO.
	desenhaCabecalho();
	printf("CADASTRO DE LEITOR-\n");
	printf("-------------------\n\n");
	printf(" DIGITE O NOME DO LEITOR:");
	fflush(stdin);
	fgets(leitor.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
	leitor.nome[strlen(leitor.nome) - 1] = '\0';
	leitor.matricula = *matricula;
	(*matricula)++;
	system("cls");	
	return leitor;
}

void cadastraLeitor(struct NoLeitor *novoLeitor, struct NoLeitor *listaDeLeitores, struct Leitor dadosLeitor){
	novoLeitor->data = dadosLeitor;
	novoLeitor->prox = listaDeLeitores;
	listaDeLeitores = novoLeitor;
}

struct Livro recolheDadosLivro(int *codLivro){
	struct Livro livro;
	fflush(stdin);//LIMPA O BUFFER DO TECLADO.
	desenhaCabecalho();
	printf("CADASTRO DE LIVRO-\n");
	printf("-------------------\n\n");
	printf(" DIGITE O NOME DO LIVRO:");
	fflush(stdin);
	fgets(livro.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
	livro.nome[strlen(livro.nome) - 1] = '\0';
	livro.codLivro = *codLivro;
	(*codLivro)++;
	system("cls");	
	return livro;
}

void cadastraLivro (struct NoLivro *novoLivro, struct NoLivro *listaDeLivros, struct Livro dadosLivro){
	novoLivro->data = dadosLivro;
	novoLivro->prox = listaDeLivros;//Todos os lugares que faço algo como isso DÁ WARNING
	listaDeLivros = novoLivro;
}

char *retornaNome(struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitores,int matricula,int codLivro,int op){
	
	struct NoLivro  *nomeLivroAtual;
	struct NoLeitor *nomeLeitorAtual;
	
	switch(op){
		case 1:
			nomeLivroAtual = listaDeLivros;
			while( (nomeLivroAtual->data.codLivro) != codLivro ){
				nomeLivroAtual = nomeLivroAtual->prox;
			}
		
			return nomeLivroAtual->data.nome;
		break;
		
		case 2:
			nomeLeitorAtual = listaDeLeitores;
			while( (nomeLeitorAtual->data.matricula) != matricula ){
				nomeLeitorAtual = nomeLeitorAtual->prox;
			}
			return nomeLeitorAtual->data.nome;
		break;
		
	}	
}

struct Emprestimo recolheDadosEmprestimo(struct NoLeitor *listaDeLeitores, struct NoLivro *listaDeLivros){
	struct Emprestimo dadosEmprestimo;
	fflush(stdin);//LIMPA O BUFFER DO TECLADO.
	desenhaCabecalho();
	
	printf("---EMPRESTIMO---\n\n");
	printf(" DIGITE SUA MATRICULA: ");
	scanf("%i",&dadosEmprestimo.matricula);
	
	strcpy(dadosEmprestimo.leitor, retornaNome(listaDeLivros, listaDeLeitores, (dadosEmprestimo.matricula), 0 ,2));
	
	system("cls");//PAUSA O SISTEMA.
	desenhaCabecalho();
	printf("---EMPRESTIMO---\n\n");
	listarLivros(listaDeLivros);
	
	printf(" DIGITE O CODIGO DO LIVRO: ");
	scanf("%i",&dadosEmprestimo.codigoLivro);
	
	strcpy(dadosEmprestimo.livroEmp , retornaNome(listaDeLivros, listaDeLeitores, 0, (dadosEmprestimo.codigoLivro) ,1)); 
	
	return dadosEmprestimo;
}

void realizarEmprestimo(struct NoEmprestimo *listaDeEmprestimos,  struct Emprestimo dadosEmprestimo, int* codEmp){
	
	listaDeEmprestimos->data = dadosEmprestimo;
	//emprestimo[(*qtdEmp)].matricula = dadosEmprestimo.matricula;
	//emprestimo[(*qtdEmp)].codigoLivro = dadosEmprestimo.codigoLivro;
	listaDeEmprestimos->data.codigo = *codEmp;
	//strcpy(emprestimo[(*qtdEmp)].livroEmp, livro[(dadosEmprestimo.codigoLivro - 1)].nome); 
	//strcpy(emprestimo[(*qtdEmp)].leitor, leitor[(dadosEmprestimo.matricula - 1)].nome); 
	(*codEmp)++;	
}

/* =============================================================================PAREI AQUI!!!!!!!!


void consultarEmprestimos(struct Emprestimo emprestimo[], int qtdEmp){
	int i;
	printf("\n\n-------------------------------CONSULTAR EMPRESTIMO-----------------------------------\n\n");
	printf(" COD                         LEITOR MATRICULA LIVRO                          COD.LIVRO\n");
	printf(" --- ------------------------------ --------- ------------------------------ ---------\n");
	for(i=0; i<qtdEmp; i++){
		printf(" %3.03i %30s %9.09i %30s %9.09i\n", emprestimo[i].codigo, emprestimo[i].leitor, emprestimo[i].matricula, emprestimo[i].livroEmp, emprestimo[i].codigoLivro);
	}
}
*/
void listarLivros(struct NoLivro *listaDeLivros){
	struct NoLivro *livroAtual;
	
	livroAtual = listaDeLivros;
	printf(" LIVRO                          COD.LIVRO\n");
	printf(" ------------------------------ ---------\n");
	while(livroAtual != NULL){
		printf(" %30s %9.09i\n\n\n",livroAtual->data.nome, livroAtual->data.codLivro);
		livroAtual = livroAtual->prox;
	}
	printf("\n\n");
}
/*
void listarLeitores(struct Leitor leitor[], int pple){
	int i;
	printf(" LEITOR                         MATRICULA\n");
	printf(" ------------------------------ ---------\n");
	for(i=0;i<pple;i++)
		printf(" %30s %9.09i\n",leitor[i].nome,leitor[i].matricula);
	
	printf("\n\n");
}
*/
