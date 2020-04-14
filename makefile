.PHONY: clean all run check rebuild
FLAGS := -std=c99
FLAG := -std=c11
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./build
OBJ_TEST_DIR := ./build/test
TEST_DIR := ./test
all: $(BIN_DIR)/documentary $(BIN_DIR)/testing

$(BIN_DIR)/documentary:  $(OBJ_DIR)/main.o  $(OBJ_DIR)/documentary.o  $(OBJ_DIR)/handler.o
	gcc -Wall -Wextra  $(OBJ_DIR)/main.o  $(OBJ_DIR)/documentary.o  $(OBJ_DIR)/handler.o -o $(BIN_DIR)/documentary  $(FLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/main.c -o  $(OBJ_DIR)/main.o $(FLAGS)

$(OBJ_DIR)/documentary.o: $(SRC_DIR)/documentary.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/documentary.c -o  $(OBJ_DIR)/documentary.o  $(FLAGS)

$(OBJ_DIR)/handler.o: $(SRC_DIR)/handler.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/handler.c -o  $(OBJ_DIR)/handler.o $(FLAGS)

$(BIN_DIR)/testing: $(OBJ_TEST_DIR)/main.o $(OBJ_TEST_DIR)/handler_test.o $(OBJ_TEST_DIR)/documentary_test.o $(OBJ_DIR)/documentary.o $(OBJ_DIR)/handler.o
	gcc   $(OBJ_TEST_DIR)/main.o  $(OBJ_TEST_DIR)/documentary_test.o  $(OBJ_TEST_DIR)/handler_test.o $(OBJ_DIR)/documentary.o $(OBJ_DIR)/handler.o -o $(BIN_DIR)/testing  $(FLAG)

$(OBJ_TEST_DIR)/main.o: $(TEST_DIR)/main.c
	gcc -I thirdparty -I src -c $(TEST_DIR)/main.c -o  $(OBJ_TEST_DIR)/main.o $(FLAG)

$(OBJ_TEST_DIR)/documentary_test.o: $(TEST_DIR)/documentary_test.c
	gcc -I thirdparty -I src -c $(TEST_DIR)/documentary_test.c -o  $(OBJ_TEST_DIR)/documentary_test.o  $(FLAG)

$(OBJ_TEST_DIR)/handler_test.o: $(TEST_DIR)/handler_test.c
	gcc -I thirdparty -I src -c $(TEST_DIR)/handler_test.c -o  $(OBJ_TEST_DIR)/handler_test.o $(FLAG)

clean:
	rm $(OBJ_DIR)/*.o	
	rm $(OBJ_TEST_DIR)/*.o	
	rm $(BIN_DIR)/documentary
	rm $(BIN_DIR)/testing

run:
	$(BIN_DIR)/documentary

check: 
	$(BIN_DIR)/testing

rebuild:clean all
