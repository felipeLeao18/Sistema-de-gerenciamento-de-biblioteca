#include "sistema.h"

int comparaString(const char *original, const char *buscada)
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
}

int verificaOcorrenciaRegistroAcademico(char *registroAcademico)
{
    FILE *file = abreArquivo("arquivoSistema.dat", "rb");
    Cliente cliente;
    bool achei = false;

    while (fread(&cliente, sizeof(Cliente), 1, file))
    {
        if (comparaString(cliente.aluno.registroAcademico, registroAcademico))
        {
            fseek(file, -sizeof(Cliente), SEEK_CUR);
            achei = true;
            break;
        }
    }
    if (achei)
    {
        printf("O aluno '%s' com Registro '%s' ja possui alugueis pendentes\n", cliente.aluno.nomeCompleto, cliente.aluno.registroAcademico);
        return 1;
    }
    else
    {

        return 0;
    }
}

Livro retornaLivro(char *nome)
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    Livro livro;
    bool achei = false;

    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaString(livro.nome, nome))
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
    else
    {
        printf("Livro nao encontrado, confira os dados e tente novamente!\n");
        exit(1);
    }
}

Aluno retornaAluno(char *registroAcademico)
{

    FILE *file = abreArquivo("arquivoAlunos.dat", "rb");
    Aluno aluno;
    bool achei = false;

    while (fread(&aluno, sizeof(Aluno), 1, file) > 0)
    {
        if (comparaString(aluno.registroAcademico, registroAcademico))
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
    else
    {
        printf("Aluno nao encontrado no sistema, confira os dados e tente novamente!\n");
        exit(1);
    }
}
bool verificaDisponibilidade(char *nomeLivro)
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    Livro livro;
    bool achei = false;

    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaString(livro.nome, nomeLivro))
        {
            achei = true;

            fseek(file, -sizeof(Livro), SEEK_CUR);
            break;
        }
    }

    fclose(file);
    if (livro.quantidade >= 1)
    {
        return true;
    }
    else
    {
        printf("O livro '%s' nao possui quantidade suficiente para aluguel!\n", nomeLivro);
        return false;
    }
}

bool inputCliente(Cliente *cliente)
{
    int index;
    

    printf("Digite o Registro academico do aluno que ira alugar o(s) livro(s):\n");
    scanf(" %[^\n]", cliente->aluno.registroAcademico);
    cliente->aluno = retornaAluno(cliente->aluno.registroAcademico);

    if (verificaOcorrenciaRegistroAcademico(cliente->aluno.registroAcademico) == 1)
    {
        printf("Confira os dados e tente novamente!\n");
        return false;
    }

    printf("Digite a quantidade de livros que o aluno ira alugar:\n");
    scanf("%d", &cliente->quantidadeLivros);

    for (index = 0; index < cliente->quantidadeLivros; index++)
    {
        printf("Digite o nome do(s) livro(s) a serem alugados:\n");
        scanf(" %[^\n]", &cliente->livro[index].nome);
        if (verificaDisponibilidade(cliente->livro[index].nome))
        {

            cliente->livro[index] = retornaLivro(cliente->livro[index].nome);
            tiraLivroEstoque(cliente->livro[index].nome);
        }
        else
        {
            printf("Quantidade para livro '%s' indisponivel para aluguel\n", cliente->livro[index].nome);
            return false;
        }
    }
    return true;
}

void criaCliente()
{
    FILE *file = abreArquivo("arquivoSistema.dat", "ab");
    Cliente *cliente;
    cliente = (Cliente *)malloc(sizeof(Cliente));
    if (inputCliente(cliente))
    {

        fwrite(cliente, sizeof(Cliente), 1, file);
        fclose(file);

        free(&cliente);
    }
}

void buscaCliente()
{
    FILE *file = abreArquivo("arquivoSistema.dat", "rb");
    Cliente cliente;

    bool achei = false;
    int index;

    char registroAcademico[19];
    printf("Digite o RA do aluno a ser buscado\n");
    scanf(" %[^\n]", registroAcademico);

    while (fread(&cliente, sizeof(Cliente), 1, file) > 0)
    {
        if (comparaString(cliente.aluno.registroAcademico, registroAcademico))

        {

            achei = true;

            fseek(file, -sizeof(Cliente), SEEK_CUR);

            printf("\n- - - - - - - - - - - - - - - - - -\n");

            printf("NOME ALUNO: %s\n\n", cliente.aluno.nomeCompleto);

            printf("Livro(s) alugado(s):\n");
            for (index = 0; index < cliente.quantidadeLivros; index++)
            {
                printf("%s, autor: %s, editora: %s\n", cliente.livro[index].nome, cliente.livro[index].autor, cliente.livro[index].editora);
            }

            printf("- - - - - - - - - - - - - - - - - -\n");

            fclose(file);
        }
    }
}
