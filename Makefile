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
		$(SRCDIR)core/LibLoader.cpp	\

NCURSES_SRC = \
		$(SRCDIR)libs/display/Ncurses/Ncurses.cpp	\

SFML_SRC = \
		$(SRCDIR)libs/display/SFML/libSFML.cpp	\

SDL_SRC = \
		$(SRCDIR)libs/display/SDL/SDL.cpp	\
		$(SRCDIR)libs/display/SDL/libSDL.cpp	\

MENU_SRC = \
		$(SRCDIR)libs/game/Menu/Menu.cpp	\
		$(SRCDIR)core/LibLoader.cpp	\

MINESWEEPER_SRC = \
		$(SRCDIR)libs/game/MineSweeper/Minesweeper.cpp

SNAKE_SRC = \
		$(SRCDIR)libs/game/Snake/Snake.cpp	\


TESTS_SRC = \


# Headers folder
INCLUDES = -I./src/interfaces	\
			-I./src/libs/game/interfaces	\
			-I./src/core	\
			-I./src/libs/display/interfaces

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
ROOT_LIBS = ./lib/
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
	$(CC) -o $(NCURSES_NAME) $^ $(LDFLAGS) -lncursesw
	mv $(NCURSES_NAME) $(ROOT_LIBS)

sdl: $(SDL_OBJ)
	$(CC) -o $(SDL_NAME) $^ $(LDFLAGS) -l SDL2 -l SDL2_ttf \
		-l SDL2_image
	mv $(SDL_NAME) $(ROOT_LIBS)

sfml: $(SFML_OBJ)
	$(CC) -o $(SFML_NAME) $^ $(LDFLAGS) -l sfml-graphics	\
		-l sfml-system -l sfml-audio
	mv $(SFML_NAME) $(ROOT_LIBS)

display: ncurses sdl sfml


menu: $(MENU_OBJ)
	$(CC) -o $(MENU_NAME) $^ $(LDFLAGS)
	mv $(MENU_NAME) $(ROOT_LIBS)

snake: $(SNAKE_OBJ)
	$(CC) -o $(SNAKE_NAME) $^ $(LDFLAGS)
	mv $(SNAKE_NAME) $(ROOT_LIBS)

minesweeper: $(MINESWEEPER_OBJ)
	$(CC) -o $(MINESWEEPER_NAME) $^ $(LDFLAGS)
	mv $(MINESWEEPER_NAME) $(ROOT_LIBS)

games: menu snake minesweeper


core: $(CORE_OBJ) $(MAIN:.cpp=.o)
	$(CC) -o $(NAME) $(CORE_OBJ) $(MAIN:.cpp=.o) $(FLAGS)

$(NAME): core games display

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
	rm -f $(ROOT_LIBS)$(NCURSES_NAME)
	rm -f $(ROOT_LIBS)$(SDL_NAME)
	rm -f $(ROOT_LIBS)$(SFML_NAME)
	rm -f $(ROOT_LIBS)$(MENU_NAME)
	rm -f $(ROOT_LIBS)$(MINESWEEPER_NAME)
	rm -f $(ROOT_LIBS)$(SNAKE_NAME)
	rm -f $(ROOT_LIBS)$(TESTS_NAME)

re: fclean all

re_clean: fclean all clean

unit_tests: $(OBJ) $(TESTS_SRC:.cpp=.o)
	$(CC) -o $(TESTS_NAME) $(OBJ) $(TESTS_SRC:.cpp=.o) $(UNIT_FLAGS)

tests_run: unit_tests
	./$(TESTS_NAME) --verbose

gcovr: tests_run
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric branch

.PHONY: all clean libclean \
	fclean re remake \
	core games display \
	menu snake minesweeper \
	tests_run unit_tests gcovr
