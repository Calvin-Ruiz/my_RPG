/*
** EPITECH PROJECT, 2019
** entitylib2
** File description:
** solid_decor.c
*/

#include <entity.h>
#include <data_storage.h>
#include <tools.h>
#include <solid_decor.h>

void create_solid_decor_cmd(char **arr)
{
    decor_t *decor = malloc(sizeof(decor_t));
    data_storage_t *datas = get_data_storage();
    char *name = arr[1];

    arr = create_entity_base((entity_t *) decor, &datas->entities, arr);
    if (arr == NULL) {
        my_puterr("\e[91mFatal : Faild to build '");
        my_puterr(name);
        my_puterr("' decor.\n\e[0m");
    }
}

decor_t *new_solid_decor(char **arr)
{
    decor_t *decor = malloc(sizeof(decor_t));

    if (*arr == NULL)
        return (NULL);
    *decor = *(decor_t *) *arr;
    decor->pos.v1 = (sfVector2f) {(long) arr[1], (long) arr[2]};
    decor->pos.v2 = (sfVector2f) {decor->pos.v1.x + decor->size[0],
        decor->pos.v1.y + decor->size[1]};
    return (decor);
}
