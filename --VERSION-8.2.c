/*                                            
*	AUTHOR: GABRIEL PEREIRA DA CRUZ --- E-MAIL:gabriel.cruz116@gmail.com 	   --- WHATSAPP:(61)9 9583-0718
*	CURSO: SISTEMAS DE INFORMAÇÃO   --- IES: UNIVERSIDADE CATÓLICA DE BRASÍLIA --- UCB
*	SEMESTRE: 4° SEMESTRE 1/2017    --- DATA DA ÚLTIMA MODIFICAÇÃO:12/05/2017
*
*	OBJETIVO: CONSTRUIR UM SOFTWARE DE GESTÃO DE UMA BIBLIOTECA
*
*	FUNÇÕES: CADASTRAR.: LIVROS - LEITORES - | LISTAR.: LIVROS - LEITORES | REALIZAR E CONSULTAR EMPRÉSTIMOS
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void cadastraLeitor(struct NoLeitor  **novoLeitor, struct NoLeitor  **listaDeLeitores,  struct Leitor dadosLeitor);

//Cadastrar Livro
struct Livro recolheDadosLivro(int *codLivro);
void cadastraLivro(struct NoLivro  **novoLivro, struct NoLivro  **listaDeLivros, struct Livro dadosLivro);

//Realizar Emprestimo
struct Emprestimo recolheDadosEmprestimo(struct NoLeitor *listaDeLeitores, struct NoLivro *listaDeLivros, int *codEmp );
char *retornaNome(struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitor, int matricula, int codLivro, int op);
void realizarEmprestimo(struct NoEmprestimo **listaDeEmprestimos, struct NoEmprestimo **novoEmprestimo, struct Emprestimo dadosEmprestimo);

//Consultar Emprestimo
void consultarEmprestimos(struct NoEmprestimo *listaDeEmprestimos);

//Listar Livros
void listarLivros(struct NoLivro *listaDeLivros);

//Listar Leitores
void listarLeitores(struct NoLeitor *listaDeLeitores);

//====================================================================================================================//

int main(void){
	
	//Declaração de variáveis primitivas
	   //Cont Cod Emprestimo  - Cont Matrícula - Cont Cod Livro - Variável Para Recolher Opção do Usuário 
	int  codEmp=1, 				matricula=1,     codLivro=1,      op=0;
	
	//Declaração de variáveis Personalizadas
	struct NoLeitor     *listaDeLeitores    = NULL, *novoLeitor     = NULL, *auxLeitor	  ;
	struct NoLivro      *listaDeLivros      = NULL, *novoLivro      = NULL, *auxLivro	  ;
	struct NoEmprestimo *listaDeEmprestimos = NULL, *novoEmprestimo = NULL, *auxEmprestimo;
	
	//Início do Ciclo DoWhile do Programa	
	do{	
		system("cls");//limpa a Tela
		desenhaCabecalho();//Chama a função que desenha o cabeçalho
		
		printf("1-CADASTRAR LEITOR    3-REALIZAR EMPRESTIMO     5-LISTAR LIVROS     7-ALTERA   9-SAIR\n");
		printf("2-CADASTRAR LIVRO     4-CONSULTAR EMPRESTIMOS   6-LISTAR LEITORES   8-EXCLUI\n\nOPCAO:");
		scanf("%i",&op);
		
		
		if(op==9)break;//Analisa se o usuário deseja finalizar o programa.
		
		else{// Caso não deseje, dá procedimento ao programa
		
			switch(op){
				case 1://Cadastra Leitor
					
					system("cls");//limpa a Tela
					
					if((novoLeitor = (NoLeitor*) malloc(sizeof(struct NoLeitor))) == NULL){//Analiza Se Foi Alocado Corretamente Um Espaço Para O Novo Leitor  
						printf(" TEMOS UM NUMERO MUITO GRANDE DE LEITORES!\nPOR FAVOR, VOLTE MES QUE VEM!");
						system("pause");//Pausa o Sistema
					}else{
						cadastraLeitor(&novoLeitor, &listaDeLeitores, recolheDadosLeitor(&matricula));
						desenhaCabecalho();//Chama a função que desenha o cabeçalho
						printf("CADASTRO DE LEITOR-\n");
						printf("-------------------\n\n");
						fflush(stdin);
						printf(" LEITOR                         MATRICULA\n");
						printf(" ------------------------------ ---------\n");
						printf(" %-30s %9.09i\n\n\n",novoLeitor->data.nome, novoLeitor->data.matricula);
						system("pause");
					}
				break;
					
				case 2://Cadastra Livro
					system("cls");
					if((novoLivro = (NoLivro*) malloc(sizeof(struct NoLivro))) == NULL){//Analiza Se Foi Alocado Corretamente Um Espaço Para O Novo Livro 
						printf(" ESTOQUE MUITO CHEIO!\nPOR FAVOR, ESPERE AUMENTAR-MOS NOSSA ESTRUTURA!");
						system("pause");						
					}else{
						cadastraLivro(&novoLivro, &listaDeLivros, recolheDadosLivro(&codLivro));
						desenhaCabecalho();//Chama a função que desenha o cabeçalho
						printf("CADASTRO DE LIVRO-\n");
						printf("-------------------\n\n");
						printf(" LIVRO CADASTRADO COM SUCESSO!\n\n");
						fflush(stdin);
						printf(" LIVRO                          COD.LIVRO\n");


						printf(" ------------------------------ ---------\n");
						printf(" %-30s %9.09i\n\n\n",novoLivro->data.nome, novoLivro->data.codLivro);
						system("pause");
					}
				break;
					
				case 3://Realiza Empréstimo
					system("cls");
					if(((listaDeLivros == NULL)||(listaDeLeitores == NULL))){
						desenhaCabecalho();//Chama a função que desenha o cabeçalho
						printf("---ERRO: IMPOSSIVEL REALIZAR EMPRESTIMO---\n\n\n");
						printf(" O ERRO PODE SER CAUSADO POR:\n\n");
						printf("   1)FALTA DE ALUNOS CONSTANDO NA BASE DE DADOS\n\n");
						printf("   2)FALTA DE LIVROS CONSTANDO NA BASE DE DADOS\n\n");
						printf(" OBS: CONSERTE O ERRO, E TENTE NOVAMENTE!\n");
						printf("\n\n");
						system("pause");				
					}else{
							novoEmprestimo = (NoEmprestimo*) malloc(sizeof(struct NoEmprestimo));
							if(novoEmprestimo == NULL ){
								desenhaCabecalho();//Chama a função que desenha o cabeçalho
								printf("---FALHA: MEMÓRIA PODE ESTAR CHEIA! TENTE NOVAMENTE. ---\n\n\n");
								printf("\n\n");
								system("pause");
							}else{
								realizarEmprestimo(&listaDeEmprestimos, &novoEmprestimo, recolheDadosEmprestimo(listaDeLeitores, listaDeLivros, &codEmp ));
							}
							
					}
				break;
			
				case 4://Consulta Empréstimos
					system("cls");
					if(listaDeEmprestimos != NULL){
						consultarEmprestimos(listaDeEmprestimos);
						printf("\n\n");
						system("pause");
					}else{
						printf("erro");
						system("pause");
					}
					
				break;
				
				case 5://Lista Livros
					system("cls");
					if( listaDeLivros == NULL ){
						desenhaCabecalho();
						printf("---ERRO: IMPOSSIVEL LISTAR LIVROS---\n\n\n");
						printf(" NENHUM LIVRO CADASTRADO ATE O MOMENTO!\n\n");
						printf("\n\n");
						system("pause");					
					}else{
						desenhaCabecalho();
						listarLivros(listaDeLivros);
						system("pause");
					}
				break;
				
				case 6://Lista Leitores
					system("cls");
					if( listaDeLeitores == NULL ){
						desenhaCabecalho();
						printf("---ERRO: IMPOSSIVEL LISTAR LEITORES---\n\n\n");
						printf(" NENHUM LEITOR CADASTRADO ATE O MOMENTO!\n\n");
						printf("\n\n");
						system("pause");					
					}else{
						desenhaCabecalho();
						listarLeitores(listaDeLeitores);
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
					printf("OPCAO INVALIDA. TENTE NOVAMENTE\n");//CASO O O USUÁRIO DIGITE UM NUMERO DIFERENTES DOS PRÉ-DEFINIDOS.
					system("pause");
				break;
			}	
		}
	}while(op!=9);	
	
	//===================================================================================================
	//Esses caras (1, 2, 3 ) Servem para liberar a memória alocada para cada lista;(DISPOSIÇÃO TEMPORÁRIA)
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

void desenhaCabecalho(void){// FUNÇÃO PARA DESENHAR O CABEÇALHO DO SISTEMA.
	printf("---------------------------------------------------------------------------------------\n");
	printf("-------------------------------SISTEMA DA BIBLIOTECA-----------------------------------\n");
	printf("---------------------------------------------------------------------------------------\n");
}

struct Leitor recolheDadosLeitor(int *matricula){

	struct Leitor leitor;
	fflush(stdin);//Limpa o buffer do teclado
	desenhaCabecalho();//Chama a função que desenha o cabeçalho

	printf("CADASTRO DE LEITOR-\n");
	printf("-------------------\n\n");
	printf(" DIGITE O NOME DO LEITOR:");
	fflush(stdin);//Limpa o buffer do teclado
	fgets(leitor.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
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
	//listarLeitores(*listaDeLeitores); Deixei aqui só caso eu queira testar se esta adicionando mesmo na lista
}

struct Livro recolheDadosLivro(int *codLivro){
	
	struct Livro livro;
	fflush(stdin);//Limpa o buffer do teclado
	desenhaCabecalho();//Chama a função que desenha o cabeçalho

	printf("CADASTRO DE LIVRO-\n");
	printf("-------------------\n\n");
	printf(" DIGITE O NOME DO LIVRO:");
	fflush(stdin);//Limpa o buffer do teclado
	fgets(livro.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
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
	//listarLivros(*listaDeLivros); Deixei aqui só caso eu queira testar se esta adicionando mesmo na lista
}

char *retornaNome(struct NoLivro *listaDeLivros, struct NoLeitor *listaDeLeitores,int matricula,int codLivro,int op){

	fflush(stdin);//Limpa o buffer do teclado
	
	//Declaração de ponteiros para auxiliar na tarefa
	struct NoLivro  *nomeLivroAtual;
	struct NoLeitor *nomeLeitorAtual;
	
	switch(op){
		case 1://caso a opção seja 1 a função vai procurar o nome do livro correspondente ao codLivro
			nomeLivroAtual = listaDeLivros;
			while((nomeLivroAtual->data.codLivro) != codLivro ){
				nomeLivroAtual = nomeLivroAtual->prox;
			}
		
			return nomeLivroAtual->data.nome;//Quando achar o nome, retorna ele
		break;
		
		case 2://caso a opção seja 2 a função vai procurar o nome do leitor correspondente à matrícula
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
	desenhaCabecalho();//Chama a função que desenha o cabeçalho
	
	printf("---EMPRESTIMO---\n\n");
	printf(" DIGITE SUA MATRICULA: ");
	scanf("%i",&dadosEmprestimo.matricula);

	//Usa a função retornaNome para procurar o nome do leitor correspondente a matricula digitada e copia para dadosEmprestimo.leitor
	strcpy(dadosEmprestimo.leitor, retornaNome(listaDeLivros, listaDeLeitores, (dadosEmprestimo.matricula), 0 ,2));
	
	system("cls");
	desenhaCabecalho();
	printf("---EMPRESTIMO---\n\n");
	listarLivros(listaDeLivros);
	printf(" DIGITE O CODIGO DO LIVRO: ");
	scanf("%i",&dadosEmprestimo.codigoLivro);
	
	//Usa a função retornaNome para procurar o nome do livro correspondente ao codLivro digitada e copia para dadosEmprestimo.livro
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
void consultarEmprestimos(struct NoEmprestimo *listaDeEmprestimos){
	
	struct NoEmprestimo *emprestimoAtual;//Cria um ponteiro para auxiliar na tarefa
	
	emprestimoAtual = listaDeEmprestimos;//o ponteiro auxiliar aponta para onde a lista está apontando
	printf("\n\n-------------------------------CONSULTAR EMPRESTIMO-----------------------------------\n\n");
	printf(" COD                         LEITOR MATRICULA LIVRO                          COD.LIVRO\n");
	printf(" --- ------------------------------ --------- ------------------------------ ---------\n");
	while( emprestimoAtual != NULL ){
		printf(" %3.03i %30s %9.09i %30s %9.09i\n", emprestimoAtual->data.codigo, emprestimoAtual->data.leitor, emprestimoAtual->data.matricula, emprestimoAtual->data.livroEmp, emprestimoAtual->data.codigoLivro);
		emprestimoAtual = emprestimoAtual->prox;
	}
	printf("\n\n");
}

void listarLivros(struct NoLivro *listaDeLivros){//Função para listar os livros

	struct NoLivro *livroAtual;//Cria um ponteiro para auxiliar na tarefa
	
	livroAtual = listaDeLivros;//o ponteiro auxiliar aponta para onde a lista está apontando
	printf(" LIVRO                          COD.LIVRO\n");
	printf(" ------------------------------ ---------\n");
	while(livroAtual != NULL){
		printf(" %-30s %9.09i\n",livroAtual->data.nome, livroAtual->data.codLivro);
		livroAtual = livroAtual->prox;
	}
	printf("\n\n");
}

void listarLeitores(struct NoLeitor *listaDeLeitores){//Função para listar os livros

	struct NoLeitor *leitorAtual;//Cria um ponteiro para auxiliar na tarefa
	
	leitorAtual = listaDeLeitores;//o ponteiro auxiliar aponta para onde a lista está apontando
	printf(" LIVRO                          COD.LIVRO\n");
	printf(" ------------------------------ ---------\n");
	while(leitorAtual != NULL){
		printf(" %-30s %9.09i\n",leitorAtual->data.nome, leitorAtual->data.matricula);
		leitorAtual = leitorAtual->prox;
	}
	printf("\n\n");
}
