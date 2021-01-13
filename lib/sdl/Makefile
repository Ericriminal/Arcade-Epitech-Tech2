##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -rf

NAME	=	../lib_arcade_sdl.so

SRC	=	SDLArcade.cpp				\
		SDLSprite.cpp				\
		../../core/src/Assets.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror

CPPFLAGS	=	-I../ -lSDL2 -lSDL2_image -lSDL2_ttf

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -shared -fpic -o $(NAME) $(CXXFLAGS) $(CPPFLAGS)

%.o: %.cpp
	$(CXX) -c -fpic $(CXXFLAGS) $(CPPFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean $(NAME)
