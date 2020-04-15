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

#endif /* CMDS_H_ */
