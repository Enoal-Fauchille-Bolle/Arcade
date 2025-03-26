##
## EPITECH PROJECT, 2025
## Arcade
## File description:
## Main Makefile
##

# Executable names
NAME = arcade

NCURSES_NAME = arcade_ncurses.so

SDL_NAME = arcade_sdl2.so

SFML_NAME = arcade_sfml.so

MENU_NAME = arcade_menu.so

SNAKE_NAME = arcade_snake.so

MINESWEEPER_NAME = arcade_minesweeper.so


TESTS_NAME = unit_tests.out

# Folders name
SRCDIR = ./src/
GL = ./sources/globals/
MISC = ./sources/miscellaneous/
TESTS = ./tests/

# Sources
MAIN = $(SRCDIR)main.cpp

CORE_SRC = \
		$(SRCDIR)core/Core.cpp	\

NCURSES_SRC = \

SFML_SRC = \

SDL_SRC = \

MENU_SRC = \

MINESWEEPER_SRC = \

SNAKE_SRC = \


TESTS_SRC = \


# Headers folder
INCLUDES = -I./src/core/interfaces	\
			-I./src/core/libs/game/interfaces	\
			-I./src/core/libs/graphical/interfaces

# GCC Flags
ERROR = -Werror -Wall -Wextra -Wshadow
# Compilation Flags
CFLAGS += $(ERROR) -I$(INCLUDES) -g -std=c++20 -fPIE -fPIC -fno-gnu-unique
# Pre Compilation
CC := g++

NCURSES_OBJ = $(NCURSES_SRC:.cpp=.o)
SDL_OBJ = $(SDL_SRC:.cpp=.o)
SFML_OBJ = $(SFML_SRC:.cpp=.o)
MENU_OBJ = $(MENU_SRC:.cpp=.o)
MINESWEEPER_OBJ = $(MINESWEEPER_SRC:.cpp=.o)
SNAKE_OBJ = $(SNAKE_SRC:.cpp=.o)

DEP	=	$(CORE_SRC:.cpp=.d)	\
		$(NCURSES_SRC:.cpp=.d)	\
		$(SDL_SRC:.cpp=.d)	\
		$(SFML_SRC:.cpp=.d)	\
		$(MENU_SRC:.cpp=.d)	\
		$(MINESWEEPER_SRC:.cpp=.d)	\
		$(SNAKE_SRC:.cpp=.d)	\
		$(MAIN:.cpp=.d)

CORE_OBJ = $(CORE_SRC:.cpp=.o)

# Libraries
LIBS = ./libs/
LLIBS = -L$(LIBS)
LIB_ = #$(LIBS)put a path to a library here

# Compilation Flags
FLAGS = $(CFLAGS) $(LLIBS)
LDFLAGS = -shared -fPIC
# Test Compilation Flags
UNIT_FLAGS = $(FLAGS) -lcriterion --coverage -pie

all: $(NAME)


ncurses: $(NCURSES_OBJ)
	$(CC) -o $(NCURSES_NAME) $< $(LDFLAGS)
	mv $(NCURSES_NAME) ./lib/

sdl: $(SDL_OBJ)
	$(CC) -o $(SDL_NAME) $< $(LDFLAGS)
	mv $(SDL_NAME) ./lib/

sfml: $(SFML_OBJ)
	$(CC) -o $(SFML_NAME) $< $(LDFLAGS)
	mv $(SFML_NAME) ./lib/

graphical: ncurses sdl sfml


menu: $(MENU_OBJ)
	$(CC) -o $(MENU_NAME) $< $(LDFLAGS)
	mv $(MENU_NAME) ./lib/

snake: $(SNAKE_OBJ)
	$(CC) -o $(SNAKE_NAME) $< $(LDFLAGS)
	mv $(SNAKE_NAME) ./lib/

minesweeper: $(MINESWEEPER_OBJ)
	$(CC) -o $(MINESWEEPER_NAME) $< $(LDFLAGS)
	mv $(MINESWEEPER_NAME) ./lib/

games: menu snake minesweeper


core: $(CORE_OBJ) $(MAIN:.cpp=.o)
	$(CC) -o $(NAME) $(CORE_OBJ) $(MAIN:.cpp=.o) $(FLAGS)

$(NAME): core games graphical

$(TESTS)%.o: $(TESTS)%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

-include $(DEP)
%.o: %.cpp
	$(CC) -c $< -o $@ -MMD -MF $*.d -MT $@ $(CFLAGS)

clean:
	rm -f $(CORE_OBJ)
	rm -f $(NCURSES_OBJ)
	rm -f $(SDL_OBJ)
	rm -f $(SFML_OBJ)
	rm -f $(MENU_OBJ)
	rm -f $(MINESWEEPER_OBJ)
	rm -f $(SNAKE_OBJ)
	rm -f $(MAIN:.cpp=.o)
	rm -f $(TESTS_SRC:.cpp=.o)
	rm -f $(DEP)
	rm -f *.gcno
	rm -f *.gcda

libclean: clean

fclean: libclean
	rm -f $(NAME)
	rm -f $(NCURSES_NAME)
	rm -f $(SDL_NAME)
	rm -f $(SFML_NAME)
	rm -f $(MENU_NAME)
	rm -f $(MINESWEEPER_NAME)
	rm -f $(SNAKE_NAME)
	rm -f $(TESTS_NAME)
	find -name "lib*.a" -delete

re: fclean all

re_clean: fclean all clean

tests_run: unit_tests
	./$(TESTS_NAME) --verbose
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric branch

# unit_tests: $(OBJ) $(TESTS_SRC:.cpp=.o)
# 	$(CC) -o $(TESTS_NAME) $(OBJ) $(TESTS_SRC:.cpp=.o) $(UNIT_FLAGS)

gcovr: tests_run
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric branch

.PHONY: all clean libclean \
	fclean re remake \
	core games graphical \
	menu snake minesweeper \
	tests_run unit_tests gcovr
