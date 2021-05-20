
#ifndef ALUNOS_H
#define ALUNOS_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "arquivos.h"
#include "menus.h"
#define MAX_EMAIL 50
#define MAX_NOME_ALUNO 70


//Descricao a mostrar para o mundo
typedef struct aluno
{
    char nomeCompleto[MAX_NOME_ALUNO];
    char registroAcademico[19];
    long int numeroCelular;
} Aluno;

void adicionarAluno();
void listarTodosAlunos();
void buscaAlunoRegistroAcademico(); 
void alteraDadosAluno();
void excluirAluno();

#endif