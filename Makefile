CC = gcc
CFLAGS = -Wall -Wextra -g -Werror
LDFLAGS = 

SRC_DIR = .
SERVER_DIR = server
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/web_server
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SERVER_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%.c, $(SRCS))) \
       $(patsubst $(SERVER_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter $(SERVER_DIR)/%.c, $(SRCS)))

.PHONY: all clean

all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SERVER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)