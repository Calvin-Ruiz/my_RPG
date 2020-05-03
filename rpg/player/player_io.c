/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** player_io.c
*/

#include <entitybase.h>
#include <player.h>
#include <data_storage.h>
#include <fcntl.h>
#include <tools.h>
#include <player_io.h>
#include <string.h>

void save_player(player_t *self, data_storage_t *datas)
{
    player_save_t save = (player_save_t) {self->health, self->speed,
        self->pos.v1, self->hp, self->base_hp, self->base_atk, self->base_def,
        self->money, self->xp, self->xp_next, self->level, "", {{}}};
    int fd = open(tmpcat(datas->path, "player.dat"), O_WRONLY | O_CREAT, 0666);
    int tmp = 0;
    for (u_char i = -1; ++i < NB_EQUIPMENT_TYPES;)
        save.equip[i] = self->equip[i];
    memset(save.mapname, '\0', 24);
    for (register u_char i = 0; datas->mapname[i] != '\0' && i < 24; i++)
        save.mapname[i] = datas->mapname[i];
    write(fd, (char *) &save, sizeof(save));
    for (capacity_t *temp = self->capacity; temp; temp = temp->next)
        tmp++;
    write(fd, &tmp, 2);
    for (capacity_t *temp = self->capacity; temp; temp = temp->next)
        write(fd, &temp->id, sizeof(short));
    for (sitem_t *sitem = self->inventory->next; sitem; sitem = sitem->next) {
        write(fd, &sitem->item->id, sizeof(short));
        write(fd, &sitem->amount, sizeof(sitem->amount));
    }
}

static void load_player_capacities(player_t *player, data_storage_t *datas,
    int fd)
{
    short size = 0;
    short id = 0;
    capacity_t *capacity = NULL;

    player->capacity = NULL;
    read(fd, (char *) &size, 2);
    while (size-- > 0) {
        capacity = malloc(sizeof(capacity_t));
        if (capacity == NULL)
            continue;
        read(fd, (char *) &id, sizeof(short));
        *capacity = *get_capacity_from_id(datas->global[1], id);
        capacity->next = player->capacity;
        player->capacity = capacity;
    }
}

static void load_player_items(player_t *player, data_storage_t *datas, int fd)
{
    short id = 0;
    sitem_t *new = NULL;

    while (read(fd, &id, sizeof(short)) == sizeof(short)) {
        new = malloc(sizeof(sitem_t));
        if (new == NULL)
            continue;
        new->next = player->inventory->next;
        new->item = get_item_from_id(datas->global[0], id);
        if (read(fd, &new->amount, sizeof(new->amount)) == sizeof(new->amount)
            && new->item && new->amount > 0)
            player->inventory->next = new;
        else
            free(new);
    }
}

void load_player(player_t *self, data_storage_t *datas)
{
    player_save_t save;
    int fd = open(tmpcat(datas->path, "player.dat"), O_RDONLY);
    if (fd == -1 || read(fd, (char *) &save, sizeof(save)) != sizeof(save))
        return;
    self->health = save.health;
    self->speed = save.speed;
    self->pos.v1 = save.pos;
    self->hp = save.hp;
    self->base_hp = save.max_hp;
    self->base_atk = save.atk;
    self->base_def = save.def;
    self->money = save.money;
    self->xp = save.xp;
    self->xp_next = save.xp_next;
    self->level = save.level;
    datas->mapname = my_tmpdup(save.mapname);
    for (u_char i = -1; ++i < NB_EQUIPMENT_TYPES;)
        self->equip[i] = save.equip[i];
    load_player_capacities(self, datas, fd);
    load_player_items(self, datas, fd);
}
