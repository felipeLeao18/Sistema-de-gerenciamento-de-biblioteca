#include "alunos.h"

Aluno *alocaMemoriaParaListaDeAlunos(int quantidadeDeAlunos);
void tratamentoDeErroAlocacaoAlunos(Aluno *aluno);
void mostraAlunos(Aluno *aluno);
void procuraOcorrencia(bool encontraOcorrencia, int registroAcademico);
int retornaQntAlunosEmArquivo(FILE *file, size_t tamanhoDoArquivo);
void procuraOcorrencia(bool encontraOcorrencia, int registroAcademico);
void mostraAluno(Aluno *aluno);
void liberaListaDeAlunos(Aluno **aluno);
void inputAluno(Aluno *aluno);

Aluno *alocaMemoriaParaListaDeAlunos(int quantidadeDeAlunos)
{
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno) * quantidadeDeAlunos);
    if (!aluno)
    {
        printf("Houve um erro ao alocar memoria para %d aluno(s)");
        return NULL;
    }
    return aluno;
}
void tratamentoDeErroAlocacaoAlunos(Aluno *aluno)
{
    if (!aluno)
    {
        printf("Ocorreu um erro de memoria ao alocar memoria ALUNO - memory Error\n");
    }
}
void liberaListaDeAlunos(Aluno **aluno)
{
    free(&aluno);
}

void inputAluno(Aluno *aluno)
{
    printf("Digite o nome do aluno\n");
    scanf(" %[^\n]", &aluno->nomeCompleto);

    printf("Digite o registro academico do aluno\n");
    scanf("%d", &aluno->registroAcademico);

    printf("Digite o numero de celular do aluno:\n");
    scanf("%ld", &aluno->numeroCelular);
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

int retornaQntAlunosEmArquivo(FILE *file, size_t tamanhoDoArquivo)
{

    int quantidadeDeRegistros;
    quantidadeDeRegistros = (tamanhoDoArquivo / sizeof(Aluno));
    return quantidadeDeRegistros;
}

void procuraOcorrencia(bool encontraOcorrencia, int registroAcademico)
{
    if (encontraOcorrencia == false)
    {
        printf("O registro academico %d nao foi encontrado sistema.\n", registroAcademico);
    }
}

void mostraAluno(Aluno *aluno)
{
    printf("NOME: %s\n", aluno->nomeCompleto);
    printf("RA: %d\n", aluno->registroAcademico);
    printf("CELULAR: %d\n", aluno->numeroCelular);
    printf("- - - - - - - - - - - - - - - - - -\n");
}

void adicionarAluno()
{

    FILE *file = abreArquivo("ArquivoAlunos.dat", "ab");
    int quantidadeDeAlunosParaCadastro;
    int index;

    printf("Digite a quantidade de alunos a serem cadastrados:\n");
    scanf("%d", &quantidadeDeAlunosParaCadastro);

    Aluno *arrayAlunos = alocaMemoriaParaListaDeAlunos(quantidadeDeAlunosParaCadastro);
    for (index = 0; index < quantidadeDeAlunosParaCadastro; index++)
    {

        inputAluno(&arrayAlunos[index]);
        fwrite(&arrayAlunos[index], sizeof(arrayAlunos[index]), 1, file);
        printf("\nAluno '%s' cadastrado com sucesso!!!\n", arrayAlunos[index].nomeCompleto);
    }
    fclose(file);
    liberaListaDeAlunos(&arrayAlunos);

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
    FILE *file = abreArquivo("arquivoAlunos.dat", "rb");
    size_t tamanhoDoArquivo = retornaTamanhoArquivo(file);
    Aluno aluno;
    int pesquisaRegistroAcademico;
    int index;
    bool encontraOcorrencia = false;

    int registrosDeAlunos = retornaQntAlunosEmArquivo(file, tamanhoDoArquivo);
    Aluno *arrayAlunos = (Aluno *)malloc(tamanhoDoArquivo);
    tratamentoDeErroAlocacaoAlunos(arrayAlunos);

    preencheListaDeAlunosComArquivo(&aluno, file, arrayAlunos);
    fclose(file);

    printf("Digite o Registro academico do aluno:\n");
    scanf("%d", &pesquisaRegistroAcademico);

    for (index = 0; index < registrosDeAlunos; index++)
    {
        if (arrayAlunos[index].registroAcademico == pesquisaRegistroAcademico)
        {
            printf("- - - - - - - - - - - - - - - - - -\n");
            encontraOcorrencia = true;
            mostraAluno(&arrayAlunos[index]);
        }

        liberaListaDeAlunos(&arrayAlunos);
    }
    procuraOcorrencia(encontraOcorrencia, pesquisaRegistroAcademico);

    printf("Pressione qualquer tecla para continuar!\n");
    getch();
}

void alteraDadosAluno()
{
    FILE *file = abreArquivo("arquivoAlunos.dat", "rb+");
    Aluno aluno;
    bool achei = false;

    int buscaRegistroAcademico;
    printf("Digite o Registro academico do aluno que voce deseja atualizar os dados:\n");
    scanf("%d", &buscaRegistroAcademico);

    while (fread(&aluno, sizeof(Aluno), 1, file) > 0)
    {
        if (aluno.registroAcademico == buscaRegistroAcademico)
        {
            printf("Registro encontrado, aluno: %s, RA: %d; Digite os novos valores para os dados do aluno\n", aluno.nomeCompleto, aluno.numeroCelular);
            achei = true;
            inputAluno(&aluno);

            fseek(file, -sizeof(Aluno), SEEK_CUR);
            fwrite(&aluno, sizeof(Aluno), 1, file);
            fclose(file);

            printf("Registro alterado com sucesso!\n");
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
    int pesquisaRegistroAcademico;
    int index;
    bool encontraOcorrencia = false;

    int registrosDeAlunos = retornaQntAlunosEmArquivo(file, tamanhoDoArquivo);
    Aluno *arrayAlunos = (Aluno *)malloc(tamanhoDoArquivo);
    tratamentoDeErroAlocacaoAlunos(arrayAlunos);

    preencheListaDeAlunosComArquivo(&aluno, file, arrayAlunos);
    fclose(file);

    printf("Digite o Registro academico do aluno\n");
    scanf("%d", &pesquisaRegistroAcademico);

    for (index = 0; index < registrosDeAlunos; index++)
    {
        if (arrayAlunos[index].registroAcademico == pesquisaRegistroAcademico)
        {
            encontraOcorrencia = true;
            printf("Aluno: %s, RA: %d; Apagado do sistema.\n", arrayAlunos[index].nomeCompleto, arrayAlunos[index].registroAcademico);
            continue;
        }
        fwrite(&arrayAlunos[index], sizeof(arrayAlunos[index]), 1, fileTemporario);
    }
    procuraOcorrencia(encontraOcorrencia, pesquisaRegistroAcademico);

    fclose(file);
    fclose(fileTemporario);
    liberaListaDeAlunos(&arrayAlunos);
    renomeiaArquivoTemporario("arquivoAlunos.dat", "arquivoAlunosTemporario.dat");

    printf("\n\nPressione qualquer tecla para continuar!\n");
    getch();
}
