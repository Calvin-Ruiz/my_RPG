##
## EPITECH PROJECT, 2019
## MUL_my_rpg_2019
## File description:
## Makefile
##

NAME = my_rpg

FILES = cmd/inits.c \
	cmd/structs.c \
	core/how_to_play.c \
	core/menu.c \
	core/pause.c \
	core/player/player.c \
	entitylib2/data_center/data_loader.c \
	entitylib2/data_center/data_saver.c \
	entitylib2/data_center/data_storage.c \
	entitylib2/data_center/data_storage_tools.c \
	entitylib2/data_center/internal_data.c \
	entitylib2/display/displays.c \
	entitylib2/display/entity_display.c \
	entitylib2/display/window_action.c \
	entitylib2/display/window_manager.c \
	entitylib2/entity.c \
	entitylib2/entitylist/entitylist.c \
	entitylib2/executor/access.c \
	entitylib2/executor/commands.c \
	entitylib2/executor/executor.c \
	entitylib2/executor/function.c \
	entitylib2/executor/inits.c \
	entitylib2/executor/trace.c \
	entitylib2/menu/button.c \
	entitylib2/menu/menu.c \
	entitylib2/sounds/sound_manager.c \
	entitylib2/tools/etools.c \
	entitylib2/tools/fast_get_next_line.c \
	entitylib2/tools/loader.c \
	main.c \
	tools/dict.c \
	tools/get_next_line.c \
	tools/my_read.c \
	tools/tools.c

INCLUDES = -I cmd/include -I core/include -I core/player/include -I entitylib2/data_center/include -I entitylib2/display/include -I entitylib2/entitylist/include -I entitylib2/executor/include -I entitylib2/include -I entitylib2/menu/include -I entitylib2/sounds/include -I entitylib2/tools/include -I include -I tools/include 

FLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-system

all:	$(NAME)

$(NAME):
	gcc -o $(NAME) $(FILES) $(FLAGS) $(INCLUDES)

fast:
	gcc -Ofast -o $(NAME) $(FILES) $(FLAGS) $(INCLUDES)

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
	gcc -g3 -o $(NAME) $(FILES) -Wall -Wextra $(FLAGS) $(INCLUDES)

valgrind:
	clear
	gcc -g3 -o $(NAME) $(FILES) $(FLAGS) $(INCLUDES)

update:
	mmkfile $(NAME) "$(FLAGS)"
