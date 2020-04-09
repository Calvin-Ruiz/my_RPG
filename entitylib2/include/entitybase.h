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
    void (*update)();
    void *(*new)();
    void (*destroy)();
    void *(*load)();
    void (*save)();
} entity_t;

typedef struct entitylist {
    entity_t *next;
    sfClock *clock;
    sfInt64 last;
    char (*collide)();
    void (*update)();
} entitylist_t;

#endif /* ENTITYBASE_H_ */
