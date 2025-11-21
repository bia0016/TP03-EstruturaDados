#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "expressao.h"

//pilha de strings
typedef struct {
    char itens[200][512];
    int topo;
}PilhaString;
void pushString(PilhaString *p, const char *str) {
    p->topo++;
    strcpy(p->itens[p->topo], str);
}
char* popString(PilhaString *p) {
    return p->itens[p->topo--];
}

//pilha de floats
typedef struct {
    float itens[200];
    int topo;
}PilhaFloat;
void pushFloat(PilhaFloat *p, float v) {
    p->topo++;
    p->itens[p->topo] = v;
}
float popFloat(PilhaFloat *p) {
    return p->itens[p->topo--];
}

//funções auxiliares
int isNumero(const char *token) {
    int i = 0;
    int ponto = 0;
    while (token[i] != '\0') {
        if (token[i] == '.') {
            if (ponto) return 0;
            ponto = 1;
        }
        else if (token[i] < '0' || token[i] > '9')
            return 0;
        i++;
    }
    return 1;
}
int isOperador(const char *t) {
    return (
        strcmp(t, "+") == 0 ||
        strcmp(t, "-") == 0 ||
        strcmp(t, "*") == 0 ||
        strcmp(t, "/") == 0 ||
        strcmp(t, "%") == 0 ||
        strcmp(t, "^") == 0
    );
}
int isFuncao(const char *t) {
    return (
        strcmp(t, "sen") == 0 ||
        strcmp(t, "cos") == 0 ||
        strcmp(t, "tg")  == 0 ||
        strcmp(t, "log") == 0 ||
        strcmp(t, "raiz")== 0
    );
}

//conversão para InFixa
char * getFormaInFixa(char *Str) {
    PilhaString p;
    p.topo = -1;
    char *resultado = malloc(512);
    if (!resultado) return NULL;
    char copia[512];
    strcpy(copia, Str);
    char *token = strtok(copia, " ");
    while (token != NULL) {
        //numero
        if (isNumero(token)) {
            pushString(&p, token);
        }
        //operador binário
        else if (isOperador(token)) {
            char *b = popString(&p);
            char *a = popString(&p);
            char temp[512];
            sprintf(temp, "(%s%s%s)", a, token, b);
            pushString(&p, temp);
        }
        //função
        else if (isFuncao(token)) {
            char *a = popString(&p);
            char temp[512];
            sprintf(temp, "%s(%s)", token, a);
            pushString(&p, temp);
        }
        token = strtok(NULL, " ");
    }
    strcpy(resultado, popString(&p));
    return resultado;
}

//valor da expressao
float getValorPosFixa(char *StrPosFixa) {
    PilhaFloat p;
    p.topo = -1;
    char copia[512];
    strcpy(copia, StrPosFixa);
    char *token = strtok(copia, " ");
    while (token != NULL) {
        //numero
        if (isNumero(token)) {
            pushFloat(&p, atof(token));
        }

        //operadores binarios
        else if (isOperador(token)) {
            float b = popFloat(&p);
            float a = popFloat(&p);
            float r = 0;
            if (strcmp(token, "+") == 0) r = a + b;
            else if (strcmp(token, "-") == 0) r = a - b;
            else if (strcmp(token, "*") == 0) r = a * b;
            else if (strcmp(token, "/") == 0) r = a / b;
            else if (strcmp(token, "%") == 0) r = fmod(a, b);
            else if (strcmp(token, "^") == 0) r = pow(a, b);
            pushFloat(&p, r);
        }

        //funções
        else if (isFuncao(token)) {
            float x = popFloat(&p);
            float r = 0;
            if (strcmp(token, "sen") == 0)
                r = sin(x * M_PI / 180.0);
            else if (strcmp(token, "cos") == 0)
                r = cos(x * M_PI / 180.0);
            else if (strcmp(token, "tg") == 0)
                r = tan(x * M_PI / 180.0);
            else if (strcmp(token, "log") == 0)
                r = log10(x);
            else if (strcmp(token, "raiz") == 0)
                r = sqrt(x);
            pushFloat(&p, r);
        }
        token = strtok(NULL, " ");
    }
    return popFloat(&p);
}
