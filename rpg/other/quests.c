/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** quests.c
*/

#include <main.h>
#include <dict.h>
#include <quest.h>
#include <player.h>

void create_quest_cmd(char **arr)
{
    quest_t *quest = malloc(sizeof(quest_t));
    req_t *req = NULL;
    char **arr2 = arr + 6;

    quest->id = (*(dict_t **) arr[1]) ? ((quest_t *) (*(dict_t **)
        arr[1])->data)->id + 1 : 0;
    quest->desc = my_strdup(arr[3]);
    quest->xp = (long) arr[4];
    quest->money = (long) arr[5];
    quest->success = 0;
    for (short i = ((long) arr[-1] - 6) / 2; i-- > 0; arr2 += 2) {
        req = malloc(sizeof(req_t));
        req->needed = (long) arr[1];
        req->actual = 0;
        append_to_dict(&quest->req, arr[0], req);
    }
    append_to_dict((dict_t **) arr[1], arr[2], quest);
}

void check_quest(char **arr)
{
    quest_t *quest = get_from_dict((dict_t *) arr[1], arr[2]);
    req_dict_t *req = (req_dict_t *) quest->req;
    player_t *player;

    while (req != NULL) {
        if (req->req->actual < req->req->needed)
            return;
        req = req->next;
    }
    if (quest->success)
        return;
    player = get_data_storage()->player;
    player->money += quest->money;
    give_xp(player, quest->xp);
    quest->success = 1;
}
