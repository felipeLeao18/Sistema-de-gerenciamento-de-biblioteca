#include "sistema.h"

int comparaNomesLivro(const char *original, const char *buscada)
{
    unsigned int tamanhoStrOriginal = strlen(original);
    if (strlen(buscada) != tamanhoStrOriginal)
        return 0;
    for (unsigned int i = 0; i < tamanhoStrOriginal; i++)
        if (tolower(original[i]) != tolower(buscada[i]))
            return 0;
    return 1;
}

void tiraLivroEstoque(char *nomeLivro)
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb+");
    bool achei = false;
    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaString(livro.nome, nomeLivro))
        {
            achei = true;

            fseek(file, -sizeof(Livro), SEEK_CUR);
            livro.quantidade -= 1;
            fwrite(&livro, sizeof(Livro), 1, file);
            fclose(file);
        }
    }

    //TODO VERIFICAOCORRENCIA;
}

Livro retornaLivro(char *nome)
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    Livro livro;
    bool achei = false;

    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaNomesLivro(livro.nome, nome))
        {
            achei = true;

            fseek(file, -sizeof(Livro), SEEK_CUR);
            break;
        }
    }
    fclose(file);

    if (achei)
    {
        return livro;
    }
}

Aluno retornaAluno(int registroAcademico)
{

    FILE *file = abreArquivo("arquivoAlunos.dat", "rb");
    Aluno aluno;
    bool achei = false;

    while (fread(&aluno, sizeof(Aluno), 1, file) > 0)
    {
        if (aluno.registroAcademico == registroAcademico)
        {

            achei = true;

            fseek(file, -sizeof(Aluno), SEEK_CUR);
            break;
        }
    }

    fclose(file);

    if (achei)
    {
        return aluno;
    }
}

void criaCliente()
{
    int index;

    FILE *file = abreArquivo("arquivoSistema.dat", "ab");
    Cliente *cliente;
    cliente = (Cliente *)malloc(sizeof(Cliente));

    cliente->aluno = retornaAluno(7);

    cliente->livro[0] = retornaLivro("clean coda");

    tiraLivroEstoque("clean coda");

    cliente->livro[1] = retornaLivro("matematica basica");

    tiraLivroEstoque("Matematica basica");

    fwrite(cliente, sizeof(Cliente), 1, file);
    fclose(file);
    free(&cliente);
}

void buscaCliente(int registroAcademico)
{
    FILE *file = abreArquivo("arquivoSistema.dat", "rb");
    Cliente cliente;
    bool achei = false;
    printf("ue");
    while (fread(&cliente, sizeof(Cliente), 1, file) > 0)
    {
        if (cliente.aluno.registroAcademico == registroAcademico)

        {

            achei = true;

            fseek(file, -sizeof(Cliente), SEEK_CUR);

            printf("\n- - - - - - - - - - - - - - - - - -\n");

            printf("NOME ALUNO: %s\n", cliente.aluno.nomeCompleto);
            printf("NOME LIVRO 1: %s\n", cliente.livro[0].nome);
            printf("EDITORA LIVRO 1: %s\n", cliente.livro[0].editora);

            printf("NOME LIVRO 2: %s\n", cliente.livro[1].nome);
            printf("EDITORA LIVRO 2: %s\n", cliente.livro[1].editora);

            printf("- - - - - - - - - - - - - - - - - -\n");

            fclose(file);
        }
    }
}

bool verificaDisponibilidade(char *nomeLivro)
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb+");
    Livro livro;
    bool achei = false;

    char nomeLivroAlterado[MAX_ATRIBUTO_LIVRO];
    printf("Digite o nome do livro a ser alterado:\n");
    scanf(" %[^\n]", nomeLivroAlterado);

    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaString(livro.nome, nomeLivroAlterado))
        {
            achei = true;
            printf("Registro encontrado! Digite os novos dados do livro: '%s' abaixo:\n\n", livro.nome);

            fseek(file, -sizeof(Livro), SEEK_CUR);
        }
    }

    fclose(file);
    if (livro.quantidade >= 1)
    {
        return true;
    }
}