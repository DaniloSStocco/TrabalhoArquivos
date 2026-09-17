#include <string.h>
#include "registro.h"
#include "fornecidas.h"
#include "sep.h"

#define TAM_REG ((sizeof(int)*4) + (sizeof(char)*2)) //18
#define TAM_CAB ((sizeof(int)*4) + sizeof(char)) //17

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
    fread(&reg->encadeamentoPilha, sizeof(int), 1, arquivoBin);
    fread(&reg->idPoPs, sizeof(int), 1, arquivoBin);
    fread(&reg->idPoPsConectado, sizeof(int), 1, arquivoBin);
    fread(&reg->velocidade, sizeof(int), 1, arquivoBin);
    fread(&reg->unidadeMedida, sizeof(char), 1, arquivoBin);
    return 1;
}

void escreverRegistro(Registro *reg, FILE *arquivoBin)
{
    fwrite(&reg->removido, sizeof(char), 1, arquivoBin);
    fwrite(&reg->encadeamentoPilha, sizeof(int), 1, arquivoBin);
    fwrite(&reg->idPoPs, sizeof(int), 1, arquivoBin);
    fwrite(&reg->idPoPsConectado, sizeof(int), 1, arquivoBin);
    fwrite(&reg->velocidade, sizeof(int), 1, arquivoBin);
    fwrite(&reg->unidadeMedida, sizeof(char), 1, arquivoBin);
}

//lê o arquivo, atribui ao cabeçalho
void lerCabecalho(Cabecalho *cab, FILE *arquivoBin)
{
    fread(&cab->status, sizeof(char), 1, arquivoBin);
    fread(&cab->topoPilha, sizeof(int), 1, arquivoBin);
    fread(&cab->proxRRN, sizeof(int), 1, arquivoBin);
    fread(&cab->nroRegRem, sizeof(int), 1, arquivoBin);
    fread(&cab->nroPares, sizeof(int), 1, arquivoBin);
}

//lê o cabeçalho, atribui ao arquivo
void escreverCabecalho(Cabecalho *cab, FILE *arquivoBin)
{
    fwrite(&cab->status, sizeof(char), 1, arquivoBin);
    fwrite(&cab->topoPilha, sizeof(int), 1, arquivoBin);
    fwrite(&cab->proxRRN, sizeof(int), 1, arquivoBin);
    fwrite(&cab->nroRegRem, sizeof(int), 1, arquivoBin);
    fwrite(&cab->nroPares, sizeof(int), 1, arquivoBin);
}

void voltaUmRegistro(FILE *arquivoBin){
    fseek(arquivoBin, (-TAM_REG), SEEK_CUR);
}

void imprimirRegistro(Registro reg){
    //if(reg.removido == '0'){ //// acaoBusca já pula os removidos

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

    //}
}

void excluirRegistro(Registro *reg, Cabecalho *cab, FILE* arqBin)
{
    //volta pro começo do arquivo
    fseek(arqBin, 0, SEEK_SET);

    //altero valores do cabecalho
    int preTopo = cab->topoPilha;
    cab->topoPilha = reg->RRN;
    cab->nroRegRem += 1;

    escreverCabecalho(cab, arqBin);

    //vou até o registro q está sendo excluido
    fseek(arqBin, (reg->RRN * TAM_REG), SEEK_CUR);

    // [removido] [encadeamentoPilha] [idPoP](int) [idPoPsConectado](int) [velocidade](int) [unidadeMedida](char)

    //atributos de controle com valor
    reg->removido = '1';
    reg->encadeamentoPilha = preTopo; //eu podia colocar um if mas fica -1 anyway

    //resto com lixo
    reg->idPoPs = -1;
    reg->idPoPsConectado = -1;
    reg->velocidade = -1;
    reg->unidadeMedida = '$';

    escreverRegistro(reg, arqBin); //termina onde estava no acaoBusca
    
    return;
}

void atualizarRegistro(Registro *reg, FILE *arqBin){
    voltaUmRegistro(arqBin);

    escreverRegistro(reg, arqBin);
}

void acaoBusca(int opcao, Registro *reg, Cabecalho *cab, FILE* arqBin){
    switch (opcao)
        {
            case 3: //imprimir resultados da busca
                imprimirRegistro(*reg);
                break;
            
            case 5:
                excluirRegistro(reg, cab, arqBin);
                break;

            case 7:
                atualizarRegistro(reg, arqBin);
                break;
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

        
        int p=1; //quantidade de pares de valores novos
        if(opcao == 7){
            scanf("%d", &p);
        }
            BuscaPar novoPar[p];
           // Registro novoReg; ////////////////// <- update
        BuscaPar par[m];
        Registro reg;
        reg.RRN = -1; //começa -1 então o 1º é 0

        for(int j=0; j<m; j++){
            scanf("%s", par[j].NomeCampo);
            if(strcmp(par[j].NomeCampo, "unidadeMedida")==0){
                ScanQuoteString(par[j].ValorCampo);
            }else{
                scanf("%s", par[j].ValorCampo);
            }
        }
////////////////////////////update//////////////////////////////
            if(opcao == 7){
                for(int j=0; j<p; j++){
                    scanf("%s", novoPar[j].NomeCampo);
                    if(strcmp(novoPar[j].NomeCampo, "unidadeMedida")==0){
                        ScanQuoteString(novoPar[j].ValorCampo);
                    }else{
                        scanf("%s", novoPar[j].ValorCampo);
                    }
                }
            }
////////////////////////////////////////////////////////////////
        while(lerRegistro(&reg, arquivoBin))
        {
            reg.RRN++;

            if(reg.removido == 1)
            {
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
//////////////////////////////////////////update/////////////////////////////////////////////
                if(opcao == 7){
                    for(int k=0; k<p; k++){
                        if(strcmp(novoPar[k].NomeCampo, "idPoPs")==0){
                            reg.idPoPs = atoi(novoPar[k].ValorCampo);
                        }
                        if(strcmp(novoPar[k].NomeCampo, "idPoPsConectado")==0){
                            reg.idPoPsConectado = atoi(novoPar[k].ValorCampo);
                        }
                        if(strcmp(novoPar[k].NomeCampo, "velocidade")==0){
                            if(strcmp(novoPar[k].ValorCampo, "NULO")==0){
                                reg.velocidade = -1;
                            }
                            else{
                                reg.velocidade = atoi(novoPar[k].ValorCampo);
                            }
                        }
                        if(strcmp(novoPar[k].NomeCampo, "unidadeMedida")==0){
                            if(strcmp(novoPar[k].ValorCampo, "NULO")==0){
                                reg.unidadeMedida = '$';
                            }
                            else{
                                reg.unidadeMedida = (novoPar[k].ValorCampo)[0];
                            }
                        }
                        
                    }
                }
//////////////////////////////////////////////////////////////////////////////////////////////
            }
            if(controle){
                acaoBusca(opcao, &reg, &cab, arquivoBin);
            }
        }

        if(opcao == 3) //runcodes :C
            printf("\n");
    }
}



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

    escreverCabecalho(&cab, arqBin); //Ainda não está correto

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