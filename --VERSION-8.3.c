/*                                            
*	AUTHOR: GABRIEL PEREIRA DA CRUZ --- E-MAIL:gabriel.cruz116@gmail.com 	   --- WHATSAPP:(61)9 9583-0718
*	CURSO: SISTEMAS DE INFORMA��O   --- IES: UNIVERSIDADE CAT�LICA DE BRAS�LIA --- UCB
*	SEMESTRE: 4� SEMESTRE 1/2017    --- DATA DA �LTIMA MODIFICA��O:12/05/2017
*
*	OBJETIVO: CONSTRUIR UM SOFTWARE DE GEST�O DE UMA BIBLIOTECA
*
*	FUN��ES: CADASTRAR.: LIVROS - LEITORES - | LISTAR.: LIVROS - LEITORES | REALIZAR E CONSULTAR EMPR�STIMOS
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>//Biblioteca para configurar os caracteres latinos

#define TS 30

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

//Estrutras De Empr�stimos
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


//Declara��o de Prot�tipos das Fun��es
//====================================================================================================================//

// Desenhar Cabe�alho Do Sistema
void desenhaCabecalho(void);

//Cadastrar Leitor
struct Leitor recolheDadosLeitor(int *matricula);
void cadastraLeitor(struct NoLeitor  **novoLeitor, struct NoLeitor  **listaDeLeitores,  struct Leitor dadosLeitor);

//Cadastrar Livro
struct Livro recolheDadosLivro(int *codLivro);
void cadastraLivro(struct NoLivro  **novoLivro, struct NoLivro  **listaDeLivros, struct Livro dadosLivro);

//Realizar Emprestimo
struct Emprestimo recolheDadosEmprestimo(struct NoLeitor *listaDeLeitores, struct NoLivro *listaDeLivros, int *codEmp );
char *retornaNome(struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitor, int matricula, int codLivro, int op);
void realizarEmprestimo(struct NoEmprestimo **listaDeEmprestimos, struct NoEmprestimo **novoEmprestimo, struct Emprestimo dadosEmprestimo);

//Realizar Consulta
void realizarConsulta(struct NoEmprestimo *listaDeEmprestimos, struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitores, int indice);

//Listar Livros
void listarLivros(struct NoLivro *listaDeLivros);

//Listar Leitores
void listarLeitores(struct NoLeitor *listaDeLeitores);

//====================================================================================================================//

int main(void){
	
	//Declara��o de vari�veis primitivas
	   //Cont Cod Emprestimo  - Cont Matr�cula - Cont Cod Livro - Vari�vel Para Recolher Op��o do Usu�rio 
	int  codEmp=1, 				matricula=1,     codLivro=1,      op=0, opcao;
	
	//Declara��o de vari�veis Personalizadas
	struct NoLeitor     *listaDeLeitores    = NULL, *novoLeitor     = NULL, *auxLeitor	  ;
	struct NoLivro      *listaDeLivros      = NULL, *novoLivro      = NULL, *auxLivro	  ;
	struct NoEmprestimo *listaDeEmprestimos = NULL, *novoEmprestimo = NULL, *auxEmprestimo;
	
	//Configura��o de Caracteres para 'UTF-8' (Permite o usuo de acentos no programa)
	setlocale(LC_ALL, "Portuguese");
	
	//In�cio do Ciclo DoWhile do Programa	
	do{	
		system("cls");//limpa a Tela
		desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho
		
		printf("1-CADASTRAR LEITOR    3-LISTAR LEITORES     5-REALIZAR EMPRESTIMO     7-ALTERA   9-SAIR\n");
		printf("2-CADASTRAR LIVRO     4-LISTAR LIVROS       6-REALIZAR CONSULTA       8-EXCLUI\n\nOPCAO:");
		scanf("%i",&op);
		
		
		if(op==9)break;//Analisa se o usu�rio deseja finalizar o programa.
		
		else{// Caso n�o deseje, d� procedimento ao programa
		
			switch(op){
				case 1://Cadastra Leitor
					
					system("cls");//limpa a Tela
					
					if((novoLeitor = (NoLeitor*) malloc(sizeof(struct NoLeitor))) == NULL){//Analiza Se Foi Alocado Corretamente Um Espa�o Para O Novo Leitor  
						printf(" TEMOS UM N�MERO MUITO GRANDE DE LEITORES!\nPOR FAVOR, VOLTE M�S QUE VEM!");
						system("pause");//Pausa o Sistema
					}else{
						cadastraLeitor(&novoLeitor, &listaDeLeitores, recolheDadosLeitor(&matricula));
						desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho
						printf("CADASTRO DE LEITOR\n");
						printf("------------------\n\n");
						printf(" LEITOR CADASTRADO COM SUCESSO!\n\n");
						fflush(stdin);
						printf(" LEITOR                         MATR�CULA\n");
						printf(" ------------------------------ ---------\n");
						printf(" %-30s %9.09i\n\n\n",novoLeitor->data.nome, novoLeitor->data.matricula);
						system("pause");
					}
				break;
					
				case 2://Cadastra Livro
					system("cls");
					if((novoLivro = (NoLivro*) malloc(sizeof(struct NoLivro))) == NULL){//Analiza Se Foi Alocado Corretamente Um Espa�o Para O Novo Livro 
						printf(" ESTOQUE MUITO CHEIO!\nPOR FAVOR, ESPERE AUMENTAR-MOS NOSSA ESTRUTURA!");
						system("pause");						
					}else{
						cadastraLivro(&novoLivro, &listaDeLivros, recolheDadosLivro(&codLivro));
						desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho
						printf("CADASTRO DE LIVRO\n");
						printf("-----------------\n\n");
						printf(" LIVRO CADASTRADO COM SUCESSO!\n\n");
						fflush(stdin);
						printf(" LIVRO                          COD.LIVRO\n");


						printf(" ------------------------------ ---------\n");
						printf(" %-30s %9.09i\n\n\n",novoLivro->data.nome, novoLivro->data.codLivro);
						system("pause");
					}
				break;
					
				case 3://Lista Leitores
					system("cls");
						if( listaDeLeitores == NULL ){
							desenhaCabecalho();
							printf("---ERRO: IMPOSS�VEL LISTAR LEITORES---\n\n\n");
							printf(" NENHUM LEITOR CADASTRADO ATE O MOMENTO!\n\n");
							printf("\n\n");
							system("pause");					
						}else{
							desenhaCabecalho();
							listarLeitores(listaDeLeitores);
							system("pause");
						}
				break;
			
				case 4://Lista Livros
					system("cls");
					if( listaDeLivros == NULL ){
						desenhaCabecalho();
						printf("---ERRO: IMPOSS�VEL LISTAR LIVROS---\n\n\n");
						printf(" NENHUM LIVRO CADASTRADO ATE O MOMENTO!\n\n");
						printf("\n\n");
						system("pause");					
					}else{
						desenhaCabecalho();
						listarLivros(listaDeLivros);
						system("pause");
					}					
				break;
				
				case 5://Realiza Empr�stimo
					system("cls");
					if(((listaDeLivros == NULL)||(listaDeLeitores == NULL))){
						desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho
						printf("---ERRO: IMPOSS�VEL REALIZAR EMPR�STIMO---\n\n\n");
						printf(" O ERRO PODE SER CAUSADO POR:\n\n");
						printf("   1)FALTA DE ALUNOS CONSTANDO NA BASE DE DADOS\n\n");
						printf("   2)FALTA DE LIVROS CONSTANDO NA BASE DE DADOS\n\n");
						printf(" OBS: CONSERTE O ERRO, E TENTE NOVAMENTE!\n");
						printf("\n\n");
						system("pause");				
					}else{
							novoEmprestimo = (NoEmprestimo*) malloc(sizeof(struct NoEmprestimo));
							if(novoEmprestimo == NULL ){
								desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho
								printf("---FALHA: MEM�RIA PODE ESTAR CHEIA! TENTE NOVAMENTE. ---\n\n\n");
								printf("\n\n");
								system("pause");
							}else{
								realizarEmprestimo(&listaDeEmprestimos, &novoEmprestimo, recolheDadosEmprestimo(listaDeLeitores, listaDeLivros, &codEmp ));
								system("cls");
								desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho
								printf("EMPRESTIMO\n");
								printf("----------\n\n");
								printf(" COD                         LEITOR MATR�CULA LIVRO                          COD.LIVRO\n");
								printf(" --- ------------------------------ --------- ------------------------------ ---------\n");
								printf(" %3.03i %30s %9.09i %30s %9.09i\n\n", novoEmprestimo->data.codigo, novoEmprestimo->data.leitor, novoEmprestimo->data.matricula, novoEmprestimo->data.livroEmp, novoEmprestimo->data.codigoLivro);
								system("pause");
							}
							
					}
				break;
				
				case 6://Realizar Consulta
					system("cls");
					desenhaCabecalho();
					printf("1-CONSULTAR LIVRO    2-CONSULTAR LEITOR    3-CONSULTAR EMPRESTIMO    4-CANCELAR OPERA��O\n\nOPCAO:");
					scanf("%i", &opcao);
					switch(opcao){
						case 1:
							if(listaDeLivros != NULL){
								realizarConsulta(listaDeEmprestimos, listaDeLivros, listaDeLeitores, 1);
								system("pause");
							}else{
								printf("erro");
								system("pause");
							}
						break;
							
						case 2:
							if(listaDeLeitores != NULL){
								realizarConsulta(listaDeEmprestimos, listaDeLivros, listaDeLeitores, 2);
								system("pause");
							}else{
								printf("erro");
								system("pause");
							}	
						break;
						
						case 3:
							if(listaDeEmprestimos != NULL){
								realizarConsulta(listaDeEmprestimos, listaDeLivros, listaDeLeitores, 3);
								system("pause");
							}else{
								printf("erro");
								system("pause");
							}					
						break;
						
						case 4:
							
						break;
						
						default:
							system("cls");
							printf("OP��O INV�LIDA. TENTE NOVAMENTE\n");//CASO O O USU�RIO DIGITE UM NUMERO DIFERENTES DOS PR�-DEFINIDOS.
							system("pause");
						
					}
					
					
				break;	
					/*
				case 7:
					system("cls");
										
				break;	
				case 8:
					
				break;	*/		
				default:
					system("cls");
					printf("OP��O INV�LIDA. TENTE NOVAMENTE\n");//CASO O O USU�RIO DIGITE UM NUMERO DIFERENTES DOS PR�-DEFINIDOS.
					system("pause");
				break;
			}	
		}
	}while(op!=9);	
	
	//===================================================================================================
	//Esses caras (1, 2, 3 ) Servem para liberar a mem�ria alocada para cada lista;(DISPOSI��O TEMPOR�RIA)
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
	
	novoEmprestimo = listaDeEmprestimos;
	while(novoEmprestimo != NULL){
		auxEmprestimo = novoEmprestimo;
		novoEmprestimo = novoEmprestimo->prox; 
		free(auxEmprestimo);
	}
	//====================================================================================================
	
	return 0;
}

void desenhaCabecalho(void){// FUN��O PARA DESENHAR O CABE�ALHO DO SISTEMA.
	printf("---------------------------------------------------------------------------------------\n");
	printf("|                              SISTEMA DA BIBLIOTECA                                  |\n");
	printf("---------------------------------------------------------------------------------------\n\n");
}

struct Leitor recolheDadosLeitor(int *matricula){

	struct Leitor leitor;
	fflush(stdin);//Limpa o buffer do teclado
	desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho

	printf("CADASTRO DE LEITOR\n");
	printf("------------------\n\n");
	printf(" DIGITE O NOME DO LEITOR:");
	fflush(stdin);//Limpa o buffer do teclado
	fgets(leitor.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USU�RIO.
	leitor.nome[strlen(leitor.nome) - 1] = '\0';
	leitor.matricula = *matricula;
	(*matricula)++;//Incrementa o numero da matricula
	system("cls");	
	return leitor;
}

void cadastraLeitor(struct NoLeitor **novoLeitor, struct NoLeitor **listaDeLeitores, struct Leitor dadosLeitor){

	(*novoLeitor)->data = dadosLeitor;//Copia dados da estrutura dadasLeitor para o ponteiro novoLeitor
	(*novoLeitor)->prox = *listaDeLeitores;//Aponta o campo prox do ponteiro novoLeitor para a onde o ponteiro da Lista esta apontando
	*listaDeLeitores = *novoLeitor;//faz a lista apontar para o novoLeitor
	//listarLeitores(*listaDeLeitores); Deixei aqui s� caso eu queira testar se esta adicionando mesmo na lista
}

struct Livro recolheDadosLivro(int *codLivro){
	
	struct Livro livro;
	fflush(stdin);//Limpa o buffer do teclado
	desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho

	printf("CADASTRO DE LIVRO\n");
	printf("-----------------\n\n");
	printf(" DIGITE O NOME DO LIVRO:");
	fflush(stdin);//Limpa o buffer do teclado
	fgets(livro.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USU�RIO.
	livro.nome[strlen(livro.nome) - 1] = '\0';
	livro.codLivro = *codLivro;
	(*codLivro)++;//Incrementa o numero do CodLivro
	system("cls");	
	return livro;
}

void cadastraLivro (struct NoLivro **novoLivro, struct NoLivro **listaDeLivros, struct Livro dadosLivro){
	
	(*novoLivro)->data = dadosLivro;//Copia dados da estrutura dadasLivro para o ponteiro novoLivro
	(*novoLivro)->prox = *listaDeLivros;//Aponta o campo prox do ponteiro novoLivro para a onde o ponteiro da Lista esta apontando
	*listaDeLivros = *novoLivro;//faz a lista apontar para o novoLivro
	//listarLivros(*listaDeLivros); Deixei aqui s� caso eu queira testar se esta adicionando mesmo na lista
}

char *retornaNome(struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitores,int matricula,int codLivro,int op){

	fflush(stdin);//Limpa o buffer do teclado
	
	//Declara��o de ponteiros para auxiliar na tarefa
	struct NoLivro  *nomeLivroAtual;
	struct NoLeitor *nomeLeitorAtual;
	
	switch(op){
		case 1://caso a op��o seja 1 a fun��o vai procurar o nome do livro correspondente ao codLivro
			nomeLivroAtual = listaDeLivros;
			while((nomeLivroAtual->data.codLivro) != codLivro ){
				nomeLivroAtual = nomeLivroAtual->prox;
			}
		
			return nomeLivroAtual->data.nome;//Quando achar o nome, retorna ele
		break;
		
		case 2://caso a op��o seja 2 a fun��o vai procurar o nome do leitor correspondente � matr�cula
			nomeLeitorAtual = listaDeLeitores;
			while((nomeLeitorAtual->data.matricula) != matricula ){
				nomeLeitorAtual = nomeLeitorAtual->prox;
			}
			return nomeLeitorAtual->data.nome;//Quando achar o nome, retorna ele
		break;
		
	}	
}

struct Emprestimo recolheDadosEmprestimo(struct NoLeitor *listaDeLeitores, struct NoLivro *listaDeLivros, int* codEmp){

	struct Emprestimo dadosEmprestimo;
	fflush(stdin);//Limpa o buffer do teclado.
	desenhaCabecalho();//Chama a fun��o que desenha o cabe�alho
	
	printf("EMPR�STIMO\n");
	printf("----------\n\n");
	printf(" DIGITE SUA MATR�CULA: ");
	scanf("%i",&dadosEmprestimo.matricula);

	//Usa a fun��o retornaNome para procurar o nome do leitor correspondente a matricula digitada e copia para dadosEmprestimo.leitor
	strcpy(dadosEmprestimo.leitor, retornaNome(listaDeLivros, listaDeLeitores, (dadosEmprestimo.matricula), 0 ,2));
	
	system("cls");
	desenhaCabecalho();
	printf("EMPR�STIMO\n");
	printf("----------\n\n");
	listarLivros(listaDeLivros);
	printf(" DIGITE O CODIGO DO LIVRO: ");
	scanf("%i",&dadosEmprestimo.codigoLivro);
	
	//Usa a fun��o retornaNome para procurar o nome do livro correspondente ao codLivro digitada e copia para dadosEmprestimo.livro
	strcpy(dadosEmprestimo.livroEmp , retornaNome(listaDeLivros, listaDeLeitores, 0, (dadosEmprestimo.codigoLivro) ,1));
	
	dadosEmprestimo.codigo = *codEmp;
	(*codEmp)++;//Incrementa o numero de codEmp
	
	return dadosEmprestimo;
}

void realizarEmprestimo(struct NoEmprestimo **listaDeEmprestimos, struct NoEmprestimo **novoEmprestimo, struct Emprestimo dadosEmprestimo){

	(*novoEmprestimo)->data = dadosEmprestimo;//Copia dados da estrutura dadasLivro para o ponteiro novoLivro
	(*novoEmprestimo)->prox = *listaDeEmprestimos;//Aponta o campo prox do ponteiro novoLivro para a onde o ponteiro da Lista esta apontando
	*listaDeEmprestimos = *novoEmprestimo;//faz a lista apontar para o novoLivro
}

/* =============================================================================PAREI AQUI!!!!!!!!*/

void listarLivros(struct NoLivro *listaDeLivros){//Fun��o para listar os livros

	struct NoLivro *livroAtual;//Cria um ponteiro para auxiliar na tarefa
	
	livroAtual = listaDeLivros;//o ponteiro auxiliar aponta para onde a lista est� apontando
	printf(" LIVRO                          COD.LIVRO\n");
	printf(" ------------------------------ ---------\n");
	while(livroAtual != NULL){
		printf(" %-30s %9.09i\n",livroAtual->data.nome, livroAtual->data.codLivro);
		livroAtual = livroAtual->prox;
	}
	printf("\n\n");
}

void listarLeitores(struct NoLeitor *listaDeLeitores){//Fun��o para listar os livros

	struct NoLeitor *leitorAtual;//Cria um ponteiro para auxiliar na tarefa
	
	leitorAtual = listaDeLeitores;//o ponteiro auxiliar aponta para onde a lista est� apontando
	printf(" LEITOR                         MATR�CULA\n");
	printf(" ------------------------------ ---------\n");
	while(leitorAtual != NULL){
		printf(" %-30s %9.09i\n",leitorAtual->data.nome, leitorAtual->data.matricula);
		leitorAtual = leitorAtual->prox;
	}
	printf("\n\n");
}

void realizarConsulta(struct NoEmprestimo *listaDeEmprestimos, struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitores, int indice){
	
	//Cria um ponteiros para auxiliar na tarefa
	struct NoEmprestimo *emprestimoAtual;
	struct NoLivro      *livroAtual;
	struct NoLeitor     *leitorAtual;
	
	//Cria um auxiliar de busca
	int procurado;
	
	switch(indice){
		case 1:
			livroAtual = listaDeLivros;//o ponteiro auxiliar aponta para onde a lista est� apontando
			printf("CONSULTA\n");
			printf("----------\n\n");
			printf(" DIGITE O CODIGO DO LIVRO: ");
			scanf("%i",&procurado);
			printf(" LIVRO                          COD.LIVRO\n");
			printf(" ------------------------------ ---------\n");
			while(livroAtual != NULL){
				if(livroAtual->data.codLivro == procurado){
					printf(" %-30s %9.09i\n",livroAtual->data.nome, livroAtual->data.codLivro);
				}	
				livroAtual = livroAtual->prox;
			}
			printf("\n\n");
				
		break;
		
		case 2:
			leitorAtual = listaDeLeitores;//o ponteiro auxiliar aponta para onde a lista est� apontando
			printf("CONSULTA\n");
			printf("----------\n\n");
			printf(" DIGITE O CODIGO DO LIVRO: ");
			scanf("%i",&procurado);
			printf(" LEITOR                         MATR�CULA\n");
			printf(" ------------------------------ ---------\n");
			while(leitorAtual != NULL){
				if(leitorAtual->data.matricula == procurado){
					printf(" %-30s %9.09i\n\n\n",leitorAtual->data.nome, leitorAtual->data.matricula);
				}	
				leitorAtual = leitorAtual->prox;
			}
			printf("\n\n");
		break;
		
		case 3:
			emprestimoAtual = listaDeEmprestimos;//o ponteiro auxiliar aponta para onde a lista est� apontando
			printf("CONSULTA\n");
			printf("----------\n\n");
			printf(" DIGITE SUA MATR�CULA: ");
			scanf("%i",&procurado);
			printf("\n\n-------------------------------CONSULTAR EMPRESTIMO-----------------------------------\n\n");
			printf(" COD                         LEITOR MATR�CULA LIVRO                          COD.LIVRO\n");
			printf(" --- ------------------------------ --------- ------------------------------ ---------\n");
			while( emprestimoAtual != NULL ){
				if(emprestimoAtual->data.matricula == procurado){
				printf(" %3.03i %30s %9.09i %30s %9.09i\n", emprestimoAtual->data.codigo, emprestimoAtual->data.leitor, emprestimoAtual->data.matricula, emprestimoAtual->data.livroEmp, emprestimoAtual->data.codigoLivro);
				}
				emprestimoAtual = emprestimoAtual->prox;
			}
			printf("\n\n");
				break;
	}
}
