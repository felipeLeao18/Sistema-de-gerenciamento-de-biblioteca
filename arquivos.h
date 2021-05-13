#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>

FILE *abreArquivo(char *caminho, char *tipoDeAbertura);
void renomeiaArquivoTemporario(char *caminhoArquivoOriginal, char *caminhoArquivoTemporario);
void trataErroArquivo(FILE *file);
size_t retornaTamanhoArquivo(FILE *file);
#endif 