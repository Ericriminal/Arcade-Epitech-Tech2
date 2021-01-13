##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

all:	graphicals games core

core:
	make -C ./core

games:
	make -C ./games

graphicals:
	make -C ./lib

clean:
	make clean -C ./core
	make clean -C ./games
	make clean -C ./lib

fclean:
	make fclean -C ./core
	make fclean -C ./games
	make fclean -C ./lib

re:	fclean all

.PHONY:	all core games graphical clean fclean re
