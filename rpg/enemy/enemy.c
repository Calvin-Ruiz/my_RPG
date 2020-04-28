/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** enemy.c
*/
#include <entitybase.h>
#include <capacity.h>
#include <enemy.h>
#include <tools.h>

void create_enemy_cmd(char **arr)
{
    const sfVector2u size = sfTexture_getSize((sfTexture *) arr[2]);
    const u_char length = (long) arr[-1];
    capacity_t **capacity = &((enemy_t *) arr[1])->capacity;
    capacity_t *new = NULL;

    *(enemy_t *) arr[1] = (enemy_t) {sfSprite_create(), (sfVector2f)
        {size.x >> 1, size.y >> 1}, (long) arr[3], (long) arr[3], (long) arr[4],
        (long) arr[5], (long) arr[6], (long) arr[7], NULL, length - 8};
    for (register u_char i = 7; ++i < length;) {
        if (arr[i] == NULL)
            continue;
        new = my_malloc(sizeof(capacity_t));
        *new = *(capacity_t *) arr[i];
        new->next = *capacity;
        *capacity = new;
    }
    sfSprite_setTexture(((enemy_t *) arr[1])->sprite,
        (sfTexture *) arr[2], sfTrue);
    sfSprite_setPosition(((enemy_t *) arr[1])->sprite, (sfVector2f) {100, 200});
}
