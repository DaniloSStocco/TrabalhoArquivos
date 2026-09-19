// Danilo Salmen Stocco - nºUSP 16861501
// Diogo Salmen Stocco - nºUSP 16906441

#include <string.h>
#include "FUNCs.h"
#include "registro.h"
#include "fornecidas.h"
#include "sep.h"

//Protótipos de funções
void acaoBusca(int opcao, Registro *reg, Cabecalho *cab, FILE* arqBin);
void buscaRegistro(FILE *arquivoBin, int opcao);

//FUNCSS
void FUNC1(char *NomeArquivoEntrada, char*NomeArquivoBin){
    FILE *arqCsv = fopen(NomeArquivoEntrada, "r");
    
    FILE *arqBin = fopen(NomeArquivoBin, "wb"); //somente escreve, cria arquivo
    
    if((arqCsv == NULL)){
        printf("Falha no processamento do arquivo.");

        if(arqBin != NULL){
            fclose(arqBin);
        }
        return;
    }

    if(arqBin == NULL){
        printf("Falha no processamento do arquivo.");

        if(arqCsv != NULL){
            fclose(arqCsv);
        }
        return;
    }
    
    Cabecalho cab;
    cab.status = '0';
    cab.topoPilha = -1;
    cab.proxRRN = 0;
    cab.nroRegRem = 0;
    cab.nroPares = 0;

    escreverCabecalho(&cab, arqBin);

    char temp[200]; //buffer pra andar no csv com tamanho seguro pra 1 linha do csv
    char *linha, *token; //token pro meu_strsep

    fgets(temp, sizeof(temp), arqCsv); //pula a primeira linha

    while(fgets(temp, sizeof(temp), arqCsv)){
        linha = temp;
        Registro reg;

        temp[strcspn(temp, "\r\n")] = 0; //transforma em nulo (codigo 0) o caractere q pula linha

        //idPoPs
        token = meu_strsep(&linha, ","); //encontra o texto entre vírgulas (garantido no csv)
        reg.idPoPs = atoi(token);

        //idConectaPoPs
        token = meu_strsep(&linha, ",");
        reg.idPoPsConectado = atoi(token);

        //velocidade
        token = meu_strsep(&linha, ",");
        reg.velocidade = atoi(token);

        //unidadeMedida
        token = meu_strsep(&linha, ",");
        reg.unidadeMedida = token[0];

        //removido
        reg.removido = '0';

        //encadeamentoPilha
        reg.encadeamentoPilha = -1;
    
        cab.proxRRN++;
        cab.nroPares++;

        escreverRegistro(&reg, arqBin);
    }
    fseek(arqBin, 0, SEEK_SET);
    cab.status = '1';
    escreverCabecalho(&cab, arqBin);

    fclose(arqCsv);
    fclose(arqBin);

    BinarioNaTela(NomeArquivoBin);
}

void FUNC2(char *NomeArquivoBin){
    FILE *arqBin = fopen(NomeArquivoBin, "rb");

    if(arqBin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    Cabecalho cab;
    lerCabecalho(&cab, arqBin);

    Registro reg;
    while(lerRegistro(&reg, arqBin)){
        if(reg.removido != '1'){
            imprimirRegistro(reg);
        }
    }

    fclose(arqBin);
}

void FUNC3(char *NomeArquivoBin){
    FILE *arqBin = fopen(NomeArquivoBin, "rb+");

    if(arqBin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    buscaRegistro(arqBin, 3);

    fclose(arqBin);
}

//SELECT WHERE RRN
void FUNC4(char *NomeArquivoBin){
    FILE *arqBin = fopen(NomeArquivoBin, "rb");

    if(arqBin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    Cabecalho cab;
    lerCabecalho(&cab, arqBin);

    int RRN;
    scanf("%d", &RRN);

    Registro reg;

    fseek(arqBin, (RRN)*TAM_REG, SEEK_CUR);

    lerRegistro(&reg, arqBin);

    if(RRN > cab.nroPares){
        printf("Registro inexistente.");
        fclose(arqBin);
        return;
    }

    if(reg.removido == '0'){
        imprimirRegistro(reg);
    }else{
        printf("Registro inexistente.");
    }

    fclose(arqBin);
}

//DELETE
void FUNC5(char *NomeArquivoBin)
{
    FILE *arqBin = fopen(NomeArquivoBin, "rb+");

    if(arqBin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    buscaRegistro(arqBin, 5);

    fclose(arqBin);
}

//INSERT
void FUNC6(char *NomeArquivoBin)
{
    FILE *arqBin = fopen(NomeArquivoBin, "rb+");

    if(arqBin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    Cabecalho cab;
    fseek(arqBin, 0, SEEK_SET);
    lerCabecalho(&cab, arqBin);

    Registro reg;

    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        //vejo o topoPilha
        //se não há removidos
        if (cab.topoPilha == -1)
        {
            fseek(arqBin, (TAM_REG * cab.proxRRN), SEEK_CUR);
            cab.proxRRN++;
        }
        else //se houver
        {
            fseek(arqBin, (TAM_REG * cab.topoPilha), SEEK_CUR);
            lerRegistro(&reg, arqBin);
            cab.nroRegRem--;
            cab.topoPilha = reg.encadeamentoPilha;

            voltaUmRegistro(arqBin);
        }

///////////////////// pegando valores de entrada
        char entrada[30];
        //valores do registrador a ser adicionado
        reg.removido = '0';
        reg.encadeamentoPilha = -1;
        scanf("%d", &reg.idPoPs);
        scanf("%d", &reg.idPoPsConectado);

        // scanf("%d", reg->velocidade);
        scanf("%s", entrada);
        if (strcmp(entrada, "NULO") == 0)
            reg.velocidade = -1;
        else
            reg.velocidade = atoi(entrada);

        // scanf("%c", reg->unidadeMedida);
        ScanQuoteString(entrada);
        if(!entrada[0]) // se não houver o primeiro char
            reg.unidadeMedida = '$';
        else
            reg.unidadeMedida = entrada[0];
/////////////////////
            //printf("Registro adicionado: (de RRN = %d)", reg.RRN);
            //imprimirRegistro(reg);
        escreverRegistro(&reg, arqBin);

        fseek(arqBin, 0, SEEK_SET);
        cab.nroPares++;
        escreverCabecalho(&cab, arqBin);
    }

    fclose(arqBin);
}

//UPDATE
void FUNC7(char *NomeArquivoBin)
{
    FILE *arqBin = fopen(NomeArquivoBin, "rb+");

    if(arqBin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    buscaRegistro(arqBin, 7);

    fclose(arqBin);
}

