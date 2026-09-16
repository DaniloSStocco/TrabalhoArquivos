# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Diretórios
SRC_DIR = source
LIB_DIR = library
INC_DIR = include

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Nome do executável final
TARGET = programa

all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regra generica para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compila e executa o programa
run: all
	./$(TARGET)

# Limpa executável e arquivos objeto
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean