#include "livros.h"

void lancaExcecaoEmCriacaoDeLista(int quantidade);
int tratamentoErroAlocarVetorDeLivros(Livro *livro);
bool naoExisteLivro(Livro *livro);
Livro *alocaMemoriaParaListaDeLivros(int quantidadeDeLivros);
Livro *criaListaDeLivros(int);
void liberaListaDeLivros(Livro **l);
void mostrarLivro(Livro livro);
void preencheListaDeLivrosComArquivo(Livro *livro, FILE *file, Livro *arrayLivros);
int comparaString(const char *a, const char *b);
void buscaOcorrencia(bool encontraOcorrencia, char *nome);
int retornaQntLivrosEmArquivo(FILE *file, size_t tamanhoDoArquivo);

Livro *alocaMemoriaParaListaDeLivros(int quantidadeDeLivros)
{
    Livro *livro = (Livro *)malloc(sizeof(Livro) * quantidadeDeLivros);
    return livro;
}

bool naoExisteLivro(Livro *livro)
{

    if (!livro)
    {
        return true;
    }
    return false;
}

void lancaExcecaoEmCriacaoDeLista(int quantidade)
{

    fprintf(stderr, "Erro de alocacao com %d livros\n", quantidade);
}

Livro *criaListaDeLivros(int quantidadeDeLivros)
{
    Livro *lista = alocaMemoriaParaListaDeLivros(quantidadeDeLivros);
    if (naoExisteLivro(lista))
    {
        lancaExcecaoEmCriacaoDeLista(quantidadeDeLivros);
        return NULL;
    }
    return lista;
}

int tratamentoErroAlocarVetorDeLivros(Livro *livro)
{
    if (!livro)
    {
        printf("Nao foi possivel alocar memoria para o vetor de livros");
        return 1;
    }

    return 0;
}

void liberaListaDeLivros(Livro **l)
{
    free(*l);
}

void preencheListaDeLivrosComArquivo(Livro *livro, FILE *file, Livro *arrayLivros)
{
    int contador = 0;
    fseek(file, 0L, SEEK_SET);
    while (fread(livro, sizeof(Livro), 1, file) > 0)
    {
        arrayLivros[contador] = *livro;

        contador++;
    }
}

void mostrarLivro(Livro livro)
{

    printf("Nome: %s\n", livro.nome);
    printf("Genero: %s\n", livro.genero);
    printf("Editora: %s\n", livro.editora);
    printf("Autor: %s\n", livro.autor);
    printf("Codigo: %d\n", livro.codigo);
    printf("Quantidade disponivel: %d\n", livro.quantidade);
    printf("- - - - - - - - - - - - - - - - - -\n");
}

int comparaString(const char *a, const char *b)
{
    unsigned int size1 = strlen(a);
    if (strlen(b) != size1)
        return 0;
    for (unsigned int i = 0; i < size1; i++)
        if (tolower(a[i]) != tolower(b[i]))
            return 0;
    return 1;
}

int retornaQntLivrosEmArquivo(FILE *file, size_t tamanhoDoArquivo)
{

    int quantidadeDeRegistros;
    quantidadeDeRegistros = (tamanhoDoArquivo / sizeof(Livro));
    return quantidadeDeRegistros;
}

void buscaOcorrencia(bool encontraOcorrencia, char *nome)
{
    if (encontraOcorrencia == false)
    {
        printf("O livro '%s' nao foi encontrado no sistema.\n", nome);
    }
}

void adicionarLivro()
{
    int quantidadeDeLivrosNaLista;
    int index;
    FILE *file = abreArquivo("arquivoLivros.dat", "ab");
    printf("Quantos livros deseja cadastrar?\n");
    scanf("%d", &quantidadeDeLivrosNaLista);
    Livro *arrayLivros = criaListaDeLivros(quantidadeDeLivrosNaLista);

    for (index = 0; index < quantidadeDeLivrosNaLista; index++)
    {

        printf("Digite o nome do livro:\n");
        scanf(" %[^\n]", arrayLivros[index].nome);

        printf("Digite o genero do livro:\n"); //
        scanf(" %[^\n]", arrayLivros[index].genero);

        printf("Digite o codigo do livro:\n");
        scanf("%d", &arrayLivros[index].codigo);

        printf("Digite a editora do livro:\n");
        scanf(" %[^\n]", arrayLivros[index].editora);

        printf("Digite o autor do livro:\n");
        scanf(" %[^\n]", arrayLivros[index].autor);

        printf("Digite a quantidade de exemplares a serem cadastrados:\n");
        scanf("%d", &arrayLivros[index].quantidade);

        printf("Livro '%s' salvo com sucesso\n", arrayLivros[index].nome);

        fwrite(&arrayLivros[index], sizeof(arrayLivros[index]), 1, file);
    }

    liberaListaDeLivros(&arrayLivros);
    fclose(file);
    printf("Pressione qualquer tecla para continuar!\n");
    getch();
}

void listarTodosLivros()
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    Livro livros;
    int index;
    int totalDeRegistrosDeLivros;

    size_t tamanhoDoArquivo = retornaTamanhoArquivo(file);
    totalDeRegistrosDeLivros = retornaQntLivrosEmArquivo(file, tamanhoDoArquivo);

    Livro *arrayLivros = (Livro *)malloc(tamanhoDoArquivo);
    tratamentoErroAlocarVetorDeLivros(arrayLivros);

    preencheListaDeLivrosComArquivo(&livros, file, arrayLivros);
    fclose(file);

    printf("- - - - - - - -LIVROS - - - - - - - - - -\n");
    for (index = 0; index < totalDeRegistrosDeLivros; index++)
    {

        mostrarLivro(arrayLivros[index]);
    }

    liberaListaDeLivros(&arrayLivros);
    printf("\nPressione qualquer tecla para continuar!\n");
    getch();
}

void buscarLivroPorNome()
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    Livro livro;
    int totalDeRegistrosDeLivros;
    int index;
    char ProcuraLivroNome[MAX_ATRIBUTO_LIVRO];
    bool encontraOcorrencia = false;

    size_t tamanhoDoArquivo = retornaTamanhoArquivo(file);
    totalDeRegistrosDeLivros = retornaQntLivrosEmArquivo(file, tamanhoDoArquivo);

    Livro *arrayLivros = (Livro *)malloc(tamanhoDoArquivo);
    tratamentoErroAlocarVetorDeLivros(arrayLivros);

    preencheListaDeLivrosComArquivo(&livro, file, arrayLivros);
    fclose(file);

    printf("Digite o nome do livro a ser procurado: \n");
    scanf(" %[^\n]", ProcuraLivroNome);
    for (index = 0; index < totalDeRegistrosDeLivros; index++)
    {
        if (comparaString(arrayLivros[index].nome, ProcuraLivroNome))
        {
            printf("- - - - - - - - - - - - - - - - - -\n");
            encontraOcorrencia = true;
            mostrarLivro(arrayLivros[index]);
            break;
        }
    }
    buscaOcorrencia(encontraOcorrencia, ProcuraLivroNome);
    liberaListaDeLivros(&arrayLivros);

    printf("Pressione qualquer tecla para continuar!\n");
    getch();
}

void alterarDadosLivro()
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
}

void excluirLivro()
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    FILE *fileTemporario = abreArquivo("arquivoLivrosTemporario.dat", "wb");

    Livro *arrayLivro;
    Livro livros;

    int totalDeRegistrosDeLivros;
    int index;
    char procuraLivroNome[MAX_ATRIBUTO_LIVRO];
    bool encontraOcorrencia;

    size_t tamanhoDoArquivo = retornaTamanhoArquivo(file);
    totalDeRegistrosDeLivros = retornaQntLivrosEmArquivo(file, tamanhoDoArquivo);

    arrayLivro = (Livro *)malloc(tamanhoDoArquivo);
    tratamentoErroAlocarVetorDeLivros(arrayLivro);

    preencheListaDeLivrosComArquivo(&livros, file, arrayLivro);

    printf("Digite o nome do livro a ser excluido:\n");
    scanf(" %[^\n]", procuraLivroNome);

    for (index = 0; index < totalDeRegistrosDeLivros; index++)
    {
        if (comparaString(arrayLivro[index].nome, procuraLivroNome))
        {
            encontraOcorrencia = true;
            printf("Livro: '%s' Apagado com sucesso!!!\n", procuraLivroNome);
            continue;
        }
        else
            fwrite(&arrayLivro[index], sizeof(arrayLivro[index]), 1, fileTemporario);
    }
    fclose(file);
    fclose(fileTemporario);
    liberaListaDeLivros(&arrayLivro);
    buscaOcorrencia(encontraOcorrencia, procuraLivroNome);
    renomeiaArquivoTemporario("arquivoLivros.dat", "arquivoLivrosTemporario.dat");

    printf("Pressione qualquer tecla para continuar!\n");
    getch();
}
