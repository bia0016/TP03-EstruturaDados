#include <stdio.h>
#include <stdlib.h>
#include "expressao.h"

int main() {

    //meu teste
    char *infixa = getFormaInFixa("4 4 +");
    float valor = getValorPosFixa("4 4 +");
    printf("Infixa: %s\n", infixa);
    printf("Valor: %.2f\n", valor);
    free(infixa);

    //meu teste1
    char *infixa1 = getFormaInFixa("14 10 * 12 /");
    float valor01 = getValorPosFixa("14 10 * 12 /");
    printf("Infixa: %s\n", infixa1);
    printf("Valor: %.2f\n", valor01);
    free(infixa1);

    //meu teste2
    char *infixa2 = getFormaInFixa("14 10 12 + 6 9 * / %");
    float valor02 = getValorPosFixa("14 10 12 + 6 9 * / %");
    printf("Infixa: %s\n", infixa2);
    printf("Valor: %.2f\n", valor02);
    free(infixa2);

    //meu teste3
    char *infixa3 = getFormaInFixa("5 2 3 + 4 * -");
    float valor03 = getValorPosFixa("5 2 3 + 4 * -");
    printf("Infixa: %s\n", infixa3);
    printf("Valor: %.2f\n", valor03);
    free(infixa3);

    //teste 1
    char *teste1 = getFormaInFixa("3 4 + 5 *");
    float valor1 = getValorPosFixa("3 4 + 5 *");
    printf("Infixa: %s\n", teste1);
    printf("Valor: %.2f\n", valor1);
    free(teste1);

    //teste2
    char *teste2 = getFormaInFixa("7 2 * 4 +");
    float valor2 = getValorPosFixa("7 2 * 4 +");
    printf("Infixa: %s\n", teste2);
    printf("Valor: %.2f\n", valor2);
    free(teste2);

    //teste3
    char *teste3 = getFormaInFixa("8 5 2 4 + * +");
    float valor3 = getValorPosFixa("8 5 2 4 + * +");
    printf("Infixa: %s\n", teste3);
    printf("Valor: %.2f\n", valor3);
    free(teste3);

    //teste4
    char *teste4 = getFormaInFixa("6 2 / 3 + 4 *");
    float valor4 = getValorPosFixa("6 2 / 3 + 4 *");
    printf("Infixa: %s\n", teste4);
    printf("Valor: %.2f\n", valor4);
    free(teste4);

    //teste5
    char *teste5 = getFormaInFixa("9 5 2 8 * 4 + * +");
    float valor5 = getValorPosFixa("9 5 2 8 * 4 + * +");
    printf("Infixa: %s\n", teste5);
    printf("Valor: %.2f\n", valor5);
    free(teste5);

    //teste6
    char *teste6 = getFormaInFixa("2 3 + log 5 /");
    float valor6 = getValorPosFixa("2 3 + log 5 /");
    printf("Infixa: %s\n", teste6);
    printf("Valor: %.2f\n", valor6);
    free(teste6);

    //teste7
    char *teste7 = getFormaInFixa("10 log 3 ^ 2 +");
    float valor7 = getValorPosFixa("10 log 3 ^ 2 +");
    printf("Infixa: %s\n", teste7);
    printf("Valor: %.2f\n", valor7);
    free(teste7);

    //teste8
    char *teste8 = getFormaInFixa("45 60 + 30 cos *");
    float valor8 = getValorPosFixa("45 60 + 30 cos *");
    printf("Infixa: %s\n", teste8);
    printf("Valor: %.2f\n", valor8);
    free(teste8);

    //teste9
    char *teste9 = getFormaInFixa("0.5 45 sen 2 ^ +");
    float valor9 = getValorPosFixa("0.5 45 sen 2 ^ +");
    printf("Infixa: %s\n", teste9);
    printf("Valor: %.2f\n", valor9);
    free(teste9);

    return 0;
}