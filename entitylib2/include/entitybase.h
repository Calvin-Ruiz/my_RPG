/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** entitybase.h
*/

#ifndef ENTITYBASE_H_
#define ENTITYBASE_H_

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned char uchar_t;
typedef unsigned short int ushort_t;
typedef unsigned int uint_t;
typedef unsigned long int ulong_t;

typedef struct pos {
    sfVector2f v1;
    sfVector2f v2;
} pos_t;

typedef struct entity {
    sfSprite **sprite;
    uint_t *size;
    int health;
    int max_health;
    int armor;
    long long timer;
    long long frame_delay;
    uchar_t frame_dec;
    uchar_t frame;
    pos_t pos;
    void (*pre_draw)();
    void (*update)();
    void (*on_select)();
    void *(*new)();
    void (*destroy)();
    void *(*load)();
    void (*save)();
    struct entity *next;
} entity_t;

typedef struct entitylist {
    sfClock *clock;
    sfInt64 last;
    entity_t *next;
} entitylist_t;

#endif /* ENTITYBASE_H_ */
