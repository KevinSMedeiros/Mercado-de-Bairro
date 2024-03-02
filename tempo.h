#ifndef __TEMPO_H__
#define __TEMPO_H__

#include <stdbool.h>

/* Definição de um registro para armazenar as datas
*/
typedef struct DATA
{
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
} DATA ;


/**
 * Função que converte texto para o tipo DATA
 * @param str String que tem a data
 * @param data Registro do tipo DATA que irá armazenar a data convertida
*/
void StringToData(char *str, DATA *data);


/**
 * Função que obtem a data e horário atual
 * @return retorna a informação na estrutura DATA
 * * 
*/
DATA hoje();

/**
 * Monta uma string a partir de uma data
 * @param p Um registro do tipo DATA com os dados para montagem da string
 * @param output Ponteiro para a string onde os dados colocados
 * @param complete Se true a string deve ser montada com horas, minutos e segundos, 
 * caso contrário deve-se montar a string apenas com dia, mês e ano
*/
int DataToString(DATA p, char *output, bool complete);


/**
 * Compara duas datas e retorna 0 se as datas forem iguais 
 * ou um valor positivo se a data d1 for mais recente que d2 e negativo caso contrário
 * @param d1 variável do tipo DATA para comparação
 * @param d2 variável do tipo DATA para comparação
 * @return retorna 0 se as datas forem iguais, 1 se a data d1 for mais recente que d2 
 * e -1 caso contrário
*/
int DataCmp(DATA d1, DATA d2);

#endif
  