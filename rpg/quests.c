/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** quests.c
*/

#include <main.h>
#include <dict.h>

typedef struct quest {
    char *desc;
    bool success;
} quest_t;

typedef struct req{
    int needed;
    int actual;
} req_t;

typedef struct qdict {
    struct qdict *next;
    req_t *req;
    char *name
} req_dict_t;

void create_quest_cmd(char **arr)
{
    quest_t *quest = malloc(sizeof(quest_t));
    req_t *req = NULL;
    char **arr2 = arr + 4;

    quest->id = (*(dict_t **) arr[1]) ? ((quest_t *) (*(dict_t **) arr[1])->data)->id + 1 : 0;
    quest->desc = my_strdup(arr[3]);
    for (short i = ((long) arr[-1] - 4) / 2; i-- > 0; arr2 += 2) {
        req = malloc(sizeof(req_t));
        req->needed = (long) arr[1];
        req->actual = 0;
        append_to_dict(&quest->requis, arr[0], req);
    }
    append_to_dict((dict_t **) arr[1], arr[2], quest);
}

void check_quest(char **arr)
{
    int count = 
    quest_t *quest = get_from_dict((dict_t *) arr[1], arr[2]);

    while (req != NULL) {
        if (req->actual < req->needed)
            return;
        req = req->next;
    }
    quest->success = 1;
}