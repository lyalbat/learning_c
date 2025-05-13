#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#define INVALID_NUM -999

int length(list_t *l){
    return l->size;
}
int get_value(list_t *l)
{
    if (l->cursor->next == NULL)
    {
        //printf("error: there are no values after the cursor!\n");
        return INVALID_NUM;
    }
    return l->cursor->next->value;
}

int count(list_t* l, int value){
    int x_times = 0;
    node_t *current = l->head;
    while (current != NULL)
    {
        if(current->value == value)
            ++x_times;
        current = current->next;
    }
    return x_times;
}
int current_pos(list_t *l)
{
    int pos = 0;
    node_t *current = l->head;
    while (current != l->cursor)
    {
        current = current->next;
        ++pos;
    }
    return pos;
}
void move_to_start(list_t *l)
{
    l->cursor = l->head;
}
void move_to_end(list_t *l)
{
    l->cursor = l->tail;
}
void next(list_t *l){
    if(l->cursor->next == NULL)
        return;
    l->cursor = l->cursor->next;
}
void move_to_pos(list_t *l, unsigned int pos){
    if(pos > l->size){
        //printf("Error: this position does not exist in the list\n");
        return;
    }
    move_to_start(l);
    for (int i = 0; i < pos; i++)
    {
        l->cursor = l->cursor->next;
    }   
}
void prev(list_t *l){
    if (l->cursor != l->head)
    {
        node_t* temp = l->head;
        while (temp->next != l->cursor)
        {
            temp = temp -> next;
        }
        l->cursor = temp;   
    }
     
}
node_t *create_node(int new_value, node_t *next_node)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = new_value;
    node->next = next_node;
    return node;
}
list_t *create_list()
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->head = list->cursor = list->tail = create_node(INVALID_NUM, NULL);
    list->size = 0;
    return list;
}

void insert(list_t *l, int new_value)
{
    l->cursor->next = create_node(new_value, l->cursor->next);
    if (l->tail == l->cursor)
    {
        l->tail = l->cursor->next;
    }
    ++l->size;
}
void append(list_t *l, int new_value)
{
    l->tail->next = create_node(new_value, NULL);
    l->tail = l->tail->next;
    ++l->size;
}

void print_list(list_t *list)
{
    node_t *current = list->head->next;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void clear(list_t *list)
{
    node_t *node = list->head;
    while (node != NULL)
    {
        node_t *n_temp = node;
        node = node->next;
        free(n_temp);
    }
    list->size = 0;
}

void dump(list_t *list)
{
    clear(list);
    free(list);
}

int delete_list(list_t* list){
    if(list->cursor->next == NULL){
        //printf("Error: no values at right of cursor - couldn't delete\n");
        return INVALID_NUM;
    }
    int element = list->cursor->next->value;
    if(list->tail == list->cursor->next){
        list->tail = list->cursor;
    }
    node_t* temp = list->cursor->next;
    list->cursor->next = temp->next;
    free(temp);
    --list->size;
    return element;
}