##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -rf

NAME	=	../arcade

SRC_FILES	=	Core.cpp	\
				Assets.cpp	\

SRC	=	$(addprefix ./src/, $(SRC_FILES))

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror

CPPFLAGS	=	-ldl -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -fpic -o $(NAME) $(OBJ) $(CXXFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean $(NAME)
