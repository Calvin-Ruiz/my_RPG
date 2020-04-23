##
## EPITECH PROJECT, 2019
## MUL_my_rpg_2019
## File description:
## Makefile
##

NAME = my_rpg

FILES = entitylib2/data_center/data_loader.c \
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
	entitylib2/executor/dynamic_structures.c \
	entitylib2/executor/executor.c \
	entitylib2/executor/function.c \
	entitylib2/executor/inits.c \
	entitylib2/executor/structs.c \
	entitylib2/executor/trace.c \
	entitylib2/menu/button.c \
	entitylib2/menu/menu.c \
	entitylib2/menu/sub_menu.c \
	entitylib2/particle/cmds.c \
	entitylib2/particle/particle.c \
	entitylib2/sounds/sound_manager.c \
	entitylib2/tools/etools.c \
	entitylib2/tools/fast_get_next_line.c \
	entitylib2/tools/loader.c \
	rpg/cmd/inits.c \
	rpg/cmd/structs.c \
	rpg/entity_groups/decor.c \
	rpg/entity_groups/event.c \
	rpg/entity_groups/npc.c \
	rpg/entity_types/dynamic_npc.c \
	rpg/entity_types/npc_event_io.c \
	rpg/entity_types/solid_decor.c \
	rpg/entity_types/solid_event.c \
	rpg/how_to_play.c \
	rpg/main.c \
	rpg/menu.c \
	rpg/pause.c \
	rpg/player/item.c \
	rpg/player/player.c \
	tools/dict.c \
	tools/get_next_line.c \
	tools/my_read.c \
	tools/tools.c

INCLUDES = -I entitylib2/data_center/include -I entitylib2/display/include -I entitylib2/entitylist/include -I entitylib2/executor/include -I entitylib2/include -I entitylib2/menu/include -I entitylib2/particle/include -I entitylib2/sounds/include -I entitylib2/tools/include -I rpg/cmd/include -I rpg/enemy/include -I rpg/entity_groups/include -I rpg/entity_types/include -I rpg/include -I rpg/player/include -I tools/include 

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

full:	update
	make re

fulld:	update
	make debug

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
