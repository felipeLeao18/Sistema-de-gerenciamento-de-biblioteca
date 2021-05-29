#include "menus.h"
#include "sistema.h"
int escolha;
char nomeLivro[MAX_ATRIBUTO_LIVRO];

void menuInicial()
{
    while (1)
    {
        system("cls");
        printf("\n----------------------BIBLIOTECA UFG-------------------------\n");
        printf("#                 1- Menu do sistema                        #\n");
        printf("#                 2- Menu de alunos                         #\n");
        printf("#                 3- Menu de livros                         #\n");
        printf("#                 4- SAIR                                   #\n");
        printf("--------------------------------------------------------------\n");
        printf("Digite sua opcao:\n");
        scanf("%d", &escolha);
        if (escolha == 4)
        {
            printf("FIM DO PROGRAMA!!!\n");
            exit(1);
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
   
    system("cls");
    printf("\n----------------------BIBLIOTECA UFG-------------------------\n");
    printf("#                 1- Emprestar livro                         #\n");
    printf("#                 2- Listar Todos emprestimos                #\n");
    printf("#                 3- Receber emprestimo de aluguel de Aluno  #\n");
    printf("#                 4- Buscar registro de emprestimo           #\n");
    printf("#                 5- Abrir menu de instrucoes                #\n");
    printf("#                 6- Voltar para o menu inicial              #\n");
    printf("---------------------------------------------------------------\n");
    printf("Digite sua opcao:\n");
    scanf("%d", &escolha);
    switch (escolha)
    {

    case 1:
        criaCliente();
        break;
    case 2:
        listarTodosClientes();
        break;
    case 3:

        receberLivro();
        break;
    case 4:
        
       buscaCliente();
        break;

    case 5:
        abrirInstrucoes();
        break;
    case 6:
        menuInicial();
        break;

    default:
        printf("Digite uma opcao valida\n");
        menuInicial();
    }
}

void menuAlunos()
{
    system("cls");
    printf("\n---------------------BIBLIOTECA UFG--------------------------\n");
    printf("#                 1- Inserir alunos                         #\n");
    printf("#                 2- Listar alunos                          #\n");
    printf("#                 3- Procurar Aluno                         #\n");
    printf("#                 4- Excluir aluno                          #\n");
    printf("#                 5- Alterar dados de aluno                 #\n");
    printf("#                 6- Voltar para o menu inicial             #\n");
    printf("--------------------------------------------------------------\n");
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
        alteraDadosAluno();
        break;
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
    system("cls");
    printf("\n--------------------BIBLIOTECA UFG--------------------------\n");
    printf("#                  1- Inserir livro                        #\n");
    printf("#                  2- Alterar livro                        #\n");
    printf("#                  3- Consultar livro                      #\n");
    printf("#                  4- Excluir livro do sistema             #\n");
    printf("#                  5- Listar todos os livros               #\n");
    printf("#                  6- Anunciar perda                       #\n");
    printf("#                  7- Voltar para o menu inicial           #\n");
    printf("--------------------------------------------------------------\n");
    printf("Digite sua opcao:\n");
    scanf("%d", &escolha);

    switch (escolha)
    {

    case 1:
        adicionarLivro();
        break;
    case 2:
        alteraDadosLivro();
        break;
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
        anunciarPerdaLivro();
        break;
    case 7:
        menuInicial();
        break;
    default:
        printf("Digite uma opcao valida\n");
        menuLivros();
    }
}