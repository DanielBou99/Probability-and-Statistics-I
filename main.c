/* main.c
*
* Programa que analisa dois conjuntos de
* dados individualmente e também correlacionados.
*
* Daniel Bou de Souza (Ciência da Computação).
* Maurício da Silva Freire (Ciência da Computação).
* Victor Gabriel Martins e Souza (Ciência da Computação).
*
* Disciplina: PROBABILIDADE E ESTATÍSTICA APLICADA I.
*
* 02/06/2019.
*/

#include "header.h"


int main()
{

    int quantidadeDeLinhas, totalDeDados, totalDeFaixas;
    char nomeDoArquivo[100];
    float media, mediay;
    double dados[MAX], tabelaDados[MAX][7];

    int totalDeFaixasy;
    double dadosy[MAX], tabelaDadosy[MAX][7];

    int opcao;

    do {
        printf("\n*IMPORTANTE*: Nao pule etapas!\n");
        printf("Dados X = Coluna de dados da esquerda do arquivo.\nDados Y = Coluna de dados da direita do arquivo.\n\n");
        printf("Menu Principal\n--------------\n");
        printf("Etapa 1 - Ler os dados do arquivo.\n");
        printf("Etapa 2 - Construir a tabela de frequencia dos dados X.\n");
        printf("Etapa 3 - Construir a tabela de frequencia dos dados Y.\n");
        printf("Etapa 4 - Estimar a moda, media e o desvio padrao da tabela X.\n");
        printf("Etapa 5 - Estimar a moda, media e o desvio padrao da tabela Y.\n");
        printf("Etapa 6 - Construir o box-plot e estimar os outliers dos dados X.\n");
        printf("Etapa 7 - Construir o box-plot e estimar os outliers dos dados Y.\n");
        printf("Etapa 8 - Calcular o coeficiente de correlacao de Pearson e os coeficientes da reta de minimos quadrados.\n");
        printf("Opcao 0 - Sair.\n");
        printf("--------------\nInforme o numero da etapa:\n>>> ");
        scanf("%d", &opcao);
        fflush(stdin);
        system("cls");
        printf("\n\n");
        switch (opcao) {

            case 0:
                break;
            case 1:
                if (LerArquivo(&quantidadeDeLinhas, nomeDoArquivo)) {
                    totalDeDados = LerDadosDoArquivo(dados, nomeDoArquivo, dadosy);
                }
                break;
            case 2:
                printf("\t-- Tabela dos dados X:\n");
                CriarTabelaDeFrequencia(totalDeDados, dados, tabelaDados, &totalDeFaixas);
                break;
            case 3:
                printf("\t-- Tabela dos dados Y:\n");
                CriarTabelaDeFrequencia(totalDeDados, dadosy, tabelaDadosy, &totalDeFaixasy);
                break;
            case 4:
                printf("\t-- Estimativa dos dados X:\n");
                EstimarModaMediaDesvioPadrao(totalDeDados, dados, &media, totalDeFaixas, tabelaDados);
                break;
            case 5:
                printf("\t-- Estimativa dos dados Y:\n");
                EstimarModaMediaDesvioPadrao(totalDeDados, dadosy, &mediay, totalDeFaixasy, tabelaDadosy);
                break;
            case 6:
                printf("\t-- Boxplot e outliers dos dados X:\n");
                Boxplot(totalDeDados, dados);
                break;
            case 7:
                printf("\t-- Boxplot e outliers dos dados Y:\n");
                Boxplot(totalDeDados, dadosy);
                break;
            case 8:
                CorrelacaoPearsonERetaMinQuadrados(totalDeDados, dados, dadosy, media, mediay);
                break;
            default:
                printf("-- Opcao invalida.\n");
        }
        system("pause");
        system("cls");
        printf("\n\n");

    } while (opcao != 0);

    return 0;
}
