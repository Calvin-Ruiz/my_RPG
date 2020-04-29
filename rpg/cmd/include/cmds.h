/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** cmds.h
*/

#ifndef CMDS_H_
#define CMDS_H_

void create_player_cmd(char **arr);
dict_t *get_sf_colors(void);
void create_solid_decor_cmd(char **arr);
void update_player(player_t *self, u_int frame_dec, void *keys);
void create_capacity(char **arr);
void create_sprite_anim(char **arr);
void create_enemy_cmd(char **arr);
void use_capacity(void *data);
void exit_menu(menu_t *menu);
void my_said(char **arr);

#endif /* CMDS_H_ */
