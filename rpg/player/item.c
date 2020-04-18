/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** item.c
*/

#include <entitybase.h>
#include <player.h>

void create_item_cmd(char **arr)
{
    item_t **item = (item_t **) arr[1];
    item_t *new = malloc(sizeof(item_t));

    if (new == NULL)
        return;
    *new = (item_t) {*item, (*item) ? (*item)->id + 1 : 0, (long) arr[2],
        arr[3], (long) arr[4], sfSprite_create()};
    if (new->icon)
        sfSprite_setTexture(new->icon, (sfTexture *) arr[5], sfTrue);
    *item = new;
}
