/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** json_parser
*/

#ifndef JSON_PARSER_READER_H_
#define JSON_PARSER_READER_H_

#include "json_parser.h"

/*data related*/

/*parsing related*/
void parse_object(FILE *fd, list_t *list);
void parse_tab(FILE *fd, list_t *list);
char *get_value(const char *str);
char *get_key(const char *str);
char *get_simple_value(const char *str);
bool check_if_object(const char *buffer, list_t *list, FILE *fd);
bool check_if_array(const char *buffer, list_t *list, FILE *fd);

#endif /* !JSON_PARSER_READER_H_ */
