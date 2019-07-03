#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include <math.h>
#define MAX 1000
#define LIMDECIMAIS 1000

/*
*   >> Fun��o que recebe uma variavel int e um vetor de caracteres.
* e devolve o nome do arquivo informado pelo usuario e a quantidade
* de linhas desse arquivo.
*
*   >> RESTRI��O(�ES):
*
* -- char nomeDoArquivo[] = N�o pode ser um vetor pequeno, pois precisa
* ter capacidade de receber o nome do arquivo.
*/
bool LerArquivo(int * quantidadeDeLinhas, char nomeDoArquivo[]);

/*
*   >> Fun��o que l� os arquivos do arquivo e armazena em vetores.
*
* -- double dados[] = A fun��o atualizara o vetor com os dados da coluna
* esquerda do arquivo.
*
* -- char nomeDoArquivo[] = vetor com o nome do arquivo.
*
* -- double dadosy[] = A fun��o atualizara o vetor com os dados da coluna
* direita do arquivo.
*
*   >> RESTRI��O(��ES):
*
* -- A string NomeDoArquivo precisam estar com as
* suas informa��es (Isso � feito pela fun��o "LerArquivo").
*
*   >> RETORNO:
* -- Retorna a quantidade de dados se a fun��o conseguir ler o arquivo
* j� criado e alimentado com os dados.
*/
int LerDadosDoArquivo(double dados[], char nomeDoArquivo[], double dadosy[]);

/*
*   >> Fun��o que cria a tabela de frequencia dos dados no vetor double dados[].
*
* -- int totalDeDados = Total de dados no vetor double dados[].
*
* -- double dados[] = Vetor com os dados para cria��o da tabela.
*
* -- double tabela[][7] = Matriz que recebe as informa��es da tabela. As 7
* colunas s�o constantes. Segue o que cada coluna ir� receber:
* 1�: Faixa inicial.
* 2�: Faixa final.
* 3�: Ponto m�dio.
* 4�: Frequ�ncia.
* 5�: Frequ�ncia acumulada.
* 6�: Frequ�ncia relativa.
* 7�: Frequ�ncia relativa acumulada.
*
* -- int * totalDeFaixas = A fun��o atualiza essa variavel com o total de
* faixas criadas.
*
*   >> RESTRI��O(��ES):
*
* -- As variaveis totalDeDados e dados[] j� precisam estar com as suas
* informa��es. Isso � feito pela fun��o "LerDadosDoArquivo".
*/
int CriarTabelaDeFrequencia(int totalDeDados, double dados[], double tabelaDados[][7], int * totalDeFaixas);

/*
*   >> Fun��o que estima a moda, media e Desvio padr�o, utilizando os dados do vetor dados[] e da tabelaDados[][7].
*
* -- int totalDeDados = Total de dados no vetor double dados[].
*
* -- double dados[] = double dados[] = Vetor com os dados.
*
* -- float *media = Variavel que recebe a m�dia dos do vetor dados[].
*
* -- int totalDeFaixas = Total de faixas da tabelaDados[][7].
*
*   >> RESTRI��O(��ES):
*
* -- As variaveis totalDeDados e dados[] j� precisam estar com as suas
* informa��es. Isso � feito pela fun��o "LerDadosDoArquivo". Assim como
* as variaveis totalDeFaixas e tabelaDados[][7] tamb�m precisam (fun��o
* "CriarTabelaDeFrequencia".
*/
int EstimarModaMediaDesvioPadrao(int totalDeDados, double dados[], float * media, int totalDeFaixas, double tabelaDados[][7]);

/*
*   >> Fun��o que recebe um vetor de double a[] e a quantidade total de
* dados desse vetor. O vedor a[] ser� ordenado em ordem crescente. Essa
* fun��o foi retirada da apostila "Ordena��o" do professor Ciro Cirne (Unisantos).
*/
void InsercaoDireta(double a[], int n);

/*
*   >> Fun��o que elabora os valores do Boxplot e indica os outliers (se houver).
*
* -- int totalDeDados = Total de dados no vetor double dados[].
*
* -- double dados[] = double dados[] = Vetor com os dados.
*
*   >> RESTRI��O(��ES):
*
*  -- As variaveis totalDeDados e dados[] j� precisam estar com as suas
* informa��es. Isso � feito pela fun��o "LerDadosDoArquivo".
*/
int Boxplot(int totalDeDados, double dados[]);

/*
*   >> Fun��o que calcula a correa��o de Pearson e a regress�o linear.
*
* -- int totalDeDados = Total de dados no vetor double dados[].
*
* -- double dados[] = Vetor com os dados da coluna esquerda do arquivo.
*
* -- double dadosy[] = Vetor com os dados da coluna direita do arquivo.
*
* -- double media = Variavel que possui a media dos valores do vetor dados[].
*
* -- double mediaY = Variavel que possui a media dos valores do vetor dadosy[].
*
*   >> RESTRI��O(�ES):
*
* -- Os valores dos vetores dados[], dadosy[] e a variavel totalDeDados s�o
* atribuidos na fun��o "LerDadosDoArquivo". J� as variaveis media e mediaY s�o
* atribuidos na fun��o "EstimarModaMediaDesvioPadrao".
*/
int CorrelacaoPearsonERetaMinQuadrados(int totalDeDados, double dados[], double dadosy[], double media, double mediaY);

#endif // _HEADER_H
