#include "alunos.h"

void tratamentoDeErroAlocacaoAlunos(Aluno *aluno);
void mostraAlunos(Aluno *aluno);
int retornaQntAlunosEmArquivo(FILE *file, size_t tamanhoDoArquivo);
void procuraOcorrencia(bool encontraOcorrencia, char *registroAcademico);
void mostraAluno(Aluno *aluno);
void liberaListaDeAlunos(Aluno **aluno);
bool inputAluno(Aluno *aluno);
int alunoExiste(char *registroAcademico);
int comparaNomeAluno(const char *a, const char *b);

int comparaNomeAluno(const char *original, const char *buscada)
{
    unsigned int tamanhoStrOriginal = strlen(original);
    if (strlen(buscada) != tamanhoStrOriginal)
        return 0;
    for (unsigned int i = 0; i < tamanhoStrOriginal; i++)
        if (tolower(original[i]) != tolower(buscada[i]))
            return 0;
    return 1;
}

void tratamentoDeErroAlocacaoAlunos(Aluno *aluno)
{
    if (!aluno)
    {
        printf("Ocorreu um erro de memoria ao alocar memoria ALUNO - memory Error\n");
        exit(1);
    }
}
void liberaListaDeAlunos(Aluno **aluno)
{
    free(&aluno);
}

int retornaQntAlunosEmArquivo(FILE *file, size_t tamanhoDoArquivo)
{

    int quantidadeDeRegistros;
    quantidadeDeRegistros = (tamanhoDoArquivo / sizeof(Aluno));
    return quantidadeDeRegistros;
}

void preencheListaDeAlunosComArquivo(Aluno *aluno, FILE *file, Aluno *arrayAlunos)
{
    int contador = 0;
    fseek(file, 0L, SEEK_SET);
    while (fread(aluno, sizeof(Aluno), 1, file) > 0)
    {
        arrayAlunos[contador] = *aluno;

        contador++;
    }
}

void procuraOcorrencia(bool encontraOcorrencia, char *registroAcademico)
{
    if (encontraOcorrencia == false)
    {
        printf("O registro academico %d nao foi encontrado sistema.\n", registroAcademico);
    }
}

void mostraAluno(Aluno *aluno)
{
    printf("NOME: %s\n", aluno->nomeCompleto);
    printf("RA: %s\n", aluno->registroAcademico);
    printf("CELULAR: %d\n", aluno->numeroCelular);
    printf("- - - - - - - - - - - - - - - - - -\n");
}

int alunoExiste(char *registroAcademico)
{
    bool acheiAluno = false;
    FILE *file = fopen("arquivoAlunos.dat", "rb");
    Aluno aluno;
    while (fread(&aluno, sizeof(Aluno), 1, file) > 0)
    {
        if (comparaNomeAluno(aluno.registroAcademico, registroAcademico))
        {
            acheiAluno = true;
            printf("O registro academico %s ja esta cadastrado no sistema, ", registroAcademico);
            fclose(file);
            return 1;
        }
    }
    if (acheiAluno == false)
        fclose(file);

    return 0;
}

bool inputAluno(Aluno *aluno)
{

    printf("Digite o nome do aluno\n");
    scanf(" %[^\n]", &aluno->nomeCompleto);

    printf("Digite o registro academico do aluno\n");
    scanf(" %[^\n]", &aluno->registroAcademico);
    if (alunoExiste(aluno->registroAcademico) == 1)
    {
        return false;
    }

    printf("Digite o numero de celular do aluno:\n");
    scanf("%ld", &aluno->numeroCelular);
    return true;
}

void adicionarAluno()
{

    Aluno aluno;

    if (inputAluno(&aluno))
    {

        FILE *file = abreArquivo("ArquivoAlunos.dat", "ab");
        fwrite(&aluno, sizeof(aluno), 1, file);
        printf("\nAluno '%s' cadastrado com sucesso!!!\n", aluno.nomeCompleto);

        fclose(file);
    }
    else
    {
        printf("confira os dados e tente cadastrar o aluno novamente!\n");
    }

    printf("\nPressione qualquer tecla para continuar!\n");
    getch();
}

void listarTodosAlunos()
{
    FILE *file = abreArquivo("arquivoAlunos.dat", "rb");
    size_t tamanhoDoArquivo = retornaTamanhoArquivo(file);
    Aluno aluno;

    int registrosDeAlunos = retornaQntAlunosEmArquivo(file, tamanhoDoArquivo);
    Aluno *arrayAlunos = (Aluno *)malloc(tamanhoDoArquivo);
    tratamentoDeErroAlocacaoAlunos(arrayAlunos);

    preencheListaDeAlunosComArquivo(&aluno, file, arrayAlunos);
    fclose(file);

    int index;
    printf("- - - - - - - -ALUNOS - - - - - - - - - -\n");
    for (index = 0; index < registrosDeAlunos; index++)
    {
        mostraAluno(&arrayAlunos[index]);
    }

    liberaListaDeAlunos(&arrayAlunos);

    printf("\nPressione qualquer tecla para continuar!\n");
    getch();
}

void buscaAlunoRegistroAcademico()
{
    FILE *file = abreArquivo("arquivoAlunos.dat", "rb+");
    Aluno aluno;
    bool achei = false;

    char buscaRegistroAcademico[19];
    printf("Digite o Registro academico do aluno a ser buscado:\n");
    scanf(" %[^\n]", &buscaRegistroAcademico);

    while (fread(&aluno, sizeof(Aluno), 1, file) > 0)
    {
        if (comparaNomeAluno(aluno.registroAcademico, buscaRegistroAcademico))
        {

            achei = true;

            printf("\n- - - - - - - - - - - - - - - - - -\n");
            fseek(file, -sizeof(Aluno), SEEK_CUR);
            mostraAluno(&aluno);

            fclose(file);
        }
    }
    procuraOcorrencia(achei, buscaRegistroAcademico);
    printf("\nPressione qualquer tecla para continuar:\n");
    getch();
}

void alteraDadosAluno()
{
    FILE *file = abreArquivo("arquivoAlunos.dat", "rb+");
    Aluno aluno;
    bool achei = false;

    char buscaRegistroAcademico[19];
    printf("Digite o Registro academico do aluno que voce deseja atualizar os dados:\n");
    scanf(" %[^\n]", &buscaRegistroAcademico);

    while (fread(&aluno, sizeof(Aluno), 1, file) > 0)
    {
        if (comparaNomeAluno(aluno.registroAcademico, buscaRegistroAcademico))
        {
            printf("Registro encontrado, aluno: %s, RA: %d; Digite os novos valores para os dados do aluno\n", aluno.nomeCompleto, aluno.numeroCelular);
            achei = true;

            if (inputAluno(&aluno))
            {

                fseek(file, -sizeof(Aluno), SEEK_CUR);
                fwrite(&aluno, sizeof(Aluno), 1, file);
                fclose(file);

                printf("Registro alterado com sucesso!\n");
            }
        }
    }
    procuraOcorrencia(achei, buscaRegistroAcademico);
    printf("\nPressione qualquer tecla para continuar:\n");
    getch();
}

void excluirAluno()
{
    listarTodosAlunos();
    printf("\n\n");
    FILE *file = abreArquivo("arquivoAlunos.dat", "rb");
    FILE *fileTemporario = abreArquivo("arquivoAlunosTemporario.dat", "wb");
    size_t tamanhoDoArquivo = retornaTamanhoArquivo(file);

    Aluno aluno;
    char buscaRegistroAcademico[19];
    int index;
    bool encontraOcorrencia = false;

    int registrosDeAlunos = retornaQntAlunosEmArquivo(file, tamanhoDoArquivo);
    Aluno *arrayAlunos = (Aluno *)malloc(tamanhoDoArquivo);
    tratamentoDeErroAlocacaoAlunos(arrayAlunos);

    preencheListaDeAlunosComArquivo(&aluno, file, arrayAlunos);
    fclose(file);

    printf("Digite o Registro academico do aluno\n");
    scanf(" %[^\n]", &buscaRegistroAcademico);

    for (index = 0; index < registrosDeAlunos; index++)
    {
        if (comparaNomeAluno(aluno.registroAcademico, buscaRegistroAcademico))
        {
            encontraOcorrencia = true;
            printf("Aluno: %s, RA: %d; Apagado do sistema.\n", arrayAlunos[index].nomeCompleto, arrayAlunos[index].registroAcademico);
            continue;
        }
        fwrite(&arrayAlunos[index], sizeof(arrayAlunos[index]), 1, fileTemporario);
    }
    procuraOcorrencia(encontraOcorrencia, buscaRegistroAcademico);

    fclose(file);
    fclose(fileTemporario);
    liberaListaDeAlunos(&arrayAlunos);
    renomeiaArquivoTemporario("arquivoAlunos.dat", "arquivoAlunosTemporario.dat");

    printf("\n\nPressione qualquer tecla para continuar!\n");
    getch();
}
