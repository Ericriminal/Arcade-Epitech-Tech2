##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

all:
	make -C ./sfml
	make -C ./ncurses
	make -C ./sdl

clean:
	make clean -C ./sfml
	make clean -C ./ncurses
	make clean -C ./sdl

fclean:	clean
	make fclean -C ./sfml
	make fclean -C ./ncurses
	make fclean -C ./sdl

re:	fclean all

.PHONY:	all clean fclean
