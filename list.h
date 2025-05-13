#ifndef _LISTHS
#define _LISTHS
typedef struct node_s
{
    int value;
    struct node_s *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
    node_t *cursor;
    int size;
} list_t;

void insert(list_t *l, int new_value);
void dump(list_t *l);
void clear(list_t *l);
int count(list_t* l, int value);
void append(list_t *l, int new_value);
int delete_list(list_t *l);
void move_to_start(list_t *l);
void move_to_end(list_t *l);
void prev(list_t *l);
void next(list_t *l);
int length(list_t *l);
int current_pos(list_t *l);
void move_to_pos(list_t *l, unsigned int pos);
int get_value(list_t *l);
void print_list(list_t *l);
node_t *create_node(int new_value, node_t *next_node);
list_t *create_list();

#endif