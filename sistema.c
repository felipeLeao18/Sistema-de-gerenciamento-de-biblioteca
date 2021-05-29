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
    if (achei == false)
    {
        printf("Livro nao encontrado no sistema");
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
    return 0;
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
        printf("Pressione qualquer tecla para sair\n");
        getch();

        menuInicial();
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
    
        printf("Aluno nao encontrado no sistema, confira os dados e tente novamente!\n");
        printf("Pressione qualquer tecla para sair\n");
        getch();
       
    
}

bool verificaDisponibilidadeLivro(char *nomeLivro)
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

    if (cliente->quantidadeLivros > 3)
    {
        printf("Nao e possivel alugar mais de 3 livros por Registro academico\n");
        return false;
    }

    for (index = 0; index < cliente->quantidadeLivros; index++)
    {
        printf("Digite o nome do(s) livro(s) a serem alugados:\n");
        scanf(" %[^\n]", &cliente->livro[index].nome);
        if (verificaDisponibilidadeLivro(cliente->livro[index].nome))
        {

            cliente->livro[index] = retornaLivro(cliente->livro[index].nome);
            tiraLivroEstoque(cliente->livro[index].nome);
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
        printf("Aluguel criado com sucesso\n", cliente->aluno.nomeCompleto);

        free(&cliente);
    }

    printf("Pressione qualquer tecla para sair\n");
    getch();
}

void mostrarCliente(Cliente *cliente)
{

    printf("\nNOME ALUNO: %s - Registro academico: %s\n", cliente->aluno.nomeCompleto, cliente->aluno.registroAcademico);
    int index;
    printf("Livro(s) alugado(s) %d:\n", cliente->quantidadeLivros);
    for (index = 0; index < cliente->quantidadeLivros; index++)
    {
        printf("%s, autor: %s, editora: %s\n", cliente->livro[index].nome, cliente->livro[index].autor, cliente->livro[index].editora);
    }
    printf("Aluguel: %i/%i/%i\nDevolucao:%i/%i/%i\n", cliente->diaAluguel, cliente->mesAluguel, cliente->anoAluguel, cliente->diaDevolucao, cliente->mesDevolucao, cliente->anoDevolucao);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
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

            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

            mostrarCliente(&cliente);

            fclose(file);
            break;
        }
    }
    achaOcorrencia(achei, registroAcademico);

    printf("Pressione qualquer tecla para sair\n");
    getch();
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

            fclose(file);
            return cliente;
        }
    }
    fclose(file);

}

void aumentaQtdLivroEmArquivoLivro(char *nomeDoLivro)
{

    Livro livro;

    FILE *fileLivros = abreArquivo("arquivoLivros.dat", "rb+");
    int index = 0;

    while (fread(&livro, sizeof(Livro), 1, fileLivros) > 0)
    {
        if (comparaString(nomeDoLivro, livro.nome))
        {
            fseek(fileLivros, -sizeof(livro), SEEK_CUR);
            livro.quantidade += 1;
            fwrite(&livro, sizeof(Livro), 1, fileLivros);
            break;
        }
    }
    fclose(fileLivros);
}

int OrdenaRegistrosCadastrados(const void *registro1, const void *registro2)

{
    const Cliente *ponteiroRegistro1 = registro1;
    const Cliente *ponteiroRegistro2 = registro2;
    return strcmp(ponteiroRegistro1->aluno.nomeCompleto, ponteiroRegistro2->aluno.nomeCompleto);
}

void listarTodosClientes()
{

    FILE *file = abreArquivo("arquivoSistema.dat", "rb");

    int index;
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

    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    qsort(arrayClientes, registrosDeClientes, sizeof(Cliente), OrdenaRegistrosCadastrados);
    for (index = 0; index < registrosDeClientes; index++)
        mostrarCliente(&arrayClientes[index]);

    free(arrayClientes);

    printf("Pressione qualquer tecla para sair\n");
    getch();
}

void excluirRegistro(char *registroAcademico)
{

    FILE *file = abreArquivo("arquivoSistema.dat", "rb");
    FILE *fileTemporario = abreArquivo("arquivoSistemaTemporario.dat", "wb");

    Cliente cliente;
    Cliente *arrayClientes;

    int index;

    bool achei = false;

    size_t tamanhoArquivo = retornaTamanhoArquivo(file);
    int quantidadeDeRegistros = retornaQntClientesEmArquivo(file, tamanhoArquivo);
    arrayClientes = (Cliente *)malloc(tamanhoArquivo);

    preencheListaDeClientesComArquivo(&cliente, file, arrayClientes);

    for (index = 0; index < quantidadeDeRegistros; index++)
    {
        if (comparaString(arrayClientes[index].aluno.registroAcademico, registroAcademico))
        {
            achei = true;
            printf("Registro excluido do sistema!\n");
            continue;
        }
        fwrite(&arrayClientes[index], sizeof(arrayClientes[index]), 1, fileTemporario);
    }
    free(arrayClientes);

    fclose(file);
    fclose(fileTemporario);

    renomeiaArquivoTemporario("arquivoSistema.dat", "arquivoSistemaTemporario.dat");

    achaOcorrencia(achei, registroAcademico);

    printf("Pressione qualquer tecla para sair\n");
    getch();
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
        aumentaQtdLivroEmArquivoLivro(cliente.livro[i].nome);
        printf("Livro %s recebido com sucesso\n", cliente.livro[i].nome);
    }

    excluirRegistro(registroAcademico);
}

void abrirInstrucoes()
{
    char ch;
    FILE *file = abreArquivo("instrucoes.txt", "r");
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);

    fclose(file);
    printf("Pressione qualquer tecla para sair\n");
    getch();
}
