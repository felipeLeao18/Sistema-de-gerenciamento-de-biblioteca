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
void achaOcorrencia(bool achei, char *registroAcademico)
{

    if (achei == false)
        printf("O aluno com registro academico %s nao possui alugueis pendentes\n", registroAcademico);
}

void cadastraData(Cliente *cliente)
{

    time(&tempoAtual);
    cliente->myTime = localtime(&tempoAtual);
    cliente->diaAluguel = cliente->myTime->tm_mday;
    cliente->mesAluguel = cliente->myTime->tm_mon + 1;
    cliente->anoAluguel = cliente->myTime->tm_year + 1900;
    cliente->diaDevolucao = cliente->myTime->tm_mday + 7;
    if (cliente->diaDevolucao > 31)
    {
        cliente->mesDevolucao = cliente->myTime->tm_mon + 2;
        cliente->diaDevolucao -= 31;
    }
    else
    {
        cliente->mesDevolucao = cliente->myTime->tm_mon + 1;
    }

    cliente->anoDevolucao = cliente->anoAluguel;
}

void preencheListaDeClientesComArquivo(Cliente *cliente, FILE *file, Cliente *arrayClientes)
{
    int contador = 0;
    fseek(file, 0L, SEEK_SET);
    while (fread(cliente, sizeof(Cliente), 1, file) > 0)
    {
        arrayClientes[contador] = *cliente;

        contador++;
    }
}

int retornaQntClientesEmArquivo(FILE *file, size_t tamanhoDoArquivo)
{

    int quantidadeDeRegistros;
    quantidadeDeRegistros = (tamanhoDoArquivo / sizeof(Cliente));
    return quantidadeDeRegistros;
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
            break;
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
    cadastraData(cliente);
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
            printf("Aluguel: %i/%i/%i\nDevolucao:%i/%i/%i\n ", cliente.diaAluguel, cliente.mesAluguel, cliente.anoAluguel, cliente.diaDevolucao, cliente.mesDevolucao, cliente.anoDevolucao);
            printf("- - - - - - - - - - - - - - - - - -\n");

            fclose(file);
            break;
        }
    }
    achaOcorrencia(achei, registroAcademico);
}

Cliente retornaCliente(char *RegistroAcademico)
{
    FILE *file = abreArquivo("arquivoSistema.dat", "rb");
    Cliente cliente;
    bool achei = false;

    while (fread(&cliente, sizeof(Cliente), 1, file) > 0)
    {
        if (comparaString(cliente.aluno.registroAcademico, RegistroAcademico))
        {
            achei = true;

            fseek(file, -sizeof(Cliente), SEEK_CUR);
            return cliente;
        }
    }

    if (achei == false)
    {
        printf("O aluno nao possui livros alugados\n");
    }
}

void aumentaQtdLivro(char *caminho)
{

    Livro livro;

    FILE *fileLivros = abreArquivo("arquivoLivros.dat", "rb+");
    int index = 0;

    while (fread(&livro, sizeof(Livro), 1, fileLivros) > 0)
    {
        if (comparaString(caminho, livro.nome))
        {
            fseek(fileLivros, -sizeof(livro), SEEK_CUR);
            livro.quantidade += 1;
            fwrite(&livro, sizeof(Livro), 1, fileLivros);
            break;
        }
    }
    fclose(fileLivros);
}

void receberLivro()
{
    char registroAcademico[19];
    printf("Digite o registro do academico do aluno\n");
    scanf("%s", &registroAcademico);
    Cliente cliente = retornaCliente(registroAcademico);
    int i;
    for (i = 0; i < cliente.quantidadeLivros; i++)
    {
        aumentaQtdLivro(cliente.livro[i].nome);
        printf("Livro %s recebido com sucesso\n", cliente.livro[i].nome);
    }
}

void listarTodosClientes()
{

    FILE *file = abreArquivo("arquivoSistema.dat", "rb");

    size_t tamanhoDoArquivo = retornaTamanhoArquivo(file);
    Cliente cliente;

    int registrosDeClientes = retornaQntClientesEmArquivo(file, tamanhoDoArquivo);

    Cliente *arrayClientes = (Cliente *)malloc(tamanhoDoArquivo);
    if (!arrayClientes)
    {
        printf("Erro ao alocar memoria\n");
    }

    preencheListaDeClientesComArquivo(&cliente, file, arrayClientes);
    fclose(file);

    int index1, index2;

    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    for (index1 = 0; index1 < registrosDeClientes; index1++)
    {

        printf("NOME ALUNO: %s\n", arrayClientes[index1].aluno.nomeCompleto);
        printf("Quantidade de livros Alugados: %d\n",arrayClientes[index1].quantidadeLivros);
        printf("Livros alugados:\n");

        for (index2 = 0; index2 < arrayClientes[index1].quantidadeLivros; index2++)
        {
            printf("%s, autor: %s, editora: %s\n", cliente.livro[index2].nome, cliente.livro[index2].autor, cliente.livro[index2].editora);
        }
        printf("Data de aluguel: %i/%i/%i\nData de devolucao: %i/%i/%i\n ", arrayClientes[index1].diaAluguel, arrayClientes[index1].mesAluguel, arrayClientes[index1].anoAluguel, arrayClientes[index1].diaDevolucao, arrayClientes[index1].mesDevolucao, arrayClientes[index1].anoDevolucao);
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    }
    free(arrayClientes);
}

void abrirTxt(); // TODO ESCREVER TXT COM LIVROS

void excluirRegistro()
{

    FILE *file = abreArquivo("arquivoSistema.dat", "rb");
    FILE *fileTemporario = abreArquivo("arquivoSistemaTemporario.dat", "wb");

    Cliente cliente;
    Cliente *arrayClientes;

    int index;
    char registroAcademico[19];
    bool achei = false;

    size_t tamanhoArquivo = retornaTamanhoArquivo(file);
    int quantidadeDeRegistros = retornaQntClientesEmArquivo(file, tamanhoArquivo);
    arrayClientes = (Cliente *)malloc(sizeof(tamanhoArquivo));

    preencheListaDeClientesComArquivo(&cliente, file, arrayClientes);

    printf("Digite o RA do aluno que ira devolver os livros:\n");
    scanf("%s", &registroAcademico);

    for (index = 0; index < quantidadeDeRegistros; index++)
    {
        if (comparaString(arrayClientes[index].aluno.registroAcademico, registroAcademico))
        {
            achei = true;
            printf("Registro excluido do sistema!\n");
            continue;
        }
        else
            fwrite(&arrayClientes[index], sizeof(arrayClientes[index]), 1, fileTemporario);
    }

    fclose(file);
    fclose(fileTemporario);
    renomeiaArquivoTemporario("arquivoSistema.dat", "arquivoSistemaTemporario.dat");
    free(arrayClientes);

    achaOcorrencia(achei, registroAcademico);

    printf("Pressione qualquer tecla para sair\n");
    getch();
}
