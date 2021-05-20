#ifndef SISTEMA_H
#define SISTEMA_H

#include "livros.h"
#include "alunos.h"
#include "arquivos.h"
#define MAX_ALUGUEIS_POR_PESSOA  2

typedef struct cliente{
    Aluno aluno;
    Livro livro[MAX_ALUGUEIS_POR_PESSOA];
    
}  Cliente;



void criaCliente();
void buscaCliente(int registroAcademico);

#endif


