#ifndef SISTEMA_H
#define SISTEMA_H

#include "livros.h"
#include "alunos.h"
#include "arquivos.h"
typedef struct Cliente{
    Aluno aluno;
    Livro livro;
    int quantidadeDeLivros;
}   Sistema;

#endif

void AlugaLivro();