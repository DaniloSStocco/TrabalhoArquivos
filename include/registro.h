#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct registro
{
    char removido;
    int tamanhoPilha;
    int idPoPs;
    int idPoPsConectado;
    int velocidade;
    char unidadeMedida;
} Registro;

typedef struct cabecalho
{
    char status;
    int topoPilha;
    int proxRRN;
    int nroRegRem;
    int nroPares;
} Cabecalho;



#endif