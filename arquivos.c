#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"

void trataErrosArquivo(FILE *file)
{
    if (!file)
    {
        printf("Houve um erro e o arquivo nao pode ser aberto!!!\n");
        exit(1);
    }
}

FILE *abreArquivo(char *caminho, char *tipoDeAbertura)
{
    FILE *file;
    file = fopen(caminho, tipoDeAbertura);
    trataErrosArquivo(file);

    return file;
}

void renomeiaArquivoTemporario(char *caminhoArquivoOriginal, char *caminhoArquivoTemporario)
{
    remove(caminhoArquivoOriginal);
    rename(caminhoArquivoTemporario, caminhoArquivoOriginal);
}



size_t retornaTamanhoArquivo(FILE *file)
{
    fseek(file, 0, SEEK_END);
    return ftell(file);
}