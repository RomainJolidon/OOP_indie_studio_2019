/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** parser
*/

#include "json_parser_reader.h"

data_t *parse_json(const char *filepath)
{
    FILE *fd = fopen(filepath, "r");
    data_t *object = create_data(NONE, NULL, init_list());
    char buffer[100] = {0};

    if (!fd || !object)
        return (NULL);
    fgets(buffer, 100, fd);
    if (strchr(buffer, '[') != NULL) {
        object->type = TAB;
        parse_tab(fd, object->value);
    } else if (strchr(buffer, '{') != NULL) {
        object->type = OBJECT;
        parse_object(fd, object->value);
    }
    fclose(fd);
    return (object);
}
