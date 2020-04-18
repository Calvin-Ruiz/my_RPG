/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** player.h
*/

#ifndef PLAYER_H_
#define PLAYER_H_

enum {
    EQUIPMENT,
    MAP_ONLY,
    EFFECT,
    FIGHT_ONLY,
    QUEST_ITEM,
    BASIC_ITEM,
};

enum {
    HIMSELF,
    ENNEMY,
    ALLIES,
    ENNEMIES,
    EVERYONE,
};

typedef struct item {
    struct item *next;
    short id;
    char type;
    char *name;
    int cost;
    sfSprite *icon;
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

typedef struct capacity {
    struct capacity *next;
    short id;
    char target;
    void *animation;
    void (*effect)(void *user, void *target);
} capacity_t;

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
    int money;
    int xp;
    char level;
    int atk;
    int def;
    int hp;
    int max_hp;
} player_t;

void create_item_cmd(char **arr);
void create_player_cmd(char **arr);

#endif /* PLAYER_H_ */
