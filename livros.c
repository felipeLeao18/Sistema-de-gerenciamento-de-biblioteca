#include "livros.h"

void lancaExcecaoEmCriacaoDeLista(int quantidade);
int tratamentoErroAlocarVetorDeLivros(Livro *livro);
bool naoExisteLivro(Livro *livro);
Livro *alocaMemoriaParaListaDeLivros(int quantidadeDeLivros);
Livro *criaListaDeLivros(int);
void liberaListaDeLivros(Livro **l);
void mostrarLivro(Livro livro);
void preencheListaDeLivrosComArquivo(Livro *livro, FILE *file, Livro *arrayLivros);
int comparaNomeLivro(const char *a, const char *b);
void buscaOcorrencia(bool encontraOcorrencia, char *nome);
int retornaQntLivrosEmArquivo(FILE *file, size_t tamanhoDoArquivo);
bool inputLivro(Livro *livro);
int existeNomeLivro(char *nomeDoLivro);
int existeCodigoLivro(int codigoDoLivro);

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

int comparaNomeLivro(const char *original, const char *buscada)
{
    unsigned int tamanhoStrOriginal = strlen(original);
    if (strlen(buscada) != tamanhoStrOriginal)
        return 0;
    for (unsigned int i = 0; i < tamanhoStrOriginal; i++)
        if (tolower(original[i]) != tolower(buscada[i]))
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

int existeNomeLivro(char *nomeDoLivro)
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    Livro livro;
    bool achei = false;
    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaNomeLivro(livro.nome, nomeDoLivro))
        {
            achei = true;
            printf("O livro '%s' consta como cadastrado no Sistema, confira os dados e tente novamente!\n", nomeDoLivro);

            fclose(file);
            return 1;
        }
    }
    if (achei == false)
        fclose(file);

    return 0;
}
int verificaQuantidadeLivros(int quantidade){
    if (quantidade <=0){
        return 1;
    }
    return 0;
}

int existeCodigoLivro(int codigoDoLivro)
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb");
    Livro livro;
    bool achei = false;
    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (livro.codigo == codigoDoLivro)
        {
            achei = true;
            printf("O livro '%s' consta como cadastrado no Sistema com o codigo: %d, confira os dados e tente novamente!\n", livro.nome, livro.codigo);

            fclose(file);
            return 1;
        }
    }
    if (achei == false)
        fclose(file);

    return 0;
}

bool inputLivro(Livro *livro)
{

    printf("Digite o nome do livro:\n");
    scanf(" %[^\n]", &livro->nome);
    if (existeNomeLivro(livro->nome) == 1)
    {
        return false;
    }
    printf("Digite o genero do livro:\n"); //
    scanf(" %[^\n]", &livro->genero);

    printf("Digite o codigo do livro:\n");
    scanf("%d", &livro->codigo);
    if (existeCodigoLivro(livro->codigo) == 1)
    {
        return false;
    }
    printf("Digite a editora do livro:\n");
    scanf(" %[^\n]", &livro->editora);

    printf("Digite o autor do livro:\n");
    scanf(" %[^\n]", &livro->autor);

    printf("Digite a quantidade de exemplares a serem cadastrados:\n");
    scanf("%d", &livro->quantidade);
    verificaQuantidadeLivros(livro->quantidade);
    return true;
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

        if (inputLivro(&arrayLivros[index]))
        {

            printf("Livro '%s' salvo com sucesso\n", arrayLivros[index].nome);

            fwrite(&arrayLivros[index], sizeof(arrayLivros[index]), 1, file);
        }
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
    FILE *file = abreArquivo("arquivoLivros.dat", "rb+");
    Livro livro;
    bool achei = false;

    char nomeLivro[MAX_ATRIBUTO_LIVRO];
    printf("Digite o nome do livro:\n");
    scanf(" %[^\n]", nomeLivro);

    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaNomeLivro(livro.nome, nomeLivro))
        {
            achei = true;
            printf("- - - - - - - - - - - - - - - - - -\n");
            fseek(file, -sizeof(Livro), SEEK_CUR);

            mostrarLivro(livro);
            fclose(file);
        }
    }

    buscaOcorrencia(achei, nomeLivro);
    printf("Pressione qualquer tecla para sair!\n");
    getch();
}

void alteraDadosLivro()
{
    FILE *file = abreArquivo("arquivoLivros.dat", "rb+");
    Livro livro;
    bool achei = false;

    char nomeLivroAlterado[MAX_ATRIBUTO_LIVRO];
    printf("Digite o nome do livro a ser alterado:\n");
    scanf(" %[^\n]", nomeLivroAlterado);

    while (fread(&livro, sizeof(Livro), 1, file) > 0)
    {
        if (comparaNomeLivro(livro.nome, nomeLivroAlterado))
        {
            achei = true;
            printf("Registro encontrado! Digite os novos dados do livro: '%s' abaixo:\n\n", livro.nome);

            if (inputLivro(&livro))
            {

                fseek(file, -sizeof(Livro), SEEK_CUR);
                fwrite(&livro, sizeof(Livro), 1, file);
                fclose(file);

                printf("Registro alterado com sucesso!\n");
            }
        }
    }

    buscaOcorrencia(achei, nomeLivroAlterado);
    printf("Pressione qualquer tecla para sair!\n");
    getch();
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
        if (comparaNomeLivro(arrayLivro[index].nome, procuraLivroNome))
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