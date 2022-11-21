/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** line_parser
*/

#include "json_parser_reader.h"


char *get_simple_value(const char *str)
{
    char whitelist[] = " *-_";
    char *value = calloc(sizeof(char), strlen(str));
    int idx = 0;
    int start = 0;

    if (!value)
        return (NULL);
    while (str[start] != '\"' && str[start] != '\0') {
        start++;
    }
    for (int i = start; str[i] != '\0'; i++) {
        if (isalnum(str[i]) != 0 || strchr(whitelist, str[i]) != NULL) {
            value[idx++] = str[i];
        }
    }
    return (value);
}

char *get_key(const char *str)
{
    char *data = calloc(sizeof(char), strlen(str));
    int start = 0;

    if (!data)
        return (NULL);
    while (str[start] != '\"' && str[start] != '\0') {
        start++;
    }
    if (str[start] == '\0')
        return (data);
    start++;
    for (int i = 0; str[start] != '\"' && str[start] != '\0'; i++) {
        data[i] = str[start++];
    }
    data[start] = '\0';
    return (data);
}

char *get_value(const char *str)
{
    int start = 0;

    while (str[start] != ':' && str[start] != '\0') {
        start++;
    }
    return (get_key(str + start + 1));
}