/************************************************************************************************************                                                             
********AUTHOR: GABRIEL PEREIRA DA CRUZ***E-MAIL:GABRIEL.CRUZ116@GMAIL.COM***WHATSAPP:(61)9 9324-4898****************
********CURSO: SISTEMAS DE INFORMAÇÃO*****IES: UNIVERSIDADE CATÓLICA DE BRASÍLIA - UCB*******************************
********SEMESTRE: 4° SEMESTRE 1/2017******DATA DA ÚLTIMA MODIFICAÇÃO:07/03/2017**************************************
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

void desenhaCabecalho(void);// FUNÇÃO PARA DESENHAR O CABEÇALHO DO SISTEMA.

typedef struct Leitor{
	char nome[TS];
	int matricula;
}Leitor;

typedef struct Livro {
	char nome[TS];
	int codigo;
}Livro;

typedef struct Emprestimo{
	int codigo;
	int codigoLivro;
	char livroEmp[TS];
	int matricula;
	char leitor[TS];
}Emprestimo;

//Declaração de Protótipos das Funções
//====================================================================================================================//
//Cadastrar Leitor
struct Leitor recolheDadosLeitor(int *matricula);
void cadastraLeitor(struct Leitor leitor[],int *pple, struct Leitor dadosLeitor);
//Cadastrar Livro
struct Livro recolheDadosLivro(int *codigo);
void cadastraLivro(struct Livro livro[],int *ppli, struct Livro dadosLivro);
//Realizar Emprestimo
struct Emprestimo recolheDadosEmprestimo(struct Livro livro[], int ppli);
void realizarEmprestimo(struct Emprestimo emprestimo[], int* cEm, int *empC, struct Emprestimo dadosEmprestimo, struct Livro livro[] , struct Leitor leitor[]);
void consultarEmprestimos(struct Emprestimo emprestimo[], int cEm);

//Listar Livros
void listarLivros(struct Livro livro[], int ppli);
//Listar Leitores
void listarLeitores(struct Leitor leitor[], int pple);

int main(void){
	int pple=0 /*Conta nº de Leitores*/,ppli=0 /*Conta nº de Livros*/,
		qtdEmp=0 /*Conta nº de Emprestimos*/,	codEmp=1 /*Código de Empréstimo*/,
		matricula=1,codigo=1, op=0;
	struct Leitor leitor[TV];
	struct Livro livro[TV];
	struct Emprestimo emprestimo[100];
		
	do{	
		system("cls");
		desenhaCabecalho();//CHAMA FUNÇÃO DESENHAR CABEÇALHO.
		printf("1-CADASTRAR LEITOR    3-REALIZAR EMPRESTIMO     5-LISTAR LIVROS     7-ALTERA   9-SAIR\n");
		printf("2-CADASTRAR LIVRO     4-CONSULTAR EMPRESTIMOS   6-LISTAR LEITORES   8-EXCLUI\n\nOPCAO:");
		scanf("%i",&op);
		if(op==9)break;//FAZ UM COMPARAÇÃO.
		else{
			switch(op){
				case 1:
					system("cls");//lIMPA A TELA.
					if(pple>TV){//CHAMA FUNÇÃO CADASTRA LIVRO.
						printf(" TEMOS UM NUMERO MUITO GRANDE DE LEITORES!\nPOR FAVOR, VOLTE MES QUE VEM!");
						system("pause");//PAUSA O SISTEMA.
					}else{
						cadastraLeitor(leitor, &pple, recolheDadosLeitor(&matricula));
						desenhaCabecalho();
						printf("CADASTRO DE LEITOR-\n");
						printf("-------------------\n\n");
						fflush(stdin);
						printf(" LEITOR                         MATRICULA\n");
						printf(" ------------------------------ ---------\n");
						printf(" %30s %-9.08i\n",leitor[pple-1].nome,leitor[pple-1].matricula);
						system("pause");//PAUSA O SISTEMA.
					}
				break;
					
				case 2:
					system("cls");//lIMPA A TELA.
					if(ppli>TV){//CHAMA FUNÇÃO CADASTRA LIVRO.
						printf(" ESTOQUE MUITO CHEIO!\nPOR FAVOR, ESPERE AUMENTAR-MOS NOSSA ESTRUTURA!");
						system("pause");//PAUSA O SISTEMA.						
					}else{
						cadastraLivro(livro, &ppli, recolheDadosLivro(&codigo));
						desenhaCabecalho();
						printf("CADASTRO DE LIVRO-\n");
						printf("-------------------\n\n");
						printf(" LIVRO CADASTRADO COM SUCESSO!\n\n");
						fflush(stdin);
						printf(" LEITOR                         MATRICULA\n");
						printf(" ------------------------------ ---------\n");
						printf(" %30s %-9.08i\n",livro[ppli-1].nome,livro[ppli-1].codigo);
						system("pause");//PAUSA O SISTEMA.
					}
				break;
				
				case 3:
					system("cls");//lIMPA A TELA.
					if((ppli<1)||(pple<1)){
						desenhaCabecalho();
						printf("***ERRO: IMPOSSIVEL REALIZAR EMPRESTIMO***\n\n\n");
						printf(" O ERRO PODE SER CAUSADO POR:\n\n");
						printf("   1)FALTA DE ALUNOS CONSTANDO NA BASE DE DADOS\n\n");
						printf("   2)FALTA DE LIVROS CONSTANDO NA BASE DE DADOS\n\n");
						printf(" OBS: CONSERTE O ERRO, E TENTE NOVAMENTE!\n");
						printf("\n\n");
						system("pause");//PAUSA O SISTEMA.					
					}else{
						realizarEmprestimo(emprestimo, &qtdEmp, &codEmp, recolheDadosEmprestimo(livro,ppli), livro, leitor);
					}
				break;
				
				case 4:
					system("cls");
					if(qtdEmp>0){
						consultarEmprestimos(emprestimo, qtdEmp);
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
						printf("***ERRO: IMPOSSIVEL LISTAR LIVROS***\n\n\n");
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
						printf("***ERRO: IMPOSSIVEL LISTAR LEITORES***\n\n\n");
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
					
				break;			
				default:
					system("cls");//lIMPA A TELA.
					printf("OPCAO INVALIDA. TENTE NOVAMENTE\n");//CASO O O USUÁRIO DIGITE UM NUMERO DIFERENTES DOS PRÉ-DEFINIDOS.
					system("pause");//PAUSA O SISTEMA.
				break;
			}	
		}
	}while(op!=9);	
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

void cadastraLeitor(struct Leitor leitor[],int *pple, struct Leitor dadosLeitor){
	strcpy(leitor[(*pple)].nome, dadosLeitor.nome);
	leitor[*pple].matricula = dadosLeitor.matricula;
	(*pple)++;
}

struct Livro recolheDadosLivro(int *codigo){
	struct Livro livro;
	fflush(stdin);//LIMPA O BUFFER DO TECLADO.
	desenhaCabecalho();
	printf("CADASTRO DE LIVRO-\n");
	printf("-------------------\n\n");
	printf(" DIGITE O NOME DO LIVRO:");
	fflush(stdin);
	fgets(livro.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
	livro.nome[strlen(livro.nome) - 1] = '\0';
	livro.codigo = *codigo;
	(*codigo)++;
	system("cls");	
	return livro;
}

void cadastraLivro(struct Livro livro[],int *ppli, struct Livro dadosLivro){
	strcpy(livro[(*ppli)].nome, dadosLivro.nome);
	livro[*ppli].codigo = dadosLivro.codigo;
	(*ppli)++;
}

struct Emprestimo recolheDadosEmprestimo(struct Livro livro[], int ppli){
	struct Emprestimo dadosEmprestimo;
	fflush(stdin);//LIMPA O BUFFER DO TECLADO.
	desenhaCabecalho();
	printf("***EMPRESTIMO***\n\n");
	printf(" DIGITE SUA MATRICULA: ");
	scanf("%i",&dadosEmprestimo.matricula);
	system("cls");//PAUSA O SISTEMA.
	desenhaCabecalho();
	printf("***EMPRESTIMO***\n\n");
	listarLivros(livro,ppli);
	//system("pause");//PAUSA O SISTEMA.
	printf(" DIGITE O CODIGO DO LIVRO: ");
	scanf("%i",&dadosEmprestimo.codigoLivro);
	return dadosEmprestimo;
}

void realizarEmprestimo(struct Emprestimo emprestimo[], int	*qtdEmp, int *codEmp, struct Emprestimo dadosEmprestimo, struct Livro livro[], struct Leitor leitor[]){
	emprestimo[(*qtdEmp)].matricula = dadosEmprestimo.matricula;
	emprestimo[(*qtdEmp)].codigoLivro = dadosEmprestimo.codigoLivro;
	emprestimo[(*qtdEmp)].codigo = *codEmp;
	strcpy(emprestimo[(*qtdEmp)].livroEmp, livro[(dadosEmprestimo.codigoLivro - 1)].nome); 
	strcpy(emprestimo[(*qtdEmp)].leitor, leitor[(dadosEmprestimo.matricula - 1)].nome); 
	(*qtdEmp)++;
	(*codEmp)++;	
}

void consultarEmprestimos(struct Emprestimo emprestimo[], int qtdEmp){
	int i;
	printf("\n\n-------------------------------CONSULTAR EMPRESTIMO-----------------------------------\n\n");
	printf(" COD                         LEITOR MATRICULA LIVRO                          COD.LIVRO\n");
	printf(" --- ------------------------------ --------- ------------------------------ ---------\n");
	for(i=0; i<qtdEmp; i++){
		printf(" %3.3i %30s %9.8i %30s %9.8i\n ", emprestimo[i].codigo, emprestimo[i].leitor, emprestimo[i].matricula, emprestimo[i].livroEmp, emprestimo[i].codigoLivro);
	}
}

void listarLivros(struct Livro livro[], int ppli){
	int i;
	printf(" LIVRO                          COD.LIVRO\n");
	printf(" ------------------------------ ---------\n");
	for(i=0;i<ppli;i++)
		printf(" %30s %-9.08i\n",livro[i].nome,livro[i].codigo);

	printf("\n\n");
}

void listarLeitores(struct Leitor leitor[], int pple){
	int i;
	printf(" LEITOR                         MATRICULA\n");
	printf(" ------------------------------ ---------\n");
	for(i=0;i<pple;i++)
		printf(" %30s %-9.08i\n",leitor[i].nome,leitor[i].matricula);
	
	printf("\n\n");
}
