##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -rf

NAME	=	../lib_arcade_sfml.so

SRC	=	SFML.cpp					\
		SFMLSprite.cpp				\
		../../core/src/Assets.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror

CPPFLAGS	=	-I../ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -shared -fpic -o $(NAME)  $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c -fpic $(CXXFLAGS) $(CPPFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean $(NAME)
