import os
import struct

# Tipos de dados em C (Little-Endian padrão x86/Linux):
# c = char (1 byte)
# i = int (4 bytes com sinal)
# < = força little-endian e sem padding de alinhamento
FORMATO_CABECALHO = "<ciiii"   # 1 + 4 + 4 + 4 + 4 = 17 bytes
FORMATO_REGISTRO  = "<ciiiic"  # 1 + 4 + 4 + 4 + 4 + 1 = 18 bytes

TAM_CABECALHO = 17
TAM_REGISTRO = 18

def ler_arquivo_binario(caminho_arquivo):
    if not os.path.exists(caminho_arquivo):
        print(f"Erro: O arquivo '{caminho_arquivo}' não foi encontrado.")
        return

    tam_total = os.path.getsize(caminho_arquivo)
    
    with open(caminho_arquivo, "rb") as f:
        # 1. Leitura do Cabeçalho
        bytes_cabecalho = f.read(TAM_CABECALHO)
        if len(bytes_cabecalho) < TAM_CABECALHO:
            print("Erro: Arquivo menor que o tamanho mínimo do cabeçalho (17 bytes).")
            return

        status, topo, prox_rrn, nro_rem, nro_pares = struct.unpack(FORMATO_CABECALHO, bytes_cabecalho)
        
        # Converter char de bytes para string legível
        status_char = status.decode('latin1', errors='replace')

        print("\n" + "=" * 65)
        print("                        CABEÇALHO                        ")
        print("=" * 65)
        print(f"{'status':<8} | {'topoPilha':<10} | {'proxRRN':<8} | {'nroRegRem':<10} | {'nroPares':<10}")
        print("-" * 65)
        print(f"{repr(status_char):<8} | {topo:<10} | {prox_rrn:<8} | {nro_rem:<10} | {nro_pares:<10}")
        print("=" * 65)

        # 2. Leitura dos Registros
        print("\n" + "=" * 90)
        print("                                REGISTROS                                 ")
        print("=" * 90)
        print(f"{'RRN':<5} | {'removido':<8} | {'encadPilha':<10} | {'idPoPs':<8} | {'idPoPsCon':<10} | {'velocidade':<10} | {'unMedida':<8}")
        print("-" * 90)

        rrn = 0
        while True:
            bytes_reg = f.read(TAM_REGISTRO)
            if not bytes_reg or len(bytes_reg) < TAM_REGISTRO:
                break
            
            removido, encad, id1, id2, vel, un_medida = struct.unpack(FORMATO_REGISTRO, bytes_reg)
            
            removido_char = removido.decode('latin1', errors='replace')
            un_medida_char = un_medida.decode('latin1', errors='replace')

            # Destaque visual: marca registros removidos com '*'
            flag_removido = f"*{repr(removido_char)}" if removido_char == '1' else repr(removido_char)

            print(f"{rrn:<5} | {flag_removido:<8} | {encad:<10} | {id1:<8} | {id2:<10} | {vel:<10} | {repr(un_medida_char):<8}")
            rrn += 1

        print("=" * 90)
        print(f"Total de bytes do arquivo: {tam_total} bytes")
        print(f"Registros lidos: {rrn}\n")


if __name__ == "__main__":
    # Permite digitar o nome do arquivo na execução
    arquivo = input("Digite o nome ou caminho do arquivo binário (ex: dados.bin): ").strip()
    if arquivo:
        ler_arquivo_binario(arquivo)