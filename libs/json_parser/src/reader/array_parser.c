/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** array_parser
*/

#include "json_parser_reader.h"

bool is_array_empty(const char *buffer)
{
    if (strchr(buffer, '[') != NULL && strchr(buffer, ']') != NULL)
        return (true);
    return (false);
}

bool check_if_array(const char *buffer, list_t *list, FILE *fd)
{
    if (strchr(buffer, '[') != NULL) {
        add_elem(list, create_data(TAB, get_key(buffer), \
        init_list()));
        if (!is_array_empty(buffer))
            parse_tab(fd, ((data_t *)list->first->data)->value);
        return (true);
    }
    return (false);
}

void parse_tab(FILE *fd, list_t *list)
{
    char buffer[100] = {0};

    while (fgets(buffer, 100, fd) != NULL) {
        if (check_if_array(buffer, list, fd))
            continue;
        if (strchr(buffer, ']') != NULL) {
            break;
        }
        if (check_if_object(buffer, list, fd)) {
            continue;
        } else if (strchr(buffer, '\"') != NULL){
            add_elem(list, create_data(STRING, NULL, \
            get_simple_value(buffer)));
        }
        memset(buffer, 0, 99);
    }
}