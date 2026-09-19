// Danilo Salmen Stocco - nºUSP 16861501
// Diogo Salmen Stocco - nºUSP 16906441

#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include <stdlib.h>

#define TAM_REG ((sizeof(int)*4) + (sizeof(char)*2)) //18
#define TAM_CAB ((sizeof(int)*4) + sizeof(char)) //17


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

//lê o arquivo, atribui ao registro
int lerRegistro(Registro *reg, FILE *arquivoBin);
//lê o registro, atribui ao arquivo
void escreverRegistro(Registro *reg, FILE *arquivoBin);
//lê o arquivo, atribui ao cabeçalho
void lerCabecalho(Cabecalho *cab, FILE *arquivoBin);
//lê o cabeçalho, atribui ao arquivo
void escreverCabecalho(Cabecalho *cab, FILE *arquivoBin);
void voltaUmRegistro(FILE *arquivoBin);
void acaoBusca(int opcao, Registro *reg, Cabecalho *cab, FILE* arqBin);
void buscaRegistro(FILE *arquivoBin, int opcao);
void imprimirRegistro(Registro reg);
void excluirRegistro(Registro *reg, Cabecalho *cab, FILE* arqBin);
void atualizarRegistro(Registro *reg, FILE *arqBin);

#endif