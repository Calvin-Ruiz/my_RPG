/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** player.c
*/

#include <entity.h>
#include <data_storage.h>
#include <tools.h>
#include <player.h>

void create_player_cmd(char **arr)
{
    player_t *player = malloc(sizeof(player_t));
    data_storage_t *datas = get_data_storage();

    arr = create_entity_base((entity_t *) player, &datas->entities, arr);
    if (arr == NULL) {
        my_puterr("\e[91mFatal : Faild to create player\n\e[0m");
        return;
    }
    datas->player = player;
    player->disp_next = datas->entitylists[0]->next;
    datas->entitylists[0]->next = (entity_t *) player;
}

void update_player(player_t *self, u_int frame_dec, my_keys_t *keys)
{
    const char coef = (keys->left || keys->right) && (keys->up || keys->down);
    if (keys->right) {
        self->pos.v1.x += coef ? self->speed * 0.7 : self->speed;
        self->pos.v2.x = self->pos.v1.x + self->size[0];
    } else if (keys->left) {
        self->pos.v1.x -= coef ? self->speed * 0.7 : self->speed;
        self->pos.v2.x = self->pos.v1.x + self->size[0];
    }
    if (keys->down) {
        self->pos.v1.y += coef ? self->speed * 0.7 : self->speed;
        self->pos.v2.y = self->pos.v1.y + self->size[1];
    } else if (keys->up) {
        self->pos.v1.y -= coef ? self->speed * 0.7 : self->speed;
        self->pos.v2.y = self->pos.v1.y + self->size[1];
    }
    self->timer += frame_dec;
    if (self->timer > self->frame_delay) {
        self->timer -= self->frame_delay;
        self->frame = (self->frame + 1) % self->size[2];
    }
}

void update_player_attributes(data_storage_t *datas)
{
    datas->player->update(datas->player, (u_int) 25000, &datas->key);
    datas->pos.x = datas->player->pos.v1.x + (*datas->player->size >> 1);
    datas->pos.y = datas->player->pos.v1.y + (datas->player->size[1] >> 1);
    sfView_setCenter(datas->view, datas->pos);
    sfRenderWindow_setView(datas->window, datas->view);
}
