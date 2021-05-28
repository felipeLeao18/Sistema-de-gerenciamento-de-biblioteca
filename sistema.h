#ifndef SISTEMA_H
#define SISTEMA_H


#include "alunos.h"
#include "arquivos.h"
#include <time.h>

#include "livros.h"

typedef struct cliente
{
    Aluno aluno;
    Livro livro[3];
    int quantidadeLivros;
    struct tm *myTime;
    int diaAluguel, mesAluguel, anoAluguel;
    int diaDevolucao, mesDevolucao, anoDevolucao;
} Cliente;

time_t tempoAtual;

void criaCliente();
void buscaCliente();
void receberLivro();
void abrirInstrucoes();
void tiraLivroEstoque();
void listarTodosClientes();
#endif

/*//TODO
Anunciar perda 
    
    Passar ra do aluno
    passar nome do(s) livro(s) perdidos
    diminuir quantidade em -1 dos livros perdidos; - ARQUIVO LIVROS
    */


