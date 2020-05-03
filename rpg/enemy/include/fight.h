/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** fight.h
*/

#ifndef FIGHT_H_
#define FIGHT_H_

typedef struct fighting {
    sfSprite *player_sprite;
    player_t *player;
    enemy_t enemy;
    menu_t *menu;
    char turn;
    char is_alive;
} fighting_t;

void engage_fight(enemy_t *enemy, menu_t *menu);
void engage_fight_event(event_t *self, player_t *player);
void player_atk_sprite(player_t *player, enemy_t *enemy,
    sprite_anim_t *animation, fighting_t *fight);
void enemy_atk_sprite(enemy_t *enemy, player_t *player,
    sprite_anim_t *animation, fighting_t *fight);
char on_clic_fight_item(dynamic_list_t *self, sfVector2f *pos);
void use_item_for_me(enemy_t *enemy, player_t *player,
    sprite_anim_t *animation, fighting_t *fight);
void use_item_for_you(enemy_t *enemy, player_t *player,
    sprite_anim_t *animation, fighting_t *fight);

static inline void draw_scene(fighting_t *fight)
{
    sfRenderWindow * const window = fight->menu->window;

    sfRenderWindow_drawSprite(window, fight->menu->background, NULL);
    sfRenderWindow_drawSprite(window, fight->player_sprite, NULL);
    sfRenderWindow_drawSprite(window, fight->enemy.sprite, NULL);
    sfSleep((sfTime) {25000});
}

static inline void enemy_atk(fighting_t *fight)
{
    capacity_t *capacity = fight->enemy.capacity;
    register char c = rand() % fight->enemy.nb_capacity;

    while (c--)
        capacity = capacity->next;
    capacity->effect(&fight->enemy, fight->player, capacity->animation, fight);
}

#ifdef ITEM_LIST_H_
    static inline void consume_item_from_fight(sitem_t *item, void *target)
    {
        if (item->amount <= 0)
            return;
        if (target == get_data_storage()->player) {
            if (item->item->type != EFFECT)
                return;
            --item->amount;
            item->item->action(item->item, target);
            ((menu_t *) get_from_rec_dict(get_from_rec_dict(
                get_executor()->var, "menu"), "fight_inv"))->opened = 0;
        } else {
            if (item->item->type != FIGHT_ONLY)
                return;
            --item->amount;
            item->item->action(item->item, target);
            ((menu_t *) get_from_rec_dict(get_from_rec_dict(
                get_executor()->var, "menu"), "fight_inv"))->opened = 0;
        }
    }
#endif

#endif /* FIGHT_H_ */
