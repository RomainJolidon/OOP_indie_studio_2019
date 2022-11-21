/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** user
*/

#include "json_parser_reader.h"


data_t *create_data(enum data_type type, const char *key, void *value)
{
    data_t *data = malloc(sizeof(data_t));

    if (!data)
        return (NULL);
    if (key != NULL && strlen(key) > 0) {
        data->key = strdup(key);
    } else
        data->key = NULL;
    data->value = value;
    data->type = type;


    return (data);
}

data_t *create_object(char *key, int size, ...)
{
    data_t *obj = create_data(OBJECT, key, init_list());
    va_list va;

    if (!obj)
        return (NULL);
    va_start(va, size);
    for (int i = 0; i < size; i++)
        add_elem((list_t *)obj->value, va_arg(va, void *));
    va_end(va);
    return (obj);
}

void dump_object(data_t *object)
{
    (void)object;
}