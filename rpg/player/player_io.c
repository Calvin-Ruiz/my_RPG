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

void save_player(player_t *self, data_storage_t *datas)
{
    player_save_t save = (player_save_t) {self->health, self->speed,
        self->pos.v1, self->hp, self->max_hp, self->atk, self->def,
        self->money, self->xp, self->xp_next, self->level};
    int fd = open(tmpcat(datas->path, "player.dat"), O_WRONLY | O_CREAT, 0666);
    int tmp = 0;

    write(fd, (char *) &save, sizeof(save));
    for (capacity_t *temp = self->capacity; temp; temp = temp->next)
        tmp++;
    write(fd, &tmp, 2);
    for (capacity_t *temp = self->capacity; temp; temp = temp->next)
        write(fd, &temp->id, sizeof(short));
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
    self->max_hp = save.max_hp;
    self->atk = save.atk;
    self->def = save.def;
    self->money = save.money;
    self->xp = save.xp;
    self->xp_next = save.xp_next;
    self->level = save.level;
    load_player_capacities(self, datas, fd);
}
