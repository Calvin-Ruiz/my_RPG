##
## EPITECH PROJECT, 2019
## MUL_my_rpg_2019
## File description:
## Makefile
##

NAME = 

FILES = main.c \
	tools/dict.c \
	tools/get_next_line.c \
	tools/my_read.c \
	tools/tools.c

FLAGS =  -I include

all:	$(NAME)

$(NAME):
	gcc -o $(NAME) $(FILES) $(FLAGS)

fast:
	gcc -Ofast -o $(NAME) $(FILES) $(FLAGS)

clean:
	rm -f *.o
	rm -f *# *~ ./*/*# ./*/*~ ./*/*/*# ./*/*/*~ vgcore*

fclean:	clean
	rm -f $(NAME)

re:	fclean all

prepush:	fclean
	git add --all
	git status

tree:	prepush
	tree -a -I .git

push:	prepush
	git commit -m 'auto-sync with master'
	git push origin master

pull:
	git pull origin master

sync:	pull	push

debug:
	clear
	gcc -g3 -o $(NAME) $(FILES) -Wall -Wextra $(FLAGS)

valgrind:
	clear
	gcc -g3 -o $(NAME) $(FILES) $(FLAGS)

update:
	mmkfile $(NAME) "$(FLAGS)"
