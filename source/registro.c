#include "registro.h"

//saves e loads
int lerRegistro(Registro *reg, FILE *arquivoBin)
{
    if(!fread(reg->removido, sizeof(char), 1, arquivoBin)){
        return 0;
    }
    fread(reg->tamanhoPilha, sizeof(int), 1, arquivoBin);
    fread(reg->idPoPs, sizeof(int), 1, arquivoBin);
    fread(reg->idPoPsConectado, sizeof(int), 1, arquivoBin);
    fread(reg->velocidade, sizeof(int), 1, arquivoBin);
    fread(reg->unidadeMedida, sizeof(char), 1, arquivoBin);
    return 1;
}

void escreverRegistro(Registro *reg, FILE *arquivoBin)
{
    fwrite(reg->removido, sizeof(char), 1, arquivoBin);
    fwrite(reg->tamanhoPilha, sizeof(int), 1, arquivoBin);
    fwrite(reg->idPoPs, sizeof(int), 1, arquivoBin);
    fwrite(reg->idPoPsConectado, sizeof(int), 1, arquivoBin);
    fwrite(reg->velocidade, sizeof(int), 1, arquivoBin);
    fwrite(reg->unidadeMedida, sizeof(char), 1, arquivoBin);
}


void lerCabecalho(Cabecalho *cab, FILE *arquivoBin)
{
    fread(cab->status, sizeof(char), 1, arquivoBin);
    fread(cab->topoPilha, sizeof(int), 1, arquivoBin);
    fread(cab->proxRRN, sizeof(int), 1, arquivoBin);
    fread(cab->topoPilha, sizeof(int), 1, arquivoBin);
    fread(cab->topoPilha, sizeof(int), 1, arquivoBin);
}

void escreverCabecalho(Cabecalho *cab, FILE *arquivoBin)
{
    fread(cab->status, sizeof(char), 1, arquivoBin);
    fread(cab->topoPilha, sizeof(int), 1, arquivoBin);
    fread(cab->proxRRN, sizeof(int), 1, arquivoBin);
    fread(cab->topoPilha, sizeof(int), 1, arquivoBin);
    fread(cab->topoPilha, sizeof(int), 1, arquivoBin);
}

void imprimirRegistro(Registro reg){
    if(reg.removido == 0){
        printf("%d %d ", reg.idPoPs, reg.idPoPsConectado); //Não podem ser nulos
        if(reg.velocidade == -1){
            printf("NULO ");
        }else{
            printf("%d", reg.idPoPs);
        }
        if(reg.unidadeMedida == -1){
            printf("NULO\n");
        }else{
            printf("%c\n", reg.unidadeMedida);
        }
    }
}

FUNC1(){
    printf("PORMO GAY \n VOCÊ EST   ")
}

FUNC2(char *arquivoBin){
    Cabecalho cab;
    lerCabecalho(&cab, arquivoBin);

    Registro reg;
    while(lerRegistro(&reg, arquivoBin)){
        imprimirRegistro(reg);
    }
}

FUNC3(){

}