##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -rf

NAME	=	../lib_arcade_solarfox.so

SRC	=	solarFox.cpp	\
		../../core/src/Assets.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror

CPPFLAGS	= -I../

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS) $(CPPFLAGS)

%.o: %.cpp
	$(CXX) -c -fpic $(CXXFLAGS) $(CPPFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean $(NAME)
