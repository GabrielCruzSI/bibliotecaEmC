#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(void){
	remove("leitores/listaDeLeitores.dat");
	remove("livros/listaDeLivros.dat");
	remove("emprestimos/listaDeEmprestimos.dat");
	remove("cont/cont.dat");
	printf("feito");
	return 0;
}
