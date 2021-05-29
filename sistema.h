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
void excluirRegistro(char registroAcademico[19]);
#endif




