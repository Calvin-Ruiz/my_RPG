/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** item.c
*/

#include <entitybase.h>
#include <player.h>
#include <tools.h>

void create_item_cmd(char **arr)
{
    item_t **item = (item_t **) arr[1];
    item_t *new = malloc(sizeof(item_t));

    if (new == NULL)
        return;
    *new = (item_t) {*item, (*item) ? (*item)->id + 1 : 0, (long) arr[2],
        arr[3], (long) arr[4], sfSprite_create(), (void (*)()) arr[6]};
    if (new->icon)
        sfSprite_setTexture(new->icon, (sfTexture *) arr[5], sfTrue);
    *item = new;
}

void give_item(player_t *player, item_t *item, char *name)
{
    sitem_t *tmp = player->inventory->next;

    while (item && my_strcmp(item->name, name))
        item = item->next;
    if (item == NULL)
        return;
    while (tmp && tmp->item != item)
        tmp = tmp->next;
    if (tmp) {
        tmp->amount++;
        return;
    }
    tmp = malloc(sizeof(sitem_t));
    if (tmp == NULL)
        return;
    *tmp = (sitem_t) {player->inventory->next, item, 1};
    player->inventory->next = tmp;
}

void buy_item(player_t *player, item_t *item, char *name)
{
    sitem_t *tmp = player->inventory->next;

    while (item && my_strcmp(item->name, name))
        item = item->next;
    if (item == NULL)
        return;
    if (player->money < item->cost)
        return;
    player->money -= item->cost;
    while (tmp && tmp->item != item)
        tmp = tmp->next;
    if (tmp) {
        tmp->amount++;
        return;
    }
    tmp = malloc(sizeof(sitem_t));
    if (tmp == NULL)
        return;
    *tmp = (sitem_t) {player->inventory->next, item, 1};
    player->inventory->next = tmp;
}

void give_item_cmd(char **arr)
{
    give_item(*(player_t **) arr[1], (item_t *) arr[2], arr[3]);
}
