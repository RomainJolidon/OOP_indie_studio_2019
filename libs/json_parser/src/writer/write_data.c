/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** write_data
*/

#include "json_parser_writer.h"

void write_depth(int depth, FILE *fd)
{
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < DEPTH_SIZE; j++) {
            fwrite(" ", sizeof(char), 1, fd);
        }
    }
}

void write_key(const data_t *data, FILE *fd, int depth)
{
    write_depth(depth, fd);
    if (data->key != NULL && strlen(data->key) > 0) {
        fwrite("\"", sizeof(char), 1, fd);
        fwrite(data->key, sizeof(char), strlen(data->key), fd);
        fwrite("\"", sizeof(char), 1, fd);
        fwrite(": ", sizeof(char), 2, fd);
    }
}

void write_end(FILE *fd, bool is_end)
{
    if (is_end)
        fwrite("\n", sizeof(char), 1, fd);
    else
        fwrite(",\n", sizeof(char), 2, fd);
}

void write_start(FILE *fd, bool is_empty, char *start)
{
    fwrite(start, sizeof(char), strlen(start), fd);
    if (!is_empty)
        fwrite("\n", sizeof(char), 1, fd);
}

bool write_str_data(const data_t *data, FILE *fd, int depth, bool is_end)
{
    if (!data || !data->value || data->type != STRING)
        return (false);
    write_key(data, fd, depth);
    fwrite("\"", sizeof(char), 1, fd);
    fwrite(data->value, sizeof(char), strlen(((const char *)data->value)), fd);
    fwrite("\"", sizeof(char), 1, fd);
    write_end(fd, is_end);
    return (true);
}