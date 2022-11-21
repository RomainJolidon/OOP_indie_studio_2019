/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** json_parser_writer
*/

#ifndef JSON_PARSER_WRITER_H_
#define JSON_PARSER_WRITER_H_

#include "json_parser.h"

#define DEPTH_SIZE 4

void write_array(data_t *object, FILE *fd, int depth);
void write_object(data_t *object, FILE *fd, int depth);
bool init_array_writing(data_t *object, FILE *fd, int depth, bool is_end);
bool init_object_writing(data_t *object, FILE *fd, int depth, bool is_end);

bool write_str_data(const data_t *data, FILE *fd, int depth, bool is_end);
void write_key(const data_t *data, FILE *fd, int depth);
void write_depth(int depth, FILE *fd);
void write_end(FILE *fd, bool is_end);
void write_start(FILE *fd, bool is_empty, char *start);

#endif /* !JSON_PARSER_WRITER_H_ */
