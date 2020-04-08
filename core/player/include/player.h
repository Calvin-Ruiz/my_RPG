/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** player.h
*/

#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct inventory {

} inventory_t;

typedef struct player {
    struct entity *next;
    struct entity *prev;
    struct entity *disp_next;
    ushort_t id;
    sfSprite **sprite;
    ushort_t *size;
    int health;
    int max_health;
    int armor;
    long long timer;
    long long frame_delay;
    uchar_t frame_dec;
    uchar_t frame;
    pos_t pos;
    void (*update)();
    void *(*new)();
    void (*destroy)();
    void *(*load)();
    void (*save)();
} player_t;

#endif /* PLAYER_H_ */
