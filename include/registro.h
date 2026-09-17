#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct registro
{
    char removido;
    int encadeamentoPilha;
    int idPoPs;
    int idPoPsConectado;
    int velocidade;
    char unidadeMedida;

    int RRN; //endereço do reg no arquivo (tamCabeçalho + (RRN * tamRegistro) = endereço)
} Registro;

typedef struct cabecalho
{
    char status;
    int topoPilha;
    int proxRRN;
    int nroRegRem;
    int nroPares;
} Cabecalho;

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

#endif