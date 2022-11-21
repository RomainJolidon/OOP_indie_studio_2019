/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** chained_list
*/

#include "json_parser_reader.h"

list_t *init_list(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (!list) {
        return (NULL);
    }
    list->first = NULL;
    list->size = 0;
    return (list);
}

void add_elem(list_t *list, void *data)
{
    node_t *new = malloc(sizeof(node_t));

    if (!list || !new || !data) {
        return;
    }
    new->data = data;
    new->next = list->first;
    new->prev = NULL;
    if (list->first != NULL)
        list->first->prev = new;
    list->first = new;
    list->size++;
}

list_t *create_list(int size, ...)
{
    list_t *list = init_list();

    va_list va;
    va_start(va, size);
    for (int i = 0; i < size; i++)
        add_elem(list, va_arg(va, void *));
    va_end(va);
    return (list);
}

void delete_elem_at_pos(list_t *list, int pos)
{
    node_t *actual = list->first;
    int count = 0;

    while (count < pos && actual != NULL) {
        count++;
        actual = actual->next;
    }
    if (!actual) {
        return;
    }
    if (actual->prev != NULL)
        actual->prev->next = actual->next;
    else
        list->first = actual->next;
    if (actual->next != NULL)
        actual->next->prev = actual->prev;
    free(actual->data);
    free(actual);
    list->size--;
}

void *get_data_at_pos(list_t *list, int pos)
{
    node_t *actual = list->first;
    int count = 0;

    while (count < pos && actual != NULL) {
        count++;
        actual = actual->next;
    }
    if (actual == NULL)
        return (NULL);
    return (actual->data);
}