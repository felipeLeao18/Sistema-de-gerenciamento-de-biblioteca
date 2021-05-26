#ifndef SISTEMA_H
#define SISTEMA_H

#include "livros.h"
#include "alunos.h"
#include "arquivos.h"


typedef struct cliente{
    Aluno aluno;
    Livro livro[3];
    int quantidadeLivros;       
}  Cliente;



void criaCliente();
void buscaCliente();
void receberLivro();
void anunciarPerda();
void abrirInstrucoes();

#endif

 
/*Anunciar perda 

    Passar ra do aluno
    passar nome do(s) livro(s) perdidos
    diminuir quantidade em -1 dos livros perdidos; - ARQUIVO LIVROS
    */


/*Receber livro
    ler ra do aluno entregando os livros;
    aumentar quantidade em + 1 no arquivoLivros
    excluir registro do aluno no arquivoSistema;
*/

/*TODO
    IMPLEMENTAR DATA DE ENTRADA DOS LIVROS E SALVAR NO REGISTRO O PRAZO DE 7 DIAS PRA FRENTE DA DATA DE LOCACAO*/