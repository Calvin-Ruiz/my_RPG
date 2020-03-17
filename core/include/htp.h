/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2019
** File description:
** htp.h
*/

#ifndef HTP_H_
#define HTP_H_

typedef struct htp {
    sfView *view;
    float scroll;
    sfSprite *background;
    char opened;
} htp_t;

void init_htp_button(data_storage_t *datas);

#endif /* HTP_H_ */
