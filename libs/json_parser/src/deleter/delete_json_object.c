/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** delete_json_object
*/

#include "json_parser.h"

void delete_json_object(data_t *obj)
{
    data_t *cur = NULL;

    if (!obj || obj->type == NONE)
        return;
    if (obj->type == STRING) {
        if (obj->key)
            free(obj->key);
        if (obj->value)
            free(obj->value);
        return;
    }
    while (((list_t *)obj->value)->size > 0) {
        cur = ((data_t *)((list_t *)obj->value)->first->data);
        delete_json_object(cur);
        delete_elem_at_pos(obj->value, 0);
    }
    if (obj->key)
        free(obj->key);
    if (obj->value)
        free(obj->value);
}