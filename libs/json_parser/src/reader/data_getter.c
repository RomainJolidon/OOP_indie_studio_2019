/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** data_getter
*/

#include "json_parser_reader.h"

data_t *get_list_of_key(data_t *object, const char *key)
{
    node_t *cur = NULL;
    data_t *data = NULL;

    if (object->type != TAB && object->type != OBJECT)
        return (NULL);
    cur = ((list_t *)object->value)->first;
    while (cur != NULL) {
        data = ((data_t *)cur->data);
        if (!strcmp(data->key, key) && data->type == TAB)
            return (data);
        cur = cur->next;
    }
    return (NULL);
}

char *get_attribute_of_key(data_t *object, const char *key)
{
    node_t *cur = NULL;
    data_t *data = NULL;

    if (!object || object->type != OBJECT)
        return (NULL);
    cur = ((list_t *)object->value)->first;
    while (cur != NULL) {
        data = ((data_t *)cur->data);
        if (!strcmp(data->key, key) && data->type == STRING)
            return (data->value);
        cur = cur->next;
    }
    return (NULL);
}

data_t *get_object_with_attribute(data_t *object, \
const char *key, const char *value)
{
    node_t *cur = NULL;
    data_t *data = NULL;
    char *res = NULL;

    if (!object || object->type != TAB) {
        puts("no objects found");
        return (NULL);
    }
    cur = ((list_t *)object->value)->first;
    while (cur != NULL) {
        data = ((data_t *)cur->data);
        res = get_attribute_of_key(data, key);
        if (res != NULL && !strcmp(res, value))
            return (data);
        cur = cur->next;
    }
    return (NULL);
}