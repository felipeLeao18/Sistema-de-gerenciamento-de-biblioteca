# **Projeto final da disciplina: Algoritmos e estruturas de dados 1**

## Universidade federal de Goias

### Sistema de gerenciamento de biblioteca utilizando linguagem C

#### Estruturas utilizadas:
- Manipulacao de arquivos.
- Alocacao dinamica.
- Manipulacao por ponteiros.
- Ordenacao(qsort).
- Manipulacao de Datas com a biblioteca time.h.
- Uso de multiplos arquivos (headers e .c).
---------------------------------------------------------------------------------------

### Para comecar usar o sistema:
#### Para registrar um emprestimo de Livro(s) para aluno(s):
- Registrar pelo menos um livro e um aluno;
---------------------------------------------------------------------------------------

# Observacoes:

- Cada aluno pode alugar no maximo 3 livros;
- Se o aluno tiver um registro pendente, nao podera realizar outro emprestimo ate que os livros alugados previamente sejam recebidos;
- Apos emprestar um livro para um aluno, o livro automaticamente ira diminuir 1 unidade em seu estoque;
- Apos o registro de entrega de livros do aluno, o sistema ira automaticamente aumentar 1 unidade do(s) livro(s) alugados pelo aluno na quantidade disponivel dos livros;
- Apos receber emprestimo de livro no menu Sistema, seu registro de emprestimo sera automaticamente excluido do sistema;
- Ao digitar um tipo de dado errado(Por exemplo no codigo do livro escrever uma letra) feche o programa imediatamente e entao refaca a operacao;
- Nao sao permitidos cadastro de LIVROS COM NOME OU CODIGO ja previamente cadastrados. Tambem nao sao permitidos cadastros com Registros academicos de alunos iguais;
- O nome e codigo de um livro sao imutaveis, ou seja, na hora de alterar os dados do livro estes nao poderao ser modificados, caso deseje alterar tais dados, exclua do sistema e cadastre novamente;
- O registro academico de um aluno e imutavel, se desejar alterar o registro academico, apague o aluno do sistema e refacao a operacao de cadastro para tal aluno;
