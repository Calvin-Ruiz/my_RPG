/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** quest_list.h
*/

#ifndef QUEST_LIST_H_
#define QUEST_LIST_H_

typedef struct req_list {
    dynamic_text_t *dtext;
    sfText *text;
    struct req_list *next;
} req_list_t;

typedef struct quest_list {
    image_t *image;
    sfText *desc;
    req_list_t *req;
    struct quest_list *next;
} quest_list_t;

void update_quest_list(dynamic_list_t *self, sfRenderWindow *window,
    data_storage_t *datas, sfVector2f *pos);
void destroy_quest_list_content(dynamic_list_t *self);
void open_quest_menu(void *ptr);

#endif /* QUEST_LIST_H_ */
