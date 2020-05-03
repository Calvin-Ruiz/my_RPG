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

#define NB_EQUIPMENT_TYPES 6

typedef struct item {
    struct item *next;
    short id;
    char type;
    int cost;
    char *name;
    sfSprite *icon;
    void (*action)(struct item *self, void *target);
    void *data;
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

typedef struct equipment {
    short hp;
    short atk;
    short def;
} equip_t;

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
    int base_hp;
    int base_atk;
    int base_def;
    equip_t equip[NB_EQUIPMENT_TYPES];
    char wpn;
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
    char mapname[24];
    equip_t equip[NB_EQUIPMENT_TYPES];
    char weapon_type;
} player_save_t;

static inline void calculate_final_characteristics(player_t *player)
{
    player->max_hp = player->base_hp;
    player->atk = player->base_atk;
    player->def = player->base_def;
    for (u_char i = -1; ++i < NB_EQUIPMENT_TYPES;) {
        player->max_hp += player->equip[i].hp;
        player->atk += player->equip[i].atk;
        player->def += player->equip[i].def;
    }
}

void update_capacities(void);

static inline void give_xp(player_t *player, int xp)
{
    player->xp += xp;
    while (player->xp >= player->xp_next) {
        player->xp -= player->xp_next;
        update_capacities();
        calculate_final_characteristics(player);
        player->hp = player->max_hp;
        player->level += 1;
    }
}

void create_item_cmd(char **arr);
void create_player_cmd(char **arr);
void give_item_cmd(char **arr);
void destroy_player(player_t *player);

void recover_effect(item_t *item, player_t *player);
void equip_item(item_t *item, player_t *player);

#endif /* PLAYER_H_ */
