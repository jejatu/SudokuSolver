PROGRAM = sudoku
OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin
C_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_FILES))
CC = gcc
CFLAGS = -Wall

$(PROGRAM): $(OBJS)
	$(CC) -o $(BIN_DIR)/$(PROGRAM) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $(CFLAGS) $(ETC) $<
	
clean:
	rm bin/$(PROGRAM).exe
	rm obj/*.o