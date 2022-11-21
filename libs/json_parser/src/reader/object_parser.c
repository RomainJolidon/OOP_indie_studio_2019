/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** object_parser
*/

#include "json_parser_reader.h"

bool is_object_empty(const char *buffer)
{
    if (strchr(buffer, '{') != NULL && strchr(buffer, '}') != NULL)
        return (true);
    return (false);
}

bool check_if_object(const char *buffer, list_t *list, FILE *fd)
{
    if (strchr(buffer, '{') != NULL) {
        add_elem(list, create_data(OBJECT, get_key(buffer), \
        init_list()));
        if (!is_object_empty(buffer))
            parse_object(fd, ((data_t *)list->first->data)->value);
        return (true);
    }
    return (false);
}

void parse_object(FILE *fd, list_t *list)
{
    char buffer[100] = {0};
    size_t size = 0;

    while (fgets(buffer, 100, fd) != NULL) {
        if (check_if_array(buffer, list, fd) || \
        check_if_object(buffer, list, fd)) {
            continue;
        }
        if (strchr(buffer, '}') != NULL) {
            break;
        } else if (strchr(buffer, ':') != NULL) {
            add_elem(list, create_data(STRING, get_key(buffer), \
            get_value(buffer)));
        }
        memset(buffer, 0, 99);
    }
}