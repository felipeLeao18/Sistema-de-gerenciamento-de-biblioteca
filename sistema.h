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

#endif


