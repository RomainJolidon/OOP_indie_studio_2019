/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** write_object
*/

#include "json_parser_writer.h"

bool init_object_writing(data_t *object, FILE *fd, int depth, bool is_end)
{
    if (object->type != OBJECT)
        return (false);
    write_key(object, fd, depth);
    write_object(object, fd, depth + 1);
    write_end(fd, is_end);
    return (true);
}

void write_object(data_t *object, FILE *fd, int depth)
{
    list_t *list = NULL;
    data_t *data = NULL;


    if (object->type != OBJECT)
        return;
    list = ((list_t *)object->value);
    write_start(fd, list->size == 0, "{");
    for (int i = 0; i < list->size; i++) {
        data = ((data_t*)get_data_at_pos(list, i));
        write_str_data(data, fd, depth, i + 1 >= list->size);
        init_array_writing(data, fd, depth, i + 1 >= list->size);
        init_object_writing(data, fd, depth, i + 1 >= list->size);
    }
    if (list->size != 0)
        write_depth(depth - 1, fd);
    fwrite("}", sizeof(char), 1, fd);
}