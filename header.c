#include "header.h"


bool LerArquivo(int * quantidadeDeLinhas, char nomeDoArquivo[]) {

    int opcao;
    printf("-- Ja possui um arquivo criado? (1 = Sim/2 = Nao):\n>>> ");
    scanf("%d", &opcao);
    fflush(stdin);

    if (opcao == 1) { /* Opcao para ler um arquivo ja criado */

        printf("-- Nome do arquivo (Informe o nome + extencao. Ex: dados.txt):\n>>> ");
        scanf("%99[^\n]", nomeDoArquivo);
        fflush(stdin);

        FILE *arquivo = fopen(nomeDoArquivo, "r");

        if (arquivo == NULL) {
            printf("-- Nao foi possivel ler o arquivo %s. Certifique-se de te-lo criado.\n", nomeDoArquivo);
            return false;
        }

        char conteudoDoArquivo[200];
        *quantidadeDeLinhas = 0;

        while(fgets(conteudoDoArquivo,199,arquivo) != NULL) {
            *quantidadeDeLinhas += 1;
        }
        fclose(arquivo);
        return true;
    } else {

    if (opcao == 2){ /* Opcao para criar um arquivo */

        printf("-- Criaremos um arquivo .txt. Digite o nome desejado:\n>>> ");
        scanf("%99[^\n]", nomeDoArquivo);
        fflush(stdin);

        strcat(nomeDoArquivo, ".txt");

        FILE *arquivo = fopen(nomeDoArquivo, "w");

        if (arquivo == NULL) {
            printf("-- Nao foi possivel criar o arquivo %s.\nProvavelmente alguma protecao do computador bloqueou.\nTente cria-lo manualmente, fora do programa.\n", nomeDoArquivo);
            return false;
        } else {
            printf("-- Arquivo %s criado com sucesso.\nAlimente o arquivo com os dados e volte nessa etapa.\n", nomeDoArquivo);
            fclose(arquivo);
            return false;
        }

    } else {
        printf("-- Opcao invalida.\n");
        return false;
    }
    }

}

int LerDadosDoArquivo(double dados[], char nomeDoArquivo[], double dadosy[]) {

    FILE *arquivo = fopen(nomeDoArquivo, "r");

    if (arquivo == NULL) {
        printf("-- Nao foi possivel ler o arquivo %s. Certifique-se de te-lo criado.\n", nomeDoArquivo);
        return 2;
    }


    int i=0;
    double x,y;
    char c;

     while (!feof(arquivo)) {
        fscanf(arquivo,"%lf%c%lf", &x, &c ,&y);
        dados[i] = x;
        dadosy[i] = y;
        i++;
    }

    fclose(arquivo);

    return i;
}

int CriarTabelaDeFrequencia(int totalDeDados, double dados[], double tabelaDados[][7], int * totalDeFaixas) {

    int i, j;
    double max = dados[0], amplitude,aux;
    double min = dados[0];

    for (i=1; i < totalDeDados; i++) {
        if (dados[i] > max) {
            max = dados[i];
        }
        if (dados[i] < min) {
            min = dados[i];
        }
    }

    amplitude = max - min;
    double n = 3.3 * log10(totalDeDados);
    n = ((int) n) + 1;
    double d = amplitude / n;

    double dAuxiliar = (int) (d * 100);
    d = dAuxiliar / 100;


    double auxiliar, TamanhoIntervalo = d;

    /* Ajustar o intervalo */

    if ( (int) d == 0 ) {
        d += 0.01;
    } else {

        auxiliar = ((int) d) % 100;

        if (auxiliar == 0) {
            TamanhoIntervalo += 0.05;
        } else if (auxiliar < 5) {
            auxiliar = 5 - auxiliar;
            auxiliar = auxiliar / 100;
            TamanhoIntervalo += auxiliar;
        } else if (auxiliar == 5) {
            TamanhoIntervalo += 0.05;
        } else if (auxiliar <= 9) {
            auxiliar = 9 - auxiliar;
            auxiliar = auxiliar / 100;
            TamanhoIntervalo += auxiliar;
        }

    }



    /* Descobrir intervalo */

    aux = min;

    *totalDeFaixas = 0;
    while (aux <= max) {
        aux += TamanhoIntervalo;
        *totalDeFaixas+=1;
    }


    aux = min;
    for (i=0; i < *totalDeFaixas; i++) { /* Construir as colunas 0 e 1 - Faixas de valores*/
        tabelaDados[i][0] = aux;
        aux += TamanhoIntervalo;
        tabelaDados[i][1] = aux;
    }

    for (i=0; i < *totalDeFaixas; i++) { /* Construir a coluna 2 Ponto Medio */
        tabelaDados[i][2] = (tabelaDados[i][0] + tabelaDados[i][1]) / 2;
    }

    for (i=0; i < *totalDeFaixas; i++) { /* Construir a coluna 3 - Frequencia */
        tabelaDados[i][3] = 0;

        for (j=0; j < totalDeDados; j++) {

            if (  (int) (dados[j] * LIMDECIMAIS) >= (int) (tabelaDados[i][0] * LIMDECIMAIS) &&  ( (int) (dados[j] * LIMDECIMAIS) < (int) (tabelaDados[i][1] * LIMDECIMAIS) ) ) {
                tabelaDados[i][3] +=1;
            }

        }

    }


    aux = 0;
    for (i=0; i < *totalDeFaixas; i++) { /* Construir a coluna 4 - Frequencia acumulada*/
        aux += tabelaDados[i][3];
        tabelaDados[i][4] = aux;
    }

    for (i=0; i < *totalDeFaixas; i++) {/* Construir a coluna 5 - Frequencia relativa*/
        tabelaDados[i][5] = tabelaDados[i][3] / aux;
    }

    for (i=0; i < *totalDeFaixas; i++) {/* Construir a coluna 6 - Frequencia acumulada*/
        tabelaDados[i][6] = tabelaDados[i][4] / aux;
    }

    printf("Faixa de valores  P.M.     Freq.     Freq. Acum.     Freq. Rel.     Freq. Rel. Acum.\n");
    for (i=0; i < *totalDeFaixas; i++) { // Imprimir a tabela final
            printf( "%-5.2lf|-- %-8.2lf %-9.2lf %-11.2lf %-14.2lf %-15.3lf %.3lf\n", tabelaDados[i][0],tabelaDados[i][1],tabelaDados[i][2],tabelaDados[i][3],tabelaDados[i][4],tabelaDados[i][5],tabelaDados[i][6]);
    }

    return 0;
}

int EstimarModaMediaDesvioPadrao(int totalDeDados, double dados[], float * media, int totalDeFaixas, double tabelaDados[][7]) {

    int i;
    double total = 0;


    printf("\n\t-- Utilizando os valores do arquivo:\n");

    for (i=0; i < totalDeDados; i++) { /*Descobrir a media*/
        total += dados[i];
    }

    *media = total / totalDeDados;
    printf("-- Media: %.2lf.\n", *media);

    double auxDados[totalDeDados];
    for (i=0; i < totalDeDados; i++) { /* Nao perder a sequencia dos valores*/
        auxDados[i] = dados[i];
    }

    InsercaoDireta(dados, totalDeDados); /*Ordenar os dados*/

    double setDados[totalDeDados];
    int indiceSetDados = 0, j;
    bool achou;

    for (i=0; i < totalDeDados; i++) { /* Criar um novo vetor sem repeticao nos dados*/
        achou = false;
        for(j=0; j < indiceSetDados; j++) {
            if ( (int) (setDados[j] * LIMDECIMAIS) == (int) (dados[i] * LIMDECIMAIS) ) {
                achou = true;
            }
        }
        if (!achou) {
            setDados[indiceSetDados] = dados[i];
            indiceSetDados++;
        }
    }

    int contarModa[indiceSetDados];


    for (i=0; i < indiceSetDados; i++) { /* contar quantas vezes um valor aparece */
        contarModa[i] = 0;
        for (j=0; j < totalDeDados; j++) {
            if ((int) (setDados[i] * LIMDECIMAIS) == (int) (dados[j] * LIMDECIMAIS)) {
                contarModa[i]++;
            }
        }
    }

    int max = contarModa[0], min = contarModa[0];

    for (i=1; i < indiceSetDados; i++) { /* Verificar os dados moda */
        if (contarModa[i] > max) {
            max = contarModa[i];
        }
        if (contarModa[i] < min) {
            min = contarModa[i];
        }
    }

    if (max == 1) { /* Verificar o tipo de moda */
        printf("-- Moda: Amodal. Sem moda, sem valores repetidos.\n");
    } else if (max == min) {
        printf("-- Moda: Todos os dados se repetem %d vezes.\n", max);
    } else {
        int count = 0;

        for (i=0; i < indiceSetDados; i++) {
            if (contarModa[i] == max) {
                count++;
            }
        }

        if (count == 1) {
            printf("-- Moda: Unimodal [ ");

            for (i=0; i < indiceSetDados; i++) {
                if (contarModa[i] == max) {
                    printf("%.2lf ].\n", setDados[i]);
                    break;
                }
            }

        } else if (count == 2) {
            printf("-- Moda: Bimodal [ ");

            for (i=0; i < indiceSetDados; i++) {
                if (contarModa[i] == max) {
                    printf("%.2f, ", setDados[i]);
                }
            }
            printf("\b\b ].\n");
        } else {
            printf("-- Moda: Multimodal [ ");

            for (i=0; i < indiceSetDados; i++) {
                if (contarModa[i] == max) {
                    printf("%.2lf, ", setDados[i]);
                }
            }
            printf("\b\b ].\n");
        }

    }


    double auxDesvioPadrao[totalDeDados];
    double totalAuxDesvioPadrao = 0;

    for (i=0; i < totalDeDados; i++) {
        auxDesvioPadrao[i] = dados[i] - *media;
        auxDesvioPadrao[i] = pow(auxDesvioPadrao[i],2);
        totalAuxDesvioPadrao += auxDesvioPadrao[i];
    }

    double variancia = totalAuxDesvioPadrao / totalDeDados;
    double desvioPadrao = sqrt(variancia);

    printf("-- Desvio Padrao: %.2lf.\n", desvioPadrao);


    printf("\n\t-- Utilizando a tabela de frequencia:\n");


    double pontoMedioXFrequencia, total2 = 0, media2;

    for (i=0; i < totalDeFaixas; i++) { /* Descobrir a media da tabela */
        pontoMedioXFrequencia = tabelaDados[i][2] * tabelaDados[i][3];
        total2 += pontoMedioXFrequencia;
    }

    media2 = total2 / tabelaDados[totalDeFaixas-1][4];
    printf("-- Media: %.2lf.\n", media2);

    double maxFrequencia = tabelaDados[0][3], minFrequencia = tabelaDados[0][3];

    for (i=0; i < totalDeFaixas; i++) { /* Descobrir a moda da tabela */
        if ( (int)(maxFrequencia * LIMDECIMAIS) < (int) (tabelaDados[i][3] * LIMDECIMAIS)) {
            maxFrequencia = tabelaDados[i][3];
        }
        if ((int) (minFrequencia * LIMDECIMAIS) > (int) (tabelaDados[i][3] * LIMDECIMAIS)) {
            minFrequencia = tabelaDados[i][3];
        }
    }

    double limiteInferiorDaClasse, amplitudeClasseModal, delta1, delta2, moda;

    if ((int) (minFrequencia * LIMDECIMAIS) == (int) (maxFrequencia * LIMDECIMAIS)) {
        printf("-- Moda: Todas as classes possuem a mesma frequencia.\n");
        printf("-- Min Frequencia: %.2lf e Max Frequencia: %.2lf\n", minFrequencia, maxFrequencia);
    } else {

        printf("-- Moda: [ ");
        for (i=0; i < totalDeFaixas; i++) {

            if ( (int) (tabelaDados[i][3] * LIMDECIMAIS) == (int) (maxFrequencia * LIMDECIMAIS)) {


                limiteInferiorDaClasse = tabelaDados[i][0];

                amplitudeClasseModal = tabelaDados[i][1] - tabelaDados[i][0];

                if (i == totalDeFaixas - 1) {
                    delta2 = tabelaDados[i][3];
                } else {

                    delta2 = tabelaDados[i][3] - tabelaDados[i+1][3];
                }

                if (i == 0) {
                    delta1 = tabelaDados[i][3];
                } else {
                    delta1 = tabelaDados[i][3] - tabelaDados[i-1][3];
                }

                if ( delta1 + delta2 == 0 ) {
                    moda = limiteInferiorDaClasse;
                } else {
                    moda = limiteInferiorDaClasse + ( ( delta1 / (delta1 + delta2) ) * amplitudeClasseModal);
                }


                printf("%.2lf, ", moda);
            }
        }
        printf("\b\b ]\n");
    }


    float pontoMedioAoQuadradoXfrequencia, total3 = 0, desvioPadrao2;

    for (i=0; i < totalDeFaixas; i++) { /* Descobrir Desvio Padrao na tabela */
        pontoMedioAoQuadradoXfrequencia = pow(tabelaDados[i][2],2) * tabelaDados[i][3];
        total3 += pontoMedioAoQuadradoXfrequencia;
    }

    desvioPadrao2 = ( total3 - tabelaDados[totalDeFaixas-1][4] * pow(media2,2) ) / ( tabelaDados[totalDeFaixas-1][4] - 1 );
    desvioPadrao2 = sqrt(desvioPadrao2);


    printf("-- Desvio Padrao: %.2f.\n", desvioPadrao2);

    for (i=0; i < totalDeDados; i++) { /* Nao perder a sequencia dos valores*/
        dados[i] = auxDados[i];
    }

    return 0;
}

void InsercaoDireta(double a[], int n) {
     int i, j;
     double x;
     for (i = 1; i < n; i++) {
         x = a[i];
         j = i - 1;
     while (j >= 0 && (int) (a[j] * LIMDECIMAIS) > (int) (x * LIMDECIMAIS)) {
         a[j + 1] = a[j]; // Desloca o elemento para a direita
         j--;
     }
        a[j + 1] = x; // Insere o elemento na posição correta
     }
}

int Boxplot(int totalDeDados, double dados[]){

    int i;
    double auxDados[totalDeDados];
    for (i=0; i < totalDeDados; i++) { /* Nao perder a sequencia dos valores*/
        auxDados[i] = dados[i];
    }

    InsercaoDireta(dados, totalDeDados);

    printf("\n-- Dados que serao analisados:\n");

    printf("[ ");
    for (i=0; i < totalDeDados; i++) {
        printf("%.2lf, ", dados[i]);
    }
    printf("\b\b ]\n\n");


    double rmPosicao = ( totalDeDados + 1.0 ) / 2.0 , rm;

    if ((int) rmPosicao - rmPosicao != 0) {
        rm = ( dados[ ((int) rmPosicao) - 1] + dados[ ((int) rmPosicao)] ) / 2;
    } else {
        rm = dados[ ((int) rmPosicao ) - 1];
    }

    printf("-- Media: %.2lf - Posicao: %.2lf.\n", rm, rmPosicao);

    double rq1Posicao = (rmPosicao + 1) / 2, rq1;

    if ((int) rq1Posicao - rq1Posicao != 0) {
        rq1 = ( dados[ ((int) rq1Posicao) - 1] + dados[ ((int) rq1Posicao)] ) / 2;
    } else {
        rq1 = dados[ ((int) rq1Posicao ) - 1];
    }

    printf("-- Quartil 1: %.2lf - Posicao: %.2lf.\n", rq1, rq1Posicao);

    double rq3Posicao = (int) rmPosicao + rq1Posicao, rq3;

    if ((int) rq3Posicao - rq3Posicao != 0) {
        rq3 = ( dados[ ((int) rq3Posicao) - 1] + dados[ ((int) rq3Posicao)] ) / 2;
    } else {
        rq3 = dados[ ((int) rq3Posicao ) - 1];
    }

    printf("-- Quartil 3: %.2lf - Posicao: %.2lf.\n", rq3, rq3Posicao);

    double distanciaIntequatil = rq3 - rq1;

    double limINF = rq1 - (1.5 * distanciaIntequatil), limSUP = rq3 + (1.5 * distanciaIntequatil);

    printf("\n-- Limite inferior: %.2lf.\n", limINF);

    printf("Outliers (se houver): [  ");
    for (i=0; i < totalDeDados; i++) {
        if ( (int) (dados[i] * LIMDECIMAIS) < (int) (limINF * LIMDECIMAIS)) {
            printf("%.2lf, ", dados[i]);
        }
    }
    printf("\b\b  ].");

    printf("\n-- Limite superior: %.2lf.\n", limSUP);

    printf("-- Outliers (se houver): [  ");
    for (i=0; i < totalDeDados; i++) {
        if ( (int) (dados[i] * LIMDECIMAIS) > (int) (limSUP * LIMDECIMAIS)) {
            printf("%.2lf, ", dados[i]);
        }
    }
    printf("\b\b  ].\n\n");

    for (i=0; i < totalDeDados; i++) { /* Nao perder a sequencia dos valores*/
        dados[i] = auxDados[i];
    }

    return 0;
}

int CorrelacaoPearsonERetaMinQuadrados(int totalDeDados, double dados[], double dadosy[], double media, double mediaY){

    double aux;
    double totalAux = 0;
    int i;

    for (i=0; i < totalDeDados; i++) {
        aux = dados[i] - media;
        aux = pow(aux,2);
        totalAux += aux;
    }

    double varianciaX = totalAux / totalDeDados; /* Variancia de X*/
    varianciaX = sqrt(varianciaX);

    totalAux = 0;
    for (i=0; i < totalDeDados; i++) {
        aux = dadosy[i] - mediaY;
        aux = pow(aux,2);
        totalAux += aux;
    }

    double varianciaY = totalAux / totalDeDados; /* Variancia de Y*/
    varianciaY = sqrt(varianciaY);

    totalAux = 0;
    for (i=0; i < totalDeDados; i++) {
        aux = dados[i] * dadosy[i];
        totalAux += aux;
    }

    double mediaXmultiplicadoY = totalAux / totalDeDados; /* 1/n E(x * y) */

    double r = ( mediaXmultiplicadoY - (media * mediaY) ) / (varianciaX*varianciaY) ;

    printf("-- Correlacao Pearson: %.2lf.\n\n\t-- Regressao Linear:\n", r);

    totalAux = 0;

    for (i=0; i < totalDeDados; i++) {
        totalAux += pow(dados[i],2);
    }

    double auxA = totalAux / totalDeDados;
    auxA = auxA - pow(media,2);
    double a = ( mediaXmultiplicadoY - (media * mediaY) ) / auxA;

    printf("-- a = %.5lf.\n", a);

    double b = mediaY - (a * media);
    printf("-- b = %.3lf.\n", b);

    if (b > 0) {
        printf("-- y = %.3lfx+%.3lf.\n", a,b);
    } else {
        printf("-- y = %.3lfx%.3lf.\n",a,b);
    }
    return 0;
}
