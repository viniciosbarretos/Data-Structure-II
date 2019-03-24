# Data-Structure-II

- File Allocation Table Manager

Escreva um programa em C que simule o armazenamento de arquivos baseado em alocação por lista encadeada usando uma tabela na memória. O programa deve ter as seguintes características:
O tamanho de cada arquivo deve variar entre 2 e 20 blocos. Nesse caso, definimos cada bloco como um tamanho w. Esse processo pode ser indicado pelo usuário ou realizado aleatoriamente;
O disco tem 300 blocos de espaço disponíveis, rotulados de 0 a 299 w;
Devem estar disponíveis as operações:
Criar arquivo em disco. Cada arquivo criado deve ter um conteúdo associado.
Abrir arquivo, visando apresentar o conteúdo armazenado.
Excluir arquivo.
Exibir disco (mostra todos o blocos para verificar se estão ocupados ou não).
Exibir tabela.
Mostrar o espaço total disponível em disco.
Um bloco do disco não pode ser ocupado por mais de um arquivo diferente. Desejável: cada nova execução, o programa deve ler os arquivos em disco.



- SGBD

1. Escreva um programa em linguagem C que simule a leitura e gravação de dados em um banco de dados de clientes. O arquivo de dados deve conter as seguintes informações sobre clientes:
  1.1. Número da Conta
  1.2. Nome
  1.3. Tipo de pessoa (F ou J)
  1.4. Saldo
2. Crie um arquivo índice com Profundidade Global 2 considerando o atributo Número da Conta. Utilize a técnica de hashing extensível. A profundidade local deve ser 3. O programa deve oferecer a possibilidade de cadastrar novos clientes, assim como excluir possíveis clientes. Após a realização dessas operações (cadastro e exclusão) os arquivos de dados e de índice devem ser atualizados. O programa deve indicar “overflow” se a profundidade local foi atingida, conforme limite indicado (4).

3. O programa deve conter (no mínimo) as seguintes opções:
  3.1. Cadastrar Cliente, Remover Cliente, Consultar Cliente pelo Número da Conta;
  3.2. Visualizar o estado da Tabela Hash, indicando o total de diretórios, os níveis de profundidades globlal e local, bem como as identificações dos buckets e linhas do em que os dados foram armazenados em disco. Cada chave do bucket tem um RID para o arquivo em disco.
  3.3. Salvar as alterações em um arquivo em disco. Este arquivo deve ser lido na próxima execução.

4. A remoção deve ocorrer conforme critérios explicitados em aula, com apoio de duas variáveis. Uma remoção pode ocorrer se atende duas propriedades: variável “dirty bit” indica que a página está sob alteração; e, “pin count” indica que não há usuários acessando a página. Após remoção, o arquivo deve ser atualizado, bem como as profundidades locais e global.

- SGBD B+ Tree
Escreva um programa em linguagem C que utilize uma árvore B+ como estrutura de armazenamento para um banco de dados (uma tabela aluno):
● -ID. Tipo inteiro.
● -Nome completo. Char, 20;
● -E-mail: Char 40;
● -Idade. Tipo inteiro;
● -Status. Valores possíveis, <A>tivo ou <F>inalizado.
● Utilize o atributo ID como índice, visando o preenchimento das páginas. Devem estar disponíveis
as operações: cadastrar, remover, exibir lista de alunos e uma opção nomeada resumo para mostrar o total de páginas da árvore, com o total em KB que está armazenado. O sistema deve utilizar uma árvore B+ de ordem 5. Cada elemento armazenado na folha deve (também) ter um apontamento para o registro armazenado um arquivo. Todos os registros estão em um único arquivo do tipo txt, abstraindo o modelo de índice denso. A abstração é que cada página representa um bloco de dados em disco, limitado por um tamanho em KB (soma dos bytes de um registro vezes o número de elementos de uma página).
  

