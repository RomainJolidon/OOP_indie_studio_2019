/*
** EPITECH PROJECT, 2020
** json_parser
** File description:
** json_parser
*/

#ifndef JSON_PARSER_H_
#define JSON_PARSER_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>
#define ptr(value) (void *)&value
#define str(key, value) ptr(((data_t){STRING, key, (void *)value}))

enum data_type {OBJECT, STRING, TAB, NONE};

typedef struct data {
    enum data_type type;
    char *key;
    void *value;
} data_t;

typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct list {
    int size;
    node_t *first;
} list_t;

/*main method*/
/*cette méthode retourne un object data_t **/
/*contenant l'architecture du JSON*/
/*parsé trié selon les clés du JSON en question*/
data_t *parse_json(const char *filepath);

/*data getter related*/
//Return the attribute matching the given key in an object
//If not data matching the key is found, NULL is returned
char *get_attribute_of_key(data_t *object, const char *key);
//Return the array of data matching the key in an array of an object
//If not array matching the key is found, NULL is returned
data_t *get_list_of_key(data_t *object, const char *key);
data_t *get_object_with_attribute(data_t *object, \
const char *key, const char *value);


/*data setter related*/
//Write given data_t * to file "filepath".
//If the file doesn't exists, it is created
//Warning : the writer override the old content of the file
void write_json_object(data_t *object, const char *filepath);

/*object related*/
void dump_object(data_t *object);
data_t *create_data(enum data_type type, const char *key, void *value);
data_t *create_object(char *key, int size, ...);

/*object deleter*/
void delete_json_object(data_t *obj);

/*chained list*/
list_t *init_list(void);
void add_elem(list_t *list, void *data);
void delete_elem_at_pos(list_t *list, int pos);
void *get_data_at_pos(list_t *list, int pos);
list_t *create_list(int size, ...);

#endif /* !JSON_PARSER_H_ */
