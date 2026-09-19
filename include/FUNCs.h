#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct busca_par
{
    char NomeCampo[20];
    char ValorCampo[20];
} BuscaPar;

//CREATE
void FUNC1(char *NomeArquivoEntrada, char*NomeArquivoBin);
//SELECT
void FUNC2(char *NomeArquivoBin);
//SELECT WHERE
void FUNC3(char *NomeArquivoBin);
//SELECT WHERE RRN
void FUNC4(char *NomeArquivoBin);
//DELETE WHERE
void FUNC5(char *NomeArquivoBin);
//INSERT INTO
void FUNC6(char *NomeArquivoBin);
//UPDATE WHERE
void FUNC7(char *NomeArquivoBin);

#endif