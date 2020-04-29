/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** player.h
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include <capacity.h>

enum {
    EQUIPMENT,
    MAP_ONLY,
    EFFECT,
    FIGHT_ONLY,
    QUEST_ITEM,
    BASIC_ITEM,
};

typedef struct item {
    struct item *next;
    short id;
    char type;
    char *name;
    int cost;
    sfSprite *icon;
    void (*action)();
} item_t;

typedef struct stored_item {
    struct stored_item *next;
    item_t *item;
    short amount;
} sitem_t;

typedef struct inventory {
    sitem_t *next;
    short inventory_id;
} inventory_t;

typedef struct effect {
    struct effect *next;
    short id;
    char duration;
    sfSprite *icon;
    void (*apply)();
    void (*active)();
    void (*remove)();
} effect_t;

typedef struct player {
    struct entity *next;
    struct entity *prev;
    struct entity *disp_next;
    sfSprite **sprite;
    ushort_t *size;
    long long timer;
    long long frame_delay;
    uchar_t frame;
    uchar_t frame_dec;
    ushort_t id;
    int health;
    float speed;
    pos_t pos;
    void (*update)(struct player *self, u_int frame_dec, void *keys);
    void *(*new)();
    void (*destroy)(struct player *self);
    void *(*load)();
    void (*save)();
    inventory_t *inventory;
    capacity_t *capacity;
    int hp;
    int max_hp;
    int atk;
    int def;
    int money;
    int xp;
    int xp_next;
    int level;
} player_t;

typedef struct psave {
    int health;
    float speed;
    sfVector2f pos;
    int hp;
    int max_hp;
    int atk;
    int def;
    int money;
    int xp;
    int xp_next;
    int level;
} player_save_t;

static inline void give_xp(player_t *player, int xp)
{
    player->xp += xp;
    if (player->xp >= player->xp_next) {
        player->xp -= player->xp_next;
        player->xp_next *= 1.5;
        player->max_hp *= 1.3;
        player->hp = player->max_hp;
        player->atk *= 1.2;
        player->def *= 1.2;
        player->level += 1;
    }
}

void create_item_cmd(char **arr);
void create_player_cmd(char **arr);
void give_item_cmd(char **arr);

#endif /* PLAYER_H_ */
