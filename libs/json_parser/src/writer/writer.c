/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** writer
*/

#include "json_parser_writer.h"

void write_json_object(data_t *object, const char *filepath)
{
    FILE *fd = NULL;

    if (!object)
        return;
    fd = fopen(filepath, "w");
    if (!fd)
        return;
    if (object->type == TAB) {
        write_array(object, fd, 1);
    } else if (object->type == OBJECT)
        write_object(object, fd, 1);
    fclose(fd);
}