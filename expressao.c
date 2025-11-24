#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "expressao.h"

#define TO_RAD(g) ((g) * M_PI / 180.0)
#define MAX 500

typedef struct{
    char *itens[MAX];
    int topo;
}PilhaString;
void pushString(PilhaString *p, const char *str){
    p->topo++;
    p->itens[p->topo] = (char*) malloc(strlen(str) + 1);
    strcpy(p->itens[p->topo], str);
}
char *popString(PilhaString *p){
    return p->itens[p->topo--];
}

typedef struct{
    float itens[MAX];
    int topo;
}PilhaFloat;
void pushFloat(PilhaFloat *p, float v){
    p->topo++;
    p->itens[p->topo] = v;
}
float popFloat(PilhaFloat *p){
    return p->itens[p->topo--];
}

//funções auxiliares
int seNumero(const char *token){
    int i = 0;
    int ponto = 0;
    while(token[i] != '\0'){
        if(token[i] == '.'){
            if(ponto){return 0;}
            ponto = 1;
        }
        else if(token[i] < '0' || token[i] > '9'){return 0;}
        i++;
    }
    return 1;
}
int seOperador(const char *t){
    return (strcmp(t, "+") == 0 || strcmp(t, "-") == 0 ||
    strcmp(t, "*") == 0 || strcmp(t, "/") == 0 || strcmp(t, "%") == 0 
    || strcmp(t, "^") == 0);
}
int seFuncao(const char *t){
    return (strcmp(t, "sen") == 0 || strcmp(t, "cos") == 0 || 
    strcmp(t, "tg")  == 0 || strcmp(t, "log") == 0 || strcmp(t, "raiz")== 0);
}

//conversão para InFixa
char * getFormaInFixa(char *Str){
    PilhaString p;
    p.topo = -1;
    char *resultado = malloc(MAX);
    if (!resultado) return NULL;
    char copia[MAX];
    strcpy(copia, Str);
    char * token = strtok(copia, " ");
    while(token != NULL){
        //verifica se é numero
        if(seNumero(token)){
            pushString(&p, token);
        }
        //verficar operador binário
        else if(seOperador(token)){
            char *b = popString(&p);
            char *a = popString(&p);
            char temp[MAX];
            sprintf(temp, "(%s%s%s)", a, token, b);
            pushString(&p, temp);
            free(b);
            free(a);
        }
        //verificar  função
        else if(seFuncao(token)){
            char *a = popString(&p);
            char temp[MAX];
            sprintf(temp, "%s(%s)", token, a);
            pushString(&p, temp);
            free(a);
        }
        token = strtok(NULL, " ");
    }
    char *final = popString(&p);
    strcpy(resultado, final);
    free(final);
    return resultado;
}

//valor da expressao
float getValorPosFixa(char *StrPosFixa){
    PilhaFloat p;
    p.topo = -1;
    char copia[MAX];
    strcpy(copia, StrPosFixa);
    char *token = strtok(copia, " ");
    while(token != NULL){
        //verifica se e numero
        if(seNumero(token)){
            pushFloat(&p, atof(token));
        }
        //faz verficação de operadores binarios
        else if(seOperador(token)){
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
        //verifica funções
        else if (seFuncao(token)){
            float x = popFloat(&p);
            float r = 0;
            if (strcmp(token, "sen") == 0)
                r = sin(TO_RAD(x));
            else if (strcmp(token, "cos") == 0)
                r = cos(TO_RAD(x));
            else if (strcmp(token, "tg") == 0)
                r = tan(TO_RAD(x));
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
