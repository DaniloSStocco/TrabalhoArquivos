#include <string.h>
#include "registro.h"
#include "fornecidas.h"

typedef struct busca_par
{
    char NomeCampo[20];
    char ValorCampo[20];
} BuscaPar;

//saves e loads
int lerRegistro(Registro *reg, FILE *arquivoBin)
{
    if(!fread(&reg->removido, sizeof(char), 1, arquivoBin)){
        return 0;
    }
    fread(&reg->tamanhoPilha, sizeof(int), 1, arquivoBin);
    fread(&reg->idPoPs, sizeof(int), 1, arquivoBin);
    fread(&reg->idPoPsConectado, sizeof(int), 1, arquivoBin);
    fread(&reg->velocidade, sizeof(int), 1, arquivoBin);
    fread(&reg->unidadeMedida, sizeof(char), 1, arquivoBin);
    return 1;
}

void escreverRegistro(Registro *reg, FILE *arquivoBin)
{
    fwrite(&reg->removido, sizeof(char), 1, arquivoBin);
    fwrite(&reg->tamanhoPilha, sizeof(int), 1, arquivoBin);
    fwrite(&reg->idPoPs, sizeof(int), 1, arquivoBin);
    fwrite(&reg->idPoPsConectado, sizeof(int), 1, arquivoBin);
    fwrite(&reg->velocidade, sizeof(int), 1, arquivoBin);
    fwrite(&reg->unidadeMedida, sizeof(char), 1, arquivoBin);
}


void lerCabecalho(Cabecalho *cab, FILE *arquivoBin)
{
    fread(&cab->status, sizeof(char), 1, arquivoBin);
    fread(&cab->topoPilha, sizeof(int), 1, arquivoBin);
    fread(&cab->proxRRN, sizeof(int), 1, arquivoBin);
    fread(&cab->nroRegRem, sizeof(int), 1, arquivoBin);
    fread(&cab->nroPares, sizeof(int), 1, arquivoBin);
}

void escreverCabecalho(Cabecalho *cab, FILE *arquivoBin)
{
    fread(&cab->status, sizeof(char), 1, arquivoBin);
    fread(&cab->topoPilha, sizeof(int), 1, arquivoBin);
    fread(&cab->proxRRN, sizeof(int), 1, arquivoBin);
    fread(&cab->nroRegRem, sizeof(int), 1, arquivoBin);
    fread(&cab->nroPares, sizeof(int), 1, arquivoBin);
}

void imprimirRegistro(Registro reg){
    if(reg.removido == '0'){
        printf("%d %d ", reg.idPoPs, reg.idPoPsConectado); //Não podem ser nulos
        if(reg.velocidade == -1){
            printf("NULO ");
        }else{
            printf("%d ", reg.velocidade);
        }
        if(reg.unidadeMedida == -1){
            printf("NULO\n");
        }else{
            printf("\"%c\"\n", reg.unidadeMedida);
        }
    }
}

void acaoBusca(int opcao, Registro *reg, FILE* arqBin){
    switch (opcao)
        {
            case 3: //imprimir resultados da busca
                imprimirRegistro(*reg);
                break;
            
            case 5:
                fseek(arqBin, 0, SEEK_CUR);
            default:
                break;
        }
}

void buscaRegistro(FILE *arquivoBin, int opcao){

    int n; //numero de buscas que ocorrera
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        fseek(arquivoBin, 0, SEEK_SET);
        int m; //quantidade de pares para filtrar
        scanf("%d", &m);

        Cabecalho cab;
        lerCabecalho(&cab, arquivoBin);

        BuscaPar par[m];
        Registro reg;

        for(int j=0; j<m; j++){
            scanf("%s", par[j].NomeCampo);
            if(strcmp(par[j].NomeCampo, "unidadeMedida")==0){
                ScanQuoteString(par[j].ValorCampo);
            }else{
                scanf("%s", par[j].ValorCampo);
            }
        }

        while(lerRegistro(&reg, arquivoBin)){
            if(reg.removido == '1'){
                continue;
            }

            int controle = 0; //se 0 não bate, se 1 bate
            for(int j=0; j<m; j++){ //verifica se bate com cada par

                if((strcmp(par[j].NomeCampo, "idPoPs")==0)){
                    if((atoi(par[j].ValorCampo) == reg.idPoPs)){
                        controle = 1;
                    }else{
                        controle = 0;
                        break;
                    }
                }

                if((strcmp(par[j].NomeCampo, "idPoPsConectado")==0)){
                    if((atoi(par[j].ValorCampo) == reg.idPoPsConectado)){
                        controle = 1;
                    }else{
                        controle = 0;
                        break;
                    }
                }

                if((strcmp(par[j].NomeCampo, "velocidade")==0)){
                    if((strcmp(par[j].ValorCampo, "NULO")==0) && (reg.velocidade==-1)){
                        controle = 1;
                    }else if((atoi(par[j].ValorCampo) == reg.velocidade) ){
                        controle = 1;
                    }else{
                        controle = 0;
                        break;
                    }
                }

                if(strcmp(par[j].NomeCampo, "unidadeMedida")==0){
                    if((strcmp(par[j].ValorCampo, "NULO")==0) && (reg.unidadeMedida == -1)){
                        controle = 1;
                    }
                    else{
                        if((par[j].ValorCampo)[0] == reg.unidadeMedida){
                            controle = 1;
                        }else{
                            controle = 0; //todos os filtros devem bater
                            break;
                        }
                    }
                    
                }
            }
            if(controle){
                acaoBusca(opcao, &reg, arquivoBin);
            }
        }
        printf("\n");
    }
}

void FUNC1(char *NomeArquivoEntrada, char*NomeArquivoBin){
    FILE *arqCsv = fopen(NomeArquivoEntrada, "r");
    FILE *arqBin = fopen(NomeArquivoBin, "rb+");

    if((arqCsv == NULL)){
        printf("Falha no processamento do arquivo.");
        return;
    }
    
    

    fclose(arqCsv);
    fclose(arqBin);
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
        imprimirRegistro(reg);
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