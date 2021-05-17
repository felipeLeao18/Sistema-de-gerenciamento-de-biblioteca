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

void AlugaLivro(); // DIMINUIR QUANTIDADE DO LIVRO EM -1 NO ARQUIVOLIVROS
void verificaDisponibilidade();
void recebeLivro();                 //AUMENTAR QUANTIDADE DO LIVRO EM +1 NO ARQUIVO LIVROS;
void abrirInstrucoes();