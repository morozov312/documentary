.PHONY: clean all run check rebuild html_clean
FLAGS := -std=c99 -D_BSD_SOURCE
FLAG := -std=c11
SRC_DIR := ./src
BIN_DIR := ./bin
OBJ_DIR := ./build
OBJ_TEST_DIR := ./build/test
TEST_DIR := ./test
all: $(BIN_DIR)/documentary $(BIN_DIR)/testing

$(BIN_DIR)/documentary:  $(OBJ_DIR)/main.o  $(OBJ_DIR)/utilities.o  $(OBJ_DIR)/comments_check.o $(OBJ_DIR)/comments_delete.o $(OBJ_DIR)/advanced_check.o $(OBJ_DIR)/advanced_handle.o $(OBJ_DIR)/processing.o
	gcc -Wall -Wextra  $(OBJ_DIR)/main.o  $(OBJ_DIR)/utilities.o  $(OBJ_DIR)/comments_check.o $(OBJ_DIR)/comments_delete.o $(OBJ_DIR)/advanced_check.o $(OBJ_DIR)/advanced_handle.o $(OBJ_DIR)/processing.o -o $(BIN_DIR)/documentary  $(FLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/main.c -o  $(OBJ_DIR)/main.o $(FLAGS)

$(OBJ_DIR)/utilities.o: $(SRC_DIR)/utilities.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/utilities.c -o  $(OBJ_DIR)/utilities.o  $(FLAGS)

$(OBJ_DIR)/comments_check.o: $(SRC_DIR)/comments_check.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/comments_check.c -o  $(OBJ_DIR)/comments_check.o  $(FLAGS)

$(OBJ_DIR)/comments_delete.o: $(SRC_DIR)/comments_delete.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/comments_delete.c -o  $(OBJ_DIR)/comments_delete.o  $(FLAGS)

$(OBJ_DIR)/advanced_check.o: $(SRC_DIR)/advanced_check.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/advanced_check.c -o  $(OBJ_DIR)/advanced_check.o  $(FLAGS)

$(OBJ_DIR)/advanced_handle.o: $(SRC_DIR)/advanced_handle.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/advanced_handle.c -o  $(OBJ_DIR)/advanced_handle.o  $(FLAGS)

$(OBJ_DIR)/processing.o: $(SRC_DIR)/processing.c
	gcc -Wall -Wextra -c  $(SRC_DIR)/processing.c -o  $(OBJ_DIR)/processing.o  $(FLAGS)

$(BIN_DIR)/testing: $(OBJ_TEST_DIR)/main.o $(OBJ_TEST_DIR)/utilities_test.o $(OBJ_TEST_DIR)/comments_check_test.o $(OBJ_TEST_DIR)/comments_delete_test.o $(OBJ_TEST_DIR)/advanced_check_test.o $(OBJ_TEST_DIR)/advanced_handle_test.o $(OBJ_TEST_DIR)/processing_test.o $(OBJ_DIR)/utilities.o $(OBJ_DIR)/comments_check.o $(OBJ_DIR)/comments_delete.o $(OBJ_DIR)/advanced_check.o $(OBJ_DIR)/advanced_handle.o $(OBJ_DIR)/processing.o
	gcc $(OBJ_TEST_DIR)/main.o $(OBJ_TEST_DIR)/utilities_test.o $(OBJ_TEST_DIR)/comments_check_test.o $(OBJ_TEST_DIR)/comments_delete_test.o $(OBJ_TEST_DIR)/advanced_check_test.o $(OBJ_TEST_DIR)/advanced_handle_test.o $(OBJ_TEST_DIR)/processing_test.o $(OBJ_DIR)/utilities.o $(OBJ_DIR)/comments_check.o $(OBJ_DIR)/comments_delete.o $(OBJ_DIR)/advanced_check.o $(OBJ_DIR)/advanced_handle.o $(OBJ_DIR)/processing.o -o $(BIN_DIR)/testing  $(FLAG)

$(OBJ_TEST_DIR)/main.o: $(TEST_DIR)/main.c
	gcc -I thirdparty -I src -c $(TEST_DIR)/main.c -o  $(OBJ_TEST_DIR)/main.o $(FLAG)

$(OBJ_TEST_DIR)/utilities_test.o: $(TEST_DIR)/utilities_test.c
	gcc -Wall -Wextra -I thirdparty -I src -c  $(TEST_DIR)/utilities_test.c -o  $(OBJ_TEST_DIR)/utilities_test.o  $(FLAG)

$(OBJ_TEST_DIR)/comments_check_test.o: $(TEST_DIR)/comments_check_test.c
	gcc -Wall -Wextra -I thirdparty -I src -c  $(TEST_DIR)/comments_check_test.c -o  $(OBJ_TEST_DIR)/comments_check_test.o  $(FLAG)

$(OBJ_TEST_DIR)/comments_delete_test.o: $(TEST_DIR)/comments_delete_test.c
	gcc -Wall -Wextra -I thirdparty -I src -c  $(TEST_DIR)/comments_delete_test.c -o  $(OBJ_TEST_DIR)/comments_delete_test.o  $(FLAG)

$(OBJ_TEST_DIR)/advanced_check_test.o: $(TEST_DIR)/advanced_check_test.c
	gcc -Wall -Wextra -I thirdparty -I src -c  $(TEST_DIR)/advanced_check_test.c -o  $(OBJ_TEST_DIR)/advanced_check_test.o  $(FLAG)

$(OBJ_TEST_DIR)/advanced_handle_test.o: $(TEST_DIR)/advanced_handle_test.c
	gcc -Wall -Wextra -I thirdparty -I src -c  $(TEST_DIR)/advanced_handle_test.c -o  $(OBJ_TEST_DIR)/advanced_handle_test.o  $(FLAG)

$(OBJ_TEST_DIR)/processing_test.o: $(TEST_DIR)/processing_test.c
	gcc -Wall -Wextra -I thirdparty -I src -c  $(TEST_DIR)/processing_test.c -o  $(OBJ_TEST_DIR)/processing_test.o  $(FLAG)

clean:
	rm $(OBJ_DIR)/*.o	
	rm $(OBJ_TEST_DIR)/*.o	
	rm $(BIN_DIR)/documentary
	rm $(BIN_DIR)/testing
clean_html:
	rm ./docs/*.html
run:
	$(BIN_DIR)/documentary -inpdir ./src

check: 
	$(BIN_DIR)/testing

rebuild:clean all
