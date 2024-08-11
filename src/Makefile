CC := g++
CFLAGS := -Wall -Wextra -Werror -std=c++17 -Wpedantic
GCOV_FLAGS := -fprofile-arcs -ftest-coverage

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	LIB_FLAGS := $(shell pkg-config --static --cflags --libs check ncurses)
else
	LIB_FLAGS := $(shell pkg-config --static --cflags --libs check ncursesw)
endif

PROJECT := main_cli
GUI_CLI := gui/cli/cli.cpp
BUILD_DIR := build
DOCS_DIR := docs
TESTS_DIR := tests
REPORT_DIR := report
DIST_DIR := dist

all : install

install : tetris.a snake.a | build_dir
	# doxygen
	$(CC) $(CFLAGS) $(PROJECT).cpp controller/controller.cpp $(GUI_CLI) $(BUILD_DIR)/tetris.a -o $(BUILD_DIR)/tetris_cli $(LIB_FLAGS) -DTETRIS=1
	$(CC) $(CFLAGS) $(PROJECT).cpp controller/controller.cpp $(GUI_CLI) $(BUILD_DIR)/snake.a -o $(BUILD_DIR)/snake_cli $(LIB_FLAGS) -DSNAKE=1
	rm -rf $(BUILD_DIR)/tetris.a
	rm -rf $(BUILD_DIR)/snake.a

install-sanitized : tetris.a
	$(CC) $(CFLAGS) $(PROJECT).c $(GUI) $(BUILD_DIR)/tetris.a -o $(BUILD_DIR)/$(PROJECT) $(LIB_FLAGS) -fsanitize=address

tetris.a : build_dir
	$(CC) $(CFLAGS) -c brick_game/tetris/tetris.c -o $(BUILD_DIR)/tetris.o
	ar rc $(BUILD_DIR)/tetris.a $(BUILD_DIR)/tetris.o
	ranlib $(BUILD_DIR)/tetris.a
	rm -rf $(BUILD_DIR)/tetris.o

snake.a : build_dir
	$(CC) $(CFLAGS) -c brick_game/snake/snake.cpp -o $(BUILD_DIR)/snake.o
	ar rc $(BUILD_DIR)/snake.a $(BUILD_DIR)/snake.o
	ranlib $(BUILD_DIR)/snake.a
	rm -rf $(BUILD_DIR)/snake.o

uninstall :
	rm -rf $(DOCS_DIR) $(BUILD_DIR)

rebuild : uninstall install


clean :
	rm -rf $(DOCS_DIR) $(BUILD_DIR) $(DIST_DIR) $(REPORT_DIR) $(TESTS_DIR)/tetris_test

dvi :
	cd docs/latex && make all

dist : dist_dir
	tar cf $(DIST_DIR)/tetris-1.0.tar $(BUILD_DIR) $(DOCS_DIR)

test :
	$(CC) $(CFLAGS) $(TESTS_DIR)/tetris_cli_test.c brick_game/tetris/tetris_test.c $(BUILD_DIR)/tetris.a -o $(TESTS_DIR)/tetris_test $(LIB_FLAGS)
	./$(TESTS_DIR)/tetris_test

leaks :
	leaks -atExit -- ./$(TESTS_DIR)/tetris_cli

gcov_report :
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c brick_game/tetris/tetris.c -o $(BUILD_DIR)/tetris.o $(LIB_FLAGS)
	ar rc $(BUILD_DIR)/tetris.a $(BUILD_DIR)/tetris.o
	ranlib $(BUILD_DIR)/tetris.a
	rm -rf $(BUILD_DIR)/tetris.o
	$(CC) $(CFLAGS) $(TESTS_DIR)/tetris_cli_test.c brick_game/tetris/tetris_test.c $(BUILD_DIR)/tetris.a -o $(TESTS_DIR)/tetris_test $(LIB_FLAGS) -lgcov
	./$(TESTS_DIR)/tetris_test
	rm -rf $(REPORT_DIR)
	mkdir $(REPORT_DIR)
	gcovr --html-details $(REPORT_DIR)/coverage.html
	rm -rf *.gcda *.gcno *.o
	open $(REPORT_DIR)/coverage.html

format :
	clang-format --style=file:"../materials/linters/.clang-format" -i *.c $(TESTS_DIR)/*.c $(TESTS_DIR)/*.h */*/*.c */*/*.h

check :
	clang-format --style=file:"../materials/linters/.clang-format" -n *.c */*.c */*.h */*/*.c */*/*.h

valgrind-test :
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --track-origins=yes $(TESTS_DIR)/tetris_test

build_dir :
	mkdir -p $(BUILD_DIR)

dist_dir :
	mkdir -p $(DIST_DIR)