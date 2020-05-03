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
#include <entity_display.h>
#include <string.h>

void create_player_cmd(char **arr)
{
    player_t *player = malloc(sizeof(player_t));
    data_storage_t *datas = get_data_storage();

    arr = create_entity_base((entity_t *) player, &datas->entities, arr);
    if (arr == NULL) {
        my_puterr("\e[91mFatal : Failed to create player\n\e[0m");
        return;
    }
    datas->player = player;
    player->inventory = malloc(sizeof(inventory_t));
    *(player->inventory) = (inventory_t) {NULL, -1};
    player->capacity = NULL;
    player->wpn = 1;
    memset(&player->equip, '\0', sizeof(equip_t) * NB_EQUIPMENT_TYPES);
}

static void move_player(player_t *self, my_keys_t *keys)
{
    const char coef = (keys->left || keys->right) && (keys->up || keys->down);

    self->frame_dec = coef ? self->size[2] * 4 : 0;
    if (keys->right) {
        self->frame_dec = 0;
        self->pos.v1.x += coef ? self->speed * 0.7 : self->speed;
    } else if (keys->left) {
        self->frame_dec = self->size[2] * 2;
        self->pos.v1.x -= coef ? self->speed * 0.7 : self->speed;
    }
    if (keys->down) {
        self->frame_dec = self->size[2];
        self->pos.v1.y += coef ? self->speed * 0.7 : self->speed;
    } else if (keys->up) {
        self->frame_dec = self->size[2] * 3;
        self->pos.v1.y -= coef ? self->speed * 0.7 : self->speed;
    }
}


void update_player(player_t *self, u_int frame_dec, my_keys_t *keys)
{
    self->sprite -= self->frame_dec;
    move_player(self, keys);
    self->sprite += self->frame_dec;
    self->pos.v2.x = self->pos.v1.x + self->size[0];
    self->pos.v2.y = self->pos.v1.y + self->size[1];
    self->timer += frame_dec;
    if (self->timer > self->frame_delay) {
        self->timer -= self->frame_delay;
        self->frame = (self->frame + 1) % self->size[2];
    }
}

void update_player_attributes(data_storage_t *datas)
{
    player_t *player = datas->player;

    conditionnal_insertion(&datas->entitylists[0]->next, (entity_t *) player);
    player->update(player, (u_int) 25000, &datas->key);
    datas->pos.x = player->pos.v1.x + (*player->size >> 1);
    datas->pos.y = player->pos.v1.y + (player->size[1] >> 1);
    sfView_setCenter(datas->view, datas->pos);
    sfRenderWindow_setView(datas->window, datas->view);
}

void destroy_player(player_t *player)
{
    sitem_t *item = player->inventory->next;
    capacity_t *cap = player->capacity;

    for (; item; item = player->inventory->next) {
        player->inventory->next = item->next;
        free(item);
    }
    free(player->inventory);
    for (; cap; cap = player->capacity) {
        player->capacity = cap->next;
        free(cap);
    }
    player->sprite -= player->frame_dec;
}
