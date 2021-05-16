#include "sistema.h"

Sistema *alugaLivro(int quantidadeDeLivros);

Sistema *alugaLivro(int quantidadeDeLivros)
{
    Sistema *sistema = (Sistema *)malloc(sizeof(Sistema) + ((sizeof(Livro) * quantidadeDeLivros)));
    return sistema;
}

Aluno buscaRegistroDeAluno(int registroAcademico)
{
    FILE *file = abreArquivo("arquivoAlunos.dat", "rb");
    Aluno aluno;
    while (fread(&aluno, sizeof(Aluno), 1, file) > 0)
    {
        if (aluno.registroAcademico == registroAcademico)
        {
            printf("Registro encontrado, aluno: %s, RA: %d;\n", aluno.nomeCompleto, aluno.numeroCelular);

            fseek(file, -sizeof(Aluno), SEEK_CUR);
            return aluno;
            fclose(file);
        }
    }
}

void AlugaLivro()
{
    // FILE *file = fopen("arquivoSistema.dat", "ab");
    // Aluno aluno = buscaRegistroDeAluno(7777);
    // Sistema sistema;
    // sistema.aluno = aluno;
    // fwrite(&sistema.aluno, sizeof(sistema.aluno), 1, file);

    // fclose(file);
}
