#include <stdio.h>
#include "fornecidas.h"
#include "registro.h"
int main(){
    int escolha;
    scanf("%d", &escolha);

    char nomeArquivoEntrada[30];
    scanf("%s", nomeArquivoEntrada);

    //as FUNCs vão abrir os arquivos dentro delas mesmas
    switch (escolha)
    {
        case 1: //CREATE TABLE: Cria um arquivo.bin (a "TABLE") baseado em um arquivo.csv
            char nomeArquivoSaida[30];
            scanf("%s", nomeArquivoSaida);

            FUNC1(nomeArquivoEntrada, nomeArquivoSaida);

            
            break;

        case 2: //SELECT FROM: Printa todos os registros de um arquivo.bin
            FUNC2(nomeArquivoEntrada);
            break;

        case 3: //SELECT FROM WHERE: Printa apenas registros que contém campos especificados no input
            FUNC3(nomeArquivoEntrada);
            break;

        case 4: //Acesso por RRN: Printa um (ou zero) registro com determinado RRN
            FUNC4(nomeArquivoEntrada);
            break;

        case 5: //DELETE: Remoção lógica de registros com abordagem dinâmica
            FUNC5(nomeArquivoEntrada);

            BinarioNaTela(nomeArquivoEntrada);
            break;

        case 6: //INSERT INTO: inserção de n registros com abordagem dinâmica
         //   FUNC6(nomeArquivoEntrada);

            BinarioNaTela(nomeArquivoEntrada);
            break;

        case 7: //UPDATE: ao invés de inserir, substitui os valores baseado em um filtro
            FUNC7(nomeArquivoEntrada);

            BinarioNaTela(nomeArquivoEntrada);
            break;

        default:
            break;
    }
}