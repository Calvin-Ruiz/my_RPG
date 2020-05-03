/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** quest.h
*/

#ifndef QUEST_H_
#define QUEST_H_

typedef struct quest {
    char *desc;
    short id;
    dict_t *req;
    char success;
    int xp;
    int money;
} quest_t;

typedef struct req {
    int needed;
    int actual;
} req_t;

typedef struct qdict {
    struct qdict *next;
    req_t *req;
    char *name;
} req_dict_t;

void create_quest_cmd(char **arr);
void check_quest(char **arr);

#endif /* QUEST_H_ */
