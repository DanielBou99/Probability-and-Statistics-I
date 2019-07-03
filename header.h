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
*   >> Função que recebe uma variavel int e um vetor de caracteres.
* e devolve o nome do arquivo informado pelo usuario e a quantidade
* de linhas desse arquivo.
*
*   >> RESTRIÇÃO(ÕES):
*
* -- char nomeDoArquivo[] = Não pode ser um vetor pequeno, pois precisa
* ter capacidade de receber o nome do arquivo.
*/
bool LerArquivo(int * quantidadeDeLinhas, char nomeDoArquivo[]);

/*
*   >> Função que lê os arquivos do arquivo e armazena em vetores.
*
* -- double dados[] = A função atualizara o vetor com os dados da coluna
* esquerda do arquivo.
*
* -- char nomeDoArquivo[] = vetor com o nome do arquivo.
*
* -- double dadosy[] = A função atualizara o vetor com os dados da coluna
* direita do arquivo.
*
*   >> RESTRIÇÃO(ÇÕES):
*
* -- A string NomeDoArquivo precisam estar com as
* suas informações (Isso é feito pela função "LerArquivo").
*
*   >> RETORNO:
* -- Retorna a quantidade de dados se a função conseguir ler o arquivo
* já criado e alimentado com os dados.
*/
int LerDadosDoArquivo(double dados[], char nomeDoArquivo[], double dadosy[]);

/*
*   >> Função que cria a tabela de frequencia dos dados no vetor double dados[].
*
* -- int totalDeDados = Total de dados no vetor double dados[].
*
* -- double dados[] = Vetor com os dados para criação da tabela.
*
* -- double tabela[][7] = Matriz que recebe as informações da tabela. As 7
* colunas são constantes. Segue o que cada coluna irá receber:
* 1ª: Faixa inicial.
* 2ª: Faixa final.
* 3ª: Ponto médio.
* 4ª: Frequência.
* 5ª: Frequência acumulada.
* 6ª: Frequência relativa.
* 7ª: Frequência relativa acumulada.
*
* -- int * totalDeFaixas = A função atualiza essa variavel com o total de
* faixas criadas.
*
*   >> RESTRIÇÃO(ÇÕES):
*
* -- As variaveis totalDeDados e dados[] já precisam estar com as suas
* informações. Isso é feito pela função "LerDadosDoArquivo".
*/
int CriarTabelaDeFrequencia(int totalDeDados, double dados[], double tabelaDados[][7], int * totalDeFaixas);

/*
*   >> Função que estima a moda, media e Desvio padrão, utilizando os dados do vetor dados[] e da tabelaDados[][7].
*
* -- int totalDeDados = Total de dados no vetor double dados[].
*
* -- double dados[] = double dados[] = Vetor com os dados.
*
* -- float *media = Variavel que recebe a média dos do vetor dados[].
*
* -- int totalDeFaixas = Total de faixas da tabelaDados[][7].
*
*   >> RESTRIÇÃO(ÇÕES):
*
* -- As variaveis totalDeDados e dados[] já precisam estar com as suas
* informações. Isso é feito pela função "LerDadosDoArquivo". Assim como
* as variaveis totalDeFaixas e tabelaDados[][7] também precisam (função
* "CriarTabelaDeFrequencia".
*/
int EstimarModaMediaDesvioPadrao(int totalDeDados, double dados[], float * media, int totalDeFaixas, double tabelaDados[][7]);

/*
*   >> Função que recebe um vetor de double a[] e a quantidade total de
* dados desse vetor. O vedor a[] será ordenado em ordem crescente. Essa
* função foi retirada da apostila "Ordenação" do professor Ciro Cirne (Unisantos).
*/
void InsercaoDireta(double a[], int n);

/*
*   >> Função que elabora os valores do Boxplot e indica os outliers (se houver).
*
* -- int totalDeDados = Total de dados no vetor double dados[].
*
* -- double dados[] = double dados[] = Vetor com os dados.
*
*   >> RESTRIÇÃO(ÇÕES):
*
*  -- As variaveis totalDeDados e dados[] já precisam estar com as suas
* informações. Isso é feito pela função "LerDadosDoArquivo".
*/
int Boxplot(int totalDeDados, double dados[]);

/*
*   >> Função que calcula a correação de Pearson e a regressão linear.
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
*   >> RESTRIÇÃO(ÕES):
*
* -- Os valores dos vetores dados[], dadosy[] e a variavel totalDeDados são
* atribuidos na função "LerDadosDoArquivo". Já as variaveis media e mediaY são
* atribuidos na função "EstimarModaMediaDesvioPadrao".
*/
int CorrelacaoPearsonERetaMinQuadrados(int totalDeDados, double dados[], double dadosy[], double media, double mediaY);

#endif // _HEADER_H
