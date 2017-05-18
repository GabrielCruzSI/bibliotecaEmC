/*                                            
*	AUTHOR: GABRIEL PEREIRA DA CRUZ --- E-MAIL:gabriel.cruz116@gmail.com 	   --- WHATSAPP:(61)9 9583-0718
*	CURSO: SISTEMAS DE INFORMAÇÃO   --- IES: UNIVERSIDADE CATÓLICA DE BRASÍLIA --- UCB
*	SEMESTRE: 4° SEMESTRE 1/2017    --- DATA DA ÚLTIMA MODIFICAÇÃO:17/05/2017
*
*	OBJETIVO: CONSTRUIR UM SOFTWARE DE GESTÃO DE UMA BIBLIOTECA
*
*	FUNÇÕES: CADASTRAR.: LIVROS - LEITORES - | LISTAR.: LIVROS - LEITORES | REALIZAR E CONSULTAR EMPRÉSTIMOS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //Biblioteca para configurar os caracteres latinos

/* Ajuste das funçôes específicas aos OS */
#ifdef __unix__ 
#define LIMPA_TELA system("clear")

#elif defined (_WIN32) || defined (WIN32) 
#define LIMPA_TELA system("cls")
#endif
#define PAUSE system("pause")

#define TS 30

//Estrutras De Leitores
typedef struct Leitor{
	char nome[TS];
	int matricula;
	char deletado;
}Leitor;

//Estrutras De Livros
typedef struct Livro {
	char nome[TS];
	int codLivro;
	char deletado;
}Livro;

//Estrutras De Empréstimos
typedef struct Emprestimo{
	int codigo;
	int codigoLivro;
	char livroEmp[TS];
	int matricula;
	char leitor[TS];
	char success;
}Emprestimo;

//Estrutras Para Contar 
typedef struct Cont{
	int mat;
	int codLiv;
	int codEmp;
	int situacao;
}Cont;

//Declaração de Protótipos das Funções
//====================================================================================================================//

// Desenhar Cabeçalho Do Sistema
void desenhaCabecalho(void);

//Desenha Subcabeçalhos do Sistema
void imprimeSubCabecalho(int sessao);

//Cadastrar Leitor
struct Leitor recolheDadosLeitor(int *matricula);
struct Leitor cadastraLeitor( FILE** listaDeleitores,  struct Leitor dadosLeitor);


//Cadastrar Livro
struct Livro recolheDadosLivro(int *codLivro);
struct Livro cadastraLivro( FILE** listaDelivros,  struct Livro dadosLivro);

//Realizar Emprestimo
struct Emprestimo recolheDadosEmprestimo(int *codEmp);
void retornaNome(struct Emprestimo *va, int matricula, int codLivro, int op);
struct Emprestimo realizarEmprestimo(FILE** , struct Emprestimo dadosEmprestimo);

//Listar Livros
int listarLivros();

//Listar Leitores
int listarLeitores();

//Abre/Fecha Arquivo
int abreArquivo(FILE** arquivo, char* nomeDoArquivo, char* modo);
void fechaArquivo(FILE** arquivo);

//Realizar Consulta
void realizarConsulta(int indice, FILE** listaAtual);

//Realizar Alteração
void realizarAlteracao(int indice, FILE** listaAtual);

//Realizar Alteração
void realizarExclusao(int indice, FILE** listaAtual);

//Atualiza Contadores
int atualizaContadores(int, int, int);

//====================================================================================================================//

int main(void){
	
	
	FILE *listaDeLeitores, *listaDeLivros, *listaDeEmprestimos, *cont;
	struct Cont contador;
	int situacao;
	
	int codEmp = 0, matricula = 0, codLivro = 0, op , opcao;
	
	situacao = abreArquivo(&cont, "cont/cont.dat", "rb");
	
	if(situacao == 0){
		codEmp=1; 
		matricula=1; 
		codLivro=1;
	}
	
	if(situacao == 1){
		fread(&contador, sizeof(struct Cont), 1, cont);
		
		codEmp = contador.codEmp;
		matricula = contador.mat;
		codLivro = contador.codLiv;
		
		fechaArquivo(&cont);
	}	
	
	//Declaração de variáveis Personalizadas
	struct Leitor 	  leitorAtual	 ;
	struct Livro  	  livroAtual	 ;
	struct Emprestimo emprestimoAtual;
	
	//Configuração de Caracteres para 'UTF-8' (Permite o usuo de acentos no programa)
	setlocale(LC_ALL, "");
	
	//Início do Ciclo DoWhile do Programa	
	do{	
		LIMPA_TELA;//limpa a Tela
		desenhaCabecalho();//Chama a função que desenha o cabeçalho
		fflush(stdin);
		printf("1-CADASTRAR LEITOR    3-LISTAR LEITORES     5-REALIZAR EMPRESTIMO     7-ALTERA   9-SAIR\n");
		printf("2-CADASTRAR LIVRO     4-LISTAR LIVROS       6-REALIZAR CONSULTA       8-EXCLUI   10-LIXEIRA\n\nOPCAO:");
		scanf("%i",&op);
		
		
		if(op==9)break;//Analisa se o usuário deseja finalizar o programa.
		
		else{// Caso não deseje, dá procedimento ao programa
		
			switch(op){
				case 1://Cadastra Leitor
					
					LIMPA_TELA;//limpa a Tela
					
					leitorAtual = cadastraLeitor(&listaDeLeitores, recolheDadosLeitor(&matricula));
					
					if(leitorAtual.matricula == 0){
						printf(" TEMOS UM NÚMERO MUITO GRANDE DE LEITORES!\nPOR FAVOR, VOLTE MÊS QUE VEM!\n\n");
					}else{
						desenhaCabecalho();//Chama a função que desenha o cabeçalho
						imprimeSubCabecalho(1);
						printf(" LEITOR CADASTRADO COM SUCESSO!\n\n");
						imprimeSubCabecalho(3);
						printf(" %-1c %-30s %9.09i\n\n\n",leitorAtual.deletado, leitorAtual.nome, leitorAtual.matricula);
						system("pause"); 
					}
										
				break;
					
				case 2://Cadastra Livro
					LIMPA_TELA;
					
					livroAtual = cadastraLivro(&listaDeLivros, recolheDadosLivro(&codLivro));
					
					if(livroAtual.codLivro == 0){
						printf(" ESTOQUE MUITO CHEIO!\nPOR FAVOR, ESPERE AUMENTAR-MOS NOSSA ESTRUTURA!");
						PAUSE;
					}else{
						desenhaCabecalho();//Chama a função que desenha o cabeçalho
						imprimeSubCabecalho(4);
						printf(" LIVRO CADASTRADO COM SUCESSO!\n\n");
						imprimeSubCabecalho(6);
						printf(" %-1c %-30s %9.09i\n\n\n",livroAtual.deletado, livroAtual.nome, livroAtual.codLivro);
						PAUSE;	
					} 
					
				break;
					
				case 3://Lista Leitores
					LIMPA_TELA;
						if(listarLeitores() == 0){
							desenhaCabecalho();
							imprimeSubCabecalho(12);
							PAUSE;					
						}else{
							PAUSE;
						}
				break;
			
				case 4://Lista Livros
						LIMPA_TELA;
						if(listarLivros() == 0){
							desenhaCabecalho();
							imprimeSubCabecalho(13);
							PAUSE;					
						}else{
							PAUSE;
						}					
				break;
				
				case 5://Realiza Empréstimo
					LIMPA_TELA;
					abreArquivo(&listaDeLeitores, "leitores/listaDeLeitores.dat", "rb");
					abreArquivo(&listaDeLivros, "livros/listaDeLivros.dat", "rb");
					if(!fread(&leitorAtual, sizeof(struct Leitor), 1, listaDeLeitores) || !fread(&livroAtual, sizeof(struct Livro), 1, listaDeLivros)){
						desenhaCabecalho();//Chama a função que desenha o cabeçalho
						printf("---ERRO: IMPOSSÍVEL REALIZAR EMPRÉSTIMO---\n\n\n");
						printf(" O ERRO PODE SER CAUSADO POR:\n\n");
						printf("   1)FALTA DE ALUNOS CONSTANDO NA BASE DE DADOS\n\n");
						printf("   2)FALTA DE LIVROS CONSTANDO NA BASE DE DADOS\n\n");
						printf(" OBS: CONSERTE O ERRO, E TENTE NOVAMENTE!\n");
						printf("\n\n");
						PAUSE;				
					}else{
						fechaArquivo(&listaDeLeitores);
						fechaArquivo(&listaDeLivros);
						emprestimoAtual = realizarEmprestimo(&listaDeEmprestimos, recolheDadosEmprestimo(&codEmp));
						
						if(emprestimoAtual.success == '1' || emprestimoAtual.success == '2'){
							LIMPA_TELA;
							desenhaCabecalho();//Chama a função que desenha o cabeçalho
							imprimeSubCabecalho(7);
							printf("---ERRO: IMPOSSÍVEL REALIZAR EMPRÉSTIMO---\n\n\n");
							if(emprestimoAtual.success == '1')
								printf(" O LIVRO INFORMADO, NÃO CONSTA MAIS NA BASE DE DADOS");
							if(emprestimoAtual.success == '2')
								printf(" O LEITOR INFORMADO, NÃO CONSTA MAIS NA BASE DE DADOS");
							printf("\n\n");
							PAUSE;
							fflush(stdin);
							emprestimoAtual.success = '*';
						}else{
							LIMPA_TELA;
							desenhaCabecalho();//Chama a função que desenha o cabeçalho
							imprimeSubCabecalho(7);
							imprimeSubCabecalho(8);
							printf(" %3.03i %30s %9.09i %30s %9.09i\n\n", emprestimoAtual.codigo, emprestimoAtual.leitor, emprestimoAtual.matricula, emprestimoAtual.livroEmp, emprestimoAtual.codigoLivro);
							PAUSE;	
						}							
					}
				break;
				
				case 6://Realizar Consulta
					do{
						LIMPA_TELA;
						desenhaCabecalho();
						imprimeSubCabecalho(9);
						printf("1-CONSULTAR LIVRO    2-CONSULTAR LEITOR    3-CONSULTAR EMPRESTIMO    4-CANCELAR OPERAÇÃO\n\nOPCAO:");
						fflush(stdin);
						scanf("%i", &opcao);
						if(opcao == 4) break;
						switch(opcao){
							case 1:
								if(abreArquivo(&listaDeLivros, "livros/listaDeLivros.dat", "rb") == 1){
									realizarConsulta(opcao, &listaDeLivros);
									PAUSE;
								}else{
									printf("erro");
									PAUSE;
								}
							break;
								
							case 2:
								if(abreArquivo(&listaDeLeitores, "leitores/listaDeLeitores.dat", "rb") == 1){
									realizarConsulta(opcao, &listaDeLeitores);
									PAUSE;
								}else{
									printf("erro");
									PAUSE;
								}	
							break;
							
							case 3:
								if(abreArquivo(&listaDeEmprestimos, "emprestimos/listaDeEmprestimos.dat", "rb") == 1){
									realizarConsulta(opcao, &listaDeEmprestimos);
									PAUSE;
								}else{
									printf("erro");
									PAUSE;
								}					
							break;
							
							case 4:
								
							break;
							
							default:
								LIMPA_TELA;
								desenhaCabecalho();
								imprimeSubCabecalho(9);
								printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE\n\n");//CASO O O USUÁRIO DIGITE UM NUMERO DIFERENTES DOS PRÉ-DEFINIDOS.
								PAUSE;
						
						}
					}while(opcao != 4);
					

				break;	
					
				case 7://Realizar Alteração
					do{
						LIMPA_TELA;
						desenhaCabecalho();
						printf("1-ALTERAR LIVRO    2-ALTERAR LEITOR    3-CANCELAR OPERAÇÃO\n\nOPCAO:");
						fflush(stdin);
						scanf("%i", &opcao);
						if(opcao == 3)break;
						switch(opcao){
							case 1:
								if(abreArquivo(&listaDeLivros, "livros/listaDeLivros.dat", "r+b") == 1){
									realizarAlteracao(1, &listaDeLivros);
									PAUSE;
								}else{
									printf("erro");
									PAUSE;
								}
							break;
								
							case 2:
								if(abreArquivo(&listaDeLeitores, "leitores/listaDeLeitores.dat", "r+b") == 1){
									realizarAlteracao(2, &listaDeLeitores);
									PAUSE;
								}else{
									printf("erro");
									PAUSE;
								}	
							break;
							
							case 3:
													
							break;
							
							default:
								LIMPA_TELA;
								desenhaCabecalho();
								imprimeSubCabecalho(10);
								printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE\n\n");//CASO O O USUÁRIO DIGITE UM NUMERO DIFERENTES DOS PRÉ-DEFINIDOS.
								PAUSE;
						}
					}while(opcao != 3);							
				break;	
				
				case 8:
					do{
						LIMPA_TELA;
						desenhaCabecalho();
						imprimeSubCabecalho(11);
						printf("1-EXCLUIR LIVRO    2-EXCLUIR LEITOR    3-CANCELAR OPERAÇÃO\n\nOPCAO:");
						fflush(stdin);
						scanf("%i", &opcao);
						switch(opcao){
							case 1:
								if(abreArquivo(&listaDeLivros, "livros/listaDeLivros.dat", "r+b") == 1){
									realizarExclusao(1, &listaDeLivros);
									PAUSE;
								}else{
									printf("erro");
									PAUSE;
								}
							break;
								
							case 2:
								if(abreArquivo(&listaDeLeitores, "leitores/listaDeLeitores.dat", "r+b") == 1){
									realizarExclusao(2, &listaDeLeitores);
									PAUSE;
								}else{
									printf("erro");
									PAUSE;
								}	
							break;
							
							case 3:
													
							break;
							
							default:
								LIMPA_TELA;
								desenhaCabecalho();
								imprimeSubCabecalho(11);
								printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE\n\n");//CASO O O USUÁRIO DIGITE UM NUMERO DIFERENTES DOS PRÉ-DEFINIDOS.
								PAUSE;
							
						}
					}while(opcao != 3);
				break;		
				
				default:
					LIMPA_TELA;
					printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE\n");//CASO O O USUÁRIO DIGITE UM NUMERO DIFERENTES DOS PRÉ-DEFINIDOS.
					PAUSE;
				break;
			}	
		}
	}while(op!=9);	
	
	
	situacao = abreArquivo(&cont, "cont/cont.dat", "wb");
	fechaArquivo(&cont);
	if(situacao == 0){
		printf("Falha na numeração!");
		exit(1);
	}
	
	if(situacao == 1){
		situacao = atualizaContadores(codEmp, matricula , codLivro);
		if(situacao == 0){
			printf("Falha grave no Sistema");
		}
	}
	
	return 0;
}

int atualizaContadores(int codEmp, int matricula, int codLivro){
	
	struct Cont dadosAtualizados;
	FILE *arquivo;
	
	dadosAtualizados.codEmp = codEmp;
	dadosAtualizados.mat = matricula;
	dadosAtualizados.codLiv = codLivro;
	
	arquivo = fopen("cont/cont.dat", "wb");
	
	if (arquivo == NULL) {
		return 0;
	}
	
	fwrite(&dadosAtualizados, sizeof(struct Cont), 1, arquivo);
	
	fclose(arquivo);
	
	return 1;
}

void desenhaCabecalho(void){// FUNÇÃO PARA DESENHAR O CABEÇALHO DO SISTEMA.
	printf("--------------------------------------------------------------------------------------------------\n");
	printf("|                                     SISTEMA DA BIBLIOTECA                                      |\n");
	printf("--------------------------------------------------------------------------------------------------\n\n");
}

struct Leitor recolheDadosLeitor(int *matricula){

	struct Leitor leitor;
	desenhaCabecalho();//Chama a função que desenha o cabeçalho

	imprimeSubCabecalho(1);
	printf(" DIGITE O NOME DO LEITOR:");
	fflush(stdin);//Limpa o buffer do teclado
	fgets(leitor.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
	leitor.nome[strlen(leitor.nome) - 1] = '\0';
	leitor.matricula = *matricula;
	(*matricula)++;//Incrementa o numero da matricula
	LIMPA_TELA;	
	return leitor;
}

struct Leitor cadastraLeitor(FILE** listaDeLeitores, struct Leitor dadosLeitor){
	
	*listaDeLeitores = fopen("leitores/ListaDeLeitores.dat", "ab");
	
	if (*listaDeLeitores == NULL) {
		dadosLeitor.matricula = 0;
		return dadosLeitor;
	}
	
	dadosLeitor.deletado = ' '; // NAO DELETADO
	
	fwrite(&dadosLeitor, sizeof(struct Leitor), 1, *listaDeLeitores);
	
	fclose(*listaDeLeitores);
	
	return dadosLeitor;

}

struct Livro recolheDadosLivro(int *codLivro){
	
	struct Livro dadosLivro;
	fflush(stdin);//Limpa o buffer do teclado
	desenhaCabecalho();//Chama a função que desenha o cabeçalho

	imprimeSubCabecalho(4);
	printf(" DIGITE O NOME DO LIVRO:");
	fflush(stdin);//Limpa o buffer do teclado
	fgets(dadosLivro.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
	dadosLivro.nome[strlen(dadosLivro.nome) - 1] = '\0';
	dadosLivro.codLivro = *codLivro;
	(*codLivro)++;//Incrementa o numero do CodLivro
	LIMPA_TELA;	
	return dadosLivro;
}

struct Livro cadastraLivro (FILE** listaDeLivros,  struct Livro dadosLivro){
	
	*listaDeLivros = fopen("livros/ListaDeLivros.dat", "ab");
	
	if (*listaDeLivros == NULL) {
		dadosLivro.codLivro = 0;
		return dadosLivro;
	}
	
	dadosLivro.deletado = ' '; // NAO DELETADO
	
	fwrite(&dadosLivro, sizeof(struct Livro), 1, *listaDeLivros);
	
	fclose(*listaDeLivros);
	
	return dadosLivro;
	
}

int abreArquivo(FILE** arquivo, char* nomeDoArquivo, char* modo){
	*arquivo = fopen(nomeDoArquivo, modo);
	if(*arquivo == NULL)
		return 0;
	else
		return 1;
}

void fechaArquivo(FILE** arquivo){
	fclose(*arquivo);
}

void retornaNome(struct Emprestimo *va, int matricula, int codLivro, int op){

	fflush(stdin);//Limpa o buffer do teclado
	
	FILE* listaDeLeitores, *listaDeLivros;
	
	//Declaração de ponteiros para auxiliar na tarefa
	struct Livro  nomeLivroAtual;
	struct Leitor nomeLeitorAtual;
	
	switch(op){
		case 1://caso a opção seja 1 a função vai procurar o nome do livro correspondente ao codLivro
			abreArquivo(&listaDeLivros, "livros/listaDeLivros.dat", "rb");
			while(fread(&nomeLivroAtual, sizeof(struct Livro), 1, listaDeLivros)){
				if(nomeLivroAtual.codLivro == codLivro)
					if(nomeLivroAtual.deletado == ' ')//Verifica se está deletado
						strcpy((*va).livroEmp,nomeLivroAtual.nome);
					else
						(*va).success = '1';
			}
			fechaArquivo(&listaDeLivros);
		break;
		
		case 2://caso a opção seja 2 a função vai procurar o nome do leitor correspondente à matrícula
			abreArquivo(&listaDeLeitores, "leitores/listaDeLeitores.dat", "rb");
			while(fread(&nomeLeitorAtual, sizeof(struct Leitor), 1, listaDeLeitores)){
				if(nomeLeitorAtual.matricula == matricula)
					if(nomeLeitorAtual.deletado == ' ')//Verifica se está deletado
						strcpy((*va).leitor, nomeLeitorAtual.nome);
					else
						(*va).success = '2';
			}
			fechaArquivo(&listaDeLeitores);
		break;
		
	}	
}

struct Emprestimo recolheDadosEmprestimo(int* codEmp){

	struct Emprestimo dadosEmprestimo;
	fflush(stdin);//Limpa o buffer do teclado.
	desenhaCabecalho();//Chama a função que desenha o cabeçalho
	
	imprimeSubCabecalho(7);
	printf(" DIGITE SUA MATRÍCULA: ");
	scanf("%i",&dadosEmprestimo.matricula);	
	
	//Usa a função retornaNome para procurar o nome do leitor correspondente a matricula digitada e copia para dadosEmprestimo.leitor
	retornaNome(&dadosEmprestimo, (dadosEmprestimo.matricula), 0 ,2);
	if(dadosEmprestimo.success == '2')
		return dadosEmprestimo;
	
	LIMPA_TELA;
	//desenhaCabecalho();
	listarLivros();
	imprimeSubCabecalho(7);
	printf(" DIGITE O CODIGO DO LIVRO: ");
	scanf("%i",&dadosEmprestimo.codigoLivro);
	
	//Usa a função retornaNome para procurar o nome do livro correspondente ao codLivro digitada e copia para dadosEmprestimo.livro
	retornaNome(&dadosEmprestimo, 0, (dadosEmprestimo.codigoLivro) ,1);
	
	if(dadosEmprestimo.success == '1')
		return dadosEmprestimo;
	
	dadosEmprestimo.codigo = *codEmp;
	(*codEmp)++;//Incrementa o numero de codEmp
	
	return dadosEmprestimo;
}

struct Emprestimo realizarEmprestimo(FILE** listaDeEmprestimos, struct Emprestimo dadosEmprestimo){
	
	if(dadosEmprestimo.success == '1' || dadosEmprestimo.success == '2')
		return dadosEmprestimo;
	else{
		*listaDeEmprestimos = fopen("emprestimos/listaDeEmprestimos.dat", "ab");
		
		if (*listaDeEmprestimos == NULL) {
			dadosEmprestimo.codigo = 0;
			return dadosEmprestimo;
		}
		
		fwrite(&dadosEmprestimo, sizeof(struct Emprestimo), 1, *listaDeEmprestimos);
		
		fclose(*listaDeEmprestimos);
		
		return dadosEmprestimo;
	}	
}

int listarLivros(){//Função para listar os livros

	struct Livro livroAtual;
	FILE *arquivo;
	
	arquivo = fopen("livros/listaDeLivros.dat", "rb");
	
	if (arquivo == NULL) {
		return 0;
	}
	desenhaCabecalho();
	imprimeSubCabecalho(5);

	while (fread(&livroAtual, sizeof(struct Livro), 1, arquivo))
		if(livroAtual.deletado== ' '){//Verifica se está deletado
			imprimeSubCabecalho(6);
			printf(" %-1c %-30s %9.09i\n",livroAtual.deletado, livroAtual.nome, livroAtual.codLivro);
		}
	
	printf("\n");
	fclose(arquivo);
	
	return 1;

}

int listarLeitores(){//Função para listar os livros

	struct Leitor leitorAtual;
	FILE *arquivo;
	
	arquivo = fopen("leitores/listaDeLeitores.dat", "rb");
	
	if (arquivo == NULL) {
		return 0;
	}
	desenhaCabecalho();
	imprimeSubCabecalho(2);

	while (fread(&leitorAtual, sizeof(struct Leitor), 1, arquivo))
		if(leitorAtual.deletado== ' '){//Verifica se está deletado
			imprimeSubCabecalho(3);
			printf(" %-1c %-30s %9.09i\n",leitorAtual.deletado, leitorAtual.nome, leitorAtual.matricula);
		}
	
	//imprimeSubCabecalho(12);
	
	printf("\n");
	fclose(arquivo);
	
	return 1;

}

void realizarConsulta(int indice, FILE** listaAtual){
	
	//Cria um ponteiros para auxiliar na tarefa
	struct Emprestimo emprestimoAtual;
	struct Livro      livroAtual;
	struct Leitor     leitorAtual;
	
	//Cria um auxiliar de busca
	int procurado, achei;
	
	LIMPA_TELA;
	switch(indice){
		case 1:
			desenhaCabecalho();
			imprimeSubCabecalho(9);
			printf(" DIGITE O CODIGO DO LIVRO: ");
			scanf("%i",&procurado);
			while(fread(&livroAtual, sizeof(struct Livro), 1, *listaAtual)){
				if(livroAtual.codLivro == procurado && livroAtual.deletado == ' '){
					if(achei == 0)imprimeSubCabecalho(6);
					printf(" %-1c %-30s %9.09i\n",livroAtual.deletado, livroAtual.nome, livroAtual.codLivro);
					achei = 1;
				}	
			}
			
			if(!achei)
				printf("\n\n CÓDIGO NÃO ENCONTRADO!\n\n");
			else
				printf("\n\n");
				
			fechaArquivo(&(*listaAtual));
			
		break;
		
		case 2:
			desenhaCabecalho();
			imprimeSubCabecalho(9);
			printf(" DIGITE A MATRÍCULA: ");
			scanf("%i",&procurado);
			while(fread(&leitorAtual, sizeof(struct Leitor), 1, *listaAtual)){
				if(leitorAtual.matricula == procurado && leitorAtual.deletado == ' '){
					if(achei == 0)imprimeSubCabecalho(3);
					printf(" %-1c %-30s %9.09i\n",leitorAtual.deletado, leitorAtual.nome, leitorAtual.matricula);
					achei = 1;
				}	
			}
			
			if(!achei)
				printf("\n\n CÓDIGO NÃO ENCONTRADO!\n\n");
			else
				printf("\n\n");
					
			fechaArquivo(&(*listaAtual));
			
		break;
		
		case 3:
			desenhaCabecalho();
			imprimeSubCabecalho(9);
			printf(" DIGITE SUA MATRÍCULA: ");
			scanf("%i",&procurado);
			while(fread(&emprestimoAtual, sizeof(struct Emprestimo), 1, *listaAtual) ){
				if(emprestimoAtual.matricula == procurado ){
					if(achei == 0){
						printf("\n-------------------------------CONSULTAR EMPRESTIMO-----------------------------------\n");
						imprimeSubCabecalho(8);
					}
					printf(" %3.03i %30s %9.09i %30s %9.09i\n", emprestimoAtual.codigo, emprestimoAtual.leitor, emprestimoAtual.matricula, emprestimoAtual.livroEmp, emprestimoAtual.codigoLivro);
					achei = 1;
				}
			}
			
			if(!achei)
				printf("\n\n CÓDIGO NÃO ENCONTRADO!\n\n");
			else
				printf("\n\n");
					
			fechaArquivo(&(*listaAtual));
			
		break;
	}
}

void realizarAlteracao(int indice, FILE** listaAtual){
	
	//Cria um ponteiros para auxiliar na tarefa
	struct Livro      livroAtual;
	struct Leitor     leitorAtual;
	
	//Cria um auxiliar de busca
	int procurado, achei;

	LIMPA_TELA;
	switch(indice){
		case 1:
			desenhaCabecalho();
			printf("ALTERAÇÃO DE LIVRO\n");
			printf("-------------------\n\n");
			printf(" DIGITE O CODIGO DO LIVRO: ");
			scanf("%i",&procurado);
			LIMPA_TELA;
			while(fread(&livroAtual, sizeof(struct Livro), 1, *listaAtual)){
				if(livroAtual.codLivro == procurado && livroAtual.deletado == ' '){
					desenhaCabecalho();//Chama a função que desenha o cabeçalho
					printf("ALTERAÇÃO DE LIVRO\n");
					printf("-------------------\n\n");
					achei = 1;
					imprimeSubCabecalho(3);
					printf(" %-1c %-30s %9.09i\n\n",livroAtual.deletado, livroAtual.nome, livroAtual.codLivro);
					printf(" DIGITE O NOVO NOME DO LIVRO:");
					fflush(stdin);//Limpa o buffer do teclado
					fgets(livroAtual.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
					livroAtual.nome[strlen(livroAtual.nome) - 1] = '\0';
					fseek(*listaAtual, ((int)(sizeof(livroAtual) * (-1))), SEEK_CUR);//TA DANDO WARNING(QUERO SABER POQUE)
					fwrite(&livroAtual, sizeof(struct Livro), 1, *listaAtual);
					fseek(*listaAtual, 0, SEEK_CUR);
				}	
			}
			printf("\n\n");
			
			if(!achei)
				printf("CÓDIGO NÃO ENCONTRADO!");
				
			fclose(*listaAtual);
			
		break;
		
		case 2:
			desenhaCabecalho();
			printf("ALTERAÇÃO DE LEITOR\n");
			printf("------------------\n\n");
			printf(" DIGITE A MATRÍCULA DO LEITOR: ");
			scanf("%i",&procurado);
			LIMPA_TELA;
			while(fread(&leitorAtual, sizeof(struct Leitor), 1, *listaAtual)){
				if(leitorAtual.matricula == procurado && leitorAtual.deletado == ' '){
					desenhaCabecalho();//Chama a função que desenha o cabeçalho
					printf("ALTERAÇÃO DE LEITOR\n");
					printf("------------------\n\n");
					achei = 1;
					imprimeSubCabecalho(3);
					printf(" %-1c %-30s %9.09i\n\n",leitorAtual.deletado, leitorAtual.nome, leitorAtual.matricula);
					printf(" DIGITE O NOVO NOME DO LEITOR:");
					fflush(stdin);//Limpa o buffer do teclado
					fgets(leitorAtual.nome,TS,stdin);//FAZ A LEITURA DE UMA STRING DIGITADA PELO USUÁRIO.
					leitorAtual.nome[strlen(leitorAtual.nome) - 1] = '\0';
					fseek(*listaAtual, ((int)(sizeof(leitorAtual) * -1)), SEEK_CUR);//TA DANDO WARNING(QUERO SABER POQUE)
					fwrite(&leitorAtual, sizeof(struct Leitor), 1, *listaAtual);
					fseek(*listaAtual, 0, SEEK_CUR);
				}	
			}
			printf("\n\n");	
			
			if(!achei)
				printf("CÓDIGO NÃO ENCONTRADO!");
				
			fclose(*listaAtual);
			
		break;

	}
}

void realizarExclusao(int indice, FILE** listaAtual){
	
	//Cria um ponteiros para auxiliar na tarefa
	struct Livro      livroAtual;
	struct Leitor     leitorAtual;
	
	//Cria um auxiliar de busca
	int procurado, achei;

	LIMPA_TELA;
	switch(indice){
		case 1:
			desenhaCabecalho();
			printf("EXCLUSÃO DE LIVRO\n");
			printf("-----------------\n\n");
			printf(" DIGITE O CODIGO DO LIVRO: ");
			scanf("%i",&procurado);
			LIMPA_TELA;
			while(fread(&livroAtual, sizeof(struct Livro), 1, *listaAtual)){
				if(livroAtual.codLivro == procurado && livroAtual.deletado == ' '){
					desenhaCabecalho();//Chama a função que desenha o cabeçalho
					printf("EXCLUSÃO DE LIVRO\n");
					printf("-----------------\n\n");
					achei = 1;
					
					livroAtual.deletado = '*';
					
					fseek(*listaAtual, ((int)(sizeof(livroAtual) * (-1))), SEEK_CUR);//TA DANDO WARNING(QUERO SABER POQUE)
					fwrite(&livroAtual, sizeof(struct Livro), 1, *listaAtual);
					fseek(*listaAtual, 0, SEEK_CUR);
				}	
			}
			
			if(!achei)
				printf("CÓDIGO NÃO ENCONTRADO!");
			else
				printf("LIVRO MOVIDO PARA LIXEIRA!\n É POSSÍVEL RESTAURÁ-LO DEPOIS.\n\n");
				
			fclose(*listaAtual);
			
		break;
		
		case 2:
			desenhaCabecalho();
			printf("EXCLUSÃO DE LEITOR\n");
			printf("------------------\n\n");
			printf(" DIGITE A MATRÍCULA DO LEITOR: ");
			scanf("%i",&procurado);
			LIMPA_TELA;
			while(fread(&leitorAtual, sizeof(struct Leitor), 1, *listaAtual)){
				if(leitorAtual.matricula == procurado && leitorAtual.deletado == ' '){
					desenhaCabecalho();//Chama a função que desenha o cabeçalho
					printf("EXCLUSÃO DE LEITOR\n");
					printf("------------------\n\n");
					achei = 1;
					
					leitorAtual.deletado = '*';
					
					fseek(*listaAtual, ((int)(sizeof(leitorAtual) * -1)), SEEK_CUR);//TA DANDO WARNING(QUERO SABER POQUE)
					fwrite(&leitorAtual, sizeof(struct Leitor), 1, *listaAtual);
					fseek(*listaAtual, 0, SEEK_CUR);
				}	
			}
			
			if(!achei)
				printf("CÓDIGO NÃO ENCONTRADO!");
			else	
				printf(" LEITOR MOVIDO PARA LIXEIRA!\n É POSSÍVEL RESTAURÁ-LO DEPOIS.\n\n");
				
			fclose(*listaAtual);
			
		break;

	}
}

void imprimeSubCabecalho(int sessao){
	switch(sessao){
		case 1:// Cadastro de Leitores
			printf("CADASTRO DE LEITOR\n");
			printf("------------------\n\n");
		break;
		
		case 2://listagem de Leitores
			printf("LISTA DE LEITORES\n");
			printf("-----------------\n\n");
		break;
		
		case 3://Apresentação de Leitores
			printf(" X LEITOR                         MATRÍCULA\n");
			printf(" - ------------------------------ ---------\n");
		break;
		
		case 4:// Cadastro de Livros
			printf("CADASTRO DE LIVRO\n");
			printf("-----------------\n\n");
		break;
		
		case 5://listagem de Livros
			printf("LISTA DE LIVROS\n");
			printf("---------------\n\n");
		break;
		
		case 6:///Apresentação de Livros
			printf(" X LIVRO                          COD.LIVRO\n");
			printf(" - ------------------------------ ---------\n");
		break;
		
		case 7://Realização de Empréstimo
			printf("EMPRÉSTIMO\n");
			printf("----------\n\n");
		break;
		
		case 8://Listagem de Empréstimo
			printf(" COD                         LEITOR MATRÍCULA LIVRO                          COD.LIVRO\n");
			printf(" --- ------------------------------ --------- ------------------------------ ---------\n");
		break;
		
		case 9://Realização de Consulta
			printf("CONSULTA\n");
			printf("----------\n\n");
		break;
		
		case 10://Realização de Alteração
			printf("ALTERAÇÃO\n");
			printf("----------\n\n");
		break;		
		
		case 11:
			printf("EXCLUSÃO\n");
			printf("--------\n\n");
		break;
		
		case 12://Erro listagem de Leitores
			printf("---ERRO: IMPOSSÍVEL LISTAR LEITORES---\n\n\n");
			printf(" NENHUM LEITOR CADASTRADO ATE O MOMENTO!\n\n");
			printf("\n\n");
		break;
		
		case 13://Erro listagem de Leitores
			printf("---ERRO: IMPOSSÍVEL LISTAR LIVROS---\n\n\n");
			printf(" NENHUM LIVRO CADASTRADO ATE O MOMENTO!\n\n");
			printf("\n\n");
		break;
	}
}
