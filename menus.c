//
// Created by felipe on 5/2/2021.
//
//

#include "menus.h"
int escolha;

void menuInicial()
{
    while (1)
    {
        system("cls");
        printf("\n\n----------------BIBLIOTECA UFG----------------\n");
        printf("1- Menu Do Sistema\n");
        printf("2- Menu de Alunos\n");
        printf("3- Menu de livros\n");
        printf("4- Sair\n");
        printf("----------------------------------------------\n");
        printf("Digite sua opcao:\n");
        scanf("%d", &escolha);
        if (escolha == 4){
            printf("FIM DO PROGRAMA!!!\n");
            break;
        }
        switch (escolha)
        {
        case 1:
            menuSistema();
            break;
        case 2:
            menuAlunos();
            break;
        case 3:
            menuLivros();
            break;
            
        default:
            printf("Digite uma opcao valida!!!\n");
            menuInicial();
        }
    }
}

void menuSistema()
{

    printf("\n\n----------------BIBLIOTECA UFG----------------\n");
    printf("1- Emprestar livro\n");
    printf("2- Verificar disponibilidade\n");
    printf("3- Receber livro\n");
    printf("4- Anunciar Perda\n");
    printf("5- Abrir instrucoes do sistema\n");
    printf("6- Voltar para o menu inicial\n");
    printf("----------------------------------------------\n");
    printf("Digite sua opcao:\n");
    scanf("%d", &escolha);
    switch (escolha)
    {

    case 1:
        //emprestarLivro();
        //break;
    case 2:
        //verificarDisponibilidade();
        //break;
    case 3:
        //Receber livro();
        //break;
    case 4:
        //Anunciar Perda();
        // break;

    case 5:
        //abrirInstrucoes();
        //break;
    case 6:
        menuInicial();
        break;
    default:
        printf("Digite uma opcao valida\n");
        menuLivros();
    }
}

void menuAlunos()
{
    printf("\n\n----------------BIBLIOTECA UFG----------------\n");
    printf("1- Inserir alunos\n");
    printf("2- Listar alunos\n");
    printf("3- Procurar Aluno\n");
    printf("4- Excluir aluno\n");
    printf("5- Voltar para o menu inicial\n");
    printf("----------------------------------------------\n");
    printf("Digite sua opcao:\n");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 1:
        adicionarAluno();
        break;
    case 2:
        listarTodosAlunos();
        break;
    case 3:
        buscaAlunoRegistroAcademico();
        break;
    case 4:
        excluirAluno();
        break;
    case 5:
        //buscarAluno();
        //break;
    case 6:
        menuInicial();
        break;
    default:
        printf("Digite uma opcao valida\n");
        menuAlunos();
    }
}

void menuLivros()
{
    printf("\n\n----------------BIBLIOTECA UFG----------------\n");
    printf("1- Inserir livro\n");
    printf("2- Alterar livro\n");
    printf("3- Consultar livro\n");
    printf("4- Excluir livro do sistema\n");
    printf("5- Listar todos os livros\n");
    printf("6- Voltar para o menu inicial\n");
    printf("----------------------------------------------\n");
    printf("Digite sua opcao:\n");
    scanf("%d", &escolha);

    switch (escolha)
    {

    case 1:
        adicionarLivro();
        break;
    case 2:
        //alterarLivro();
        //break;
    case 3:
        buscarLivroPorNome();
        break;
    case 4:
        excluirLivro();
        break;
    case 5:
        listarTodosLivros();
        break;
    case 6:
        menuInicial();
        break;
    default:
        printf("Digite uma opcao valida\n");
        menuLivros();
    }
}
