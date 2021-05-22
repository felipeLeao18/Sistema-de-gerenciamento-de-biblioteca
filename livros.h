#ifndef LIVROS_H
#define LIVROS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include "arquivos.h"

#define MAX_ATRIBUTO_LIVRO 40
#define MAX_TAMANHO_GENERO 20


//DESCRICAO A MOSTRAR PARA O MUNDO;
typedef struct livro
{
    char nome[MAX_ATRIBUTO_LIVRO];
    char genero[MAX_TAMANHO_GENERO];
    char autor[MAX_ATRIBUTO_LIVRO];
    char editora[MAX_ATRIBUTO_LIVRO];
    int codigo; // -> STRINGGGGGGGGGGG
    int quantidade;
} Livro;


void adicionarLivro();
void listarTodosLivros();
void buscarLivroPorNome();
void alteraDadosLivro();
void excluirLivro();

#endif
