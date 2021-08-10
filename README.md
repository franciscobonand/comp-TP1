# Compiladores - TP2

Pedro Tavares de Carvalho
Francisco Bonome Andrade

## Introdução

Para este trabalho foi proposta a contrução de um ligador para uma máquina virtual, o qual deve receber como entrada instruções geradas pelo montador (adaptado) desenvolvido no Trabalho Prático 1.  

Em casos nos quais programa principal está implementado em um arquivo e suas funções auxiliares em outro, cada um dos arquivos deve ser passado individualmente para o montador, e esse por sua vez irá gerar uma saída para cada um dos arquivos. O ligador, por sua vez, recebe todas as informações geradas pelo montador de uma vez e liga-as de forma a gerar o arquivo `.mv` a ser executado pela máquina virtual.

## Desenvolvimento

O montador teve seu comportamento levemente alterado quando comparado àquele implementado no Trabalho Prático 1. Ao invés de gerar o arquivo "pronto" para a máquina virtual, ele gera uma tabela de símbolos para todos os labels definidos no programa de input, seguida da representação do código em si a ser executado (contendo os métodos pré-definidos, valores de registradores e os labels ainda não substituidos por seus respectivos valores).
Além disso, a palavra-chave "WORD" passou a ser tratada como uma instrução, representada pelo número 21, de forma que o tratamento desta palavra-chave e referência para o espaço de memória apontado por ela seja feito de maneira trivial pelo ligador.

O ligador, por sua vez, itera por todos os argumentos dados como entrada para o programa, que são os arquivos gerados pelo montador a serem ligados. Para cada um dos arquivos, itera-se pela primeira linha, na qual encontra-se a tabela de símbolos referente ao código daquele arquivo, e esses dados são armazenados em um mapa de label para valor. Em seguida, itera-se pela segunda linha, a qual representa o programa/função em si, e as instruções (seguidas por seus valores) são armazenadas em um vetor.
Como o processo descrito acima é feito para cada um dos arquivos, ao final têm-se um mapa com todas as relações label-valor do programa final, formado pela junção dos programas de cada um dos arquivos, assim como um vetor que possui toda a ordem de execução do programa final.

Por fim, itera-se pelo vetor citado acima e substitui-se os labels nele presentes por seus respectivos valores (os quais estão registrados no mapa), gerando assim o programa final que será executado na máquina virtual. Nessa etapa, para que as consultas a espaços fixos de memória (representados pela letra "M" em algumas instruções) funcionem devidamente, a referência para cada espaço de memória específico é calculado dinâmicamente, variando conforme o espaço de memória no qual a instrução atual que tem um atributo "M" se encontra.

## Conclusão

Após o término da implementação foram criados alguns programas em Assembly a fim de testar os programas gerados pelo montador e ligador. Esses programas de teste foram baseados nos previamente implementados no Trabalho Prático 1. Utilizou-se novamente o emulador fornecido, o qual recebe as instruções geradas pelo montador e ligadas pelo ligador, e simula a execução da máquina virtual com base nas instruções para verificar que os programas gerados foram devidamente compilados pelo montador e ligador.
