#include "tempo.h"
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


/**
 * Função que converte texto para o tipo DATA
 * @param str String que tem a data
 * @param data Registro do tipo DATA que irá armazenar a data convertida
*/
void StringToData(char *str, DATA *data)
{
    int i = 0, c=0;
    char tmp[5];
    while( str[i] != '/')
    {
        tmp[c++] = str[i++];
    }
    tmp[c] = 0;
    data->dia = atoi(tmp);
    c = 0;
    i++;
    while( str[i] != '/')
    {
        tmp[c++] = str[i++];
    }
    tmp[c] = 0;
    data->mes = atoi(tmp);
    c = 0;
    i++;
    while( str[i] != 0)
    {
        tmp[c++] = str[i++];
    }
    tmp[c] = 0;
    data->ano = atoi(tmp);
}


/**
 * Função que obtem a data e horário atual
 * @return retorna a informação na estrutura DATA
 * *
*/
DATA hoje()
{
    //char instante[30];
    struct tm *instante ;
    DATA d;
    time_t result = time(NULL);
    instante = localtime(&result);
    //strcpy(instante, ctime(&result));
    // printf("Agora: %s");
    // distribuindo
    d.hora = instante->tm_hour;
    d.minuto = instante->tm_min;
    d.segundo = instante->tm_sec;
    d.ano = instante->tm_year + 1900;
    d.mes = instante->tm_mon + 1;
    d.dia = instante->tm_mday;
    return d;
    //

}

/**
 * Monta uma string a partir de uma data
 * @param p Um registro do tipo DATA com os dados para montagem da string
 * @param output Ponteiro para a string onde os dados colocados
 * @param complete Se true a string deve ser montada com horas, minutos e segundos,
 * caso contrário deve-se montar a string apenas com dia, mês e ano
*/
int DataToString(DATA p, char *output, bool complete)
{
    if (complete == false)
        sprintf(output,"%02d\\%02d\\%d", p.dia, p.mes, p.ano);
    else
        sprintf(output,"%02d:%02d:%02d %02d\\%02d\\%d", p.hora,p.minuto, p.segundo, p.dia, p.mes, p.ano);

    return strlen(output);
}


int comparaValor(int t)
{
    if (t == 0 )
        return 0;
    else if ( t > 0 )
        return 1;
    else return -1;
}

/**
 * Compara duas datas e retorna 0 se as datas forem iguais
 * ou um valor positivo se a data d1 for mais recente que d2 e negativo caso contrário
 * @param d1 variável do tipo DATA para comparação
 * @param d2 variável do tipo DATA para comparação
 * @return retorna 0 se as datas forem iguais, 1 se a data d1 for mais recente que d2
 * e -1 caso contrário
*/
int DataCmp(DATA d1, DATA d2)
{
    int tmp;
    tmp = d1.ano - d2.ano;
    tmp = comparaValor(tmp);
    if (tmp != 0)
        return tmp;
    tmp = d1.mes - d2.mes;
    tmp = comparaValor(tmp);
    if (tmp != 0)
        return tmp;
    tmp = d1.dia - d2.dia;
    tmp = comparaValor(tmp);
    return tmp;
}

