#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND 10

typedef struct node_s
{
    int value;
    struct node_s *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
    int size;
} queue_t;

void enqueue(queue_t *q, int new_value);
void clear(queue_t *q);
void dump(queue_t *q);
int dequeue(queue_t *q);
int dequeue_n(queue_t *q, unsigned int n);
int length(queue_t *q);
int get_first(queue_t *q);
void print_queue(queue_t *q);
node_t *create_node(int new_value, node_t *next_node);
queue_t *create_queue();

#define INVALID_NUM -999

int length(queue_t *q)
{
    return q->size;
}

int get_first(queue_t *q)
{
    return q->head->next->value;
}

node_t *create_node(int new_value, node_t *next_node)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = new_value;
    node->next = next_node;
    return node;
}

queue_t *create_queue()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->head = queue->tail = create_node(INVALID_NUM, NULL);
    queue->size = 0;
    return queue;
}

void enqueue(queue_t *q, int new_value)
{
    q->tail->next = create_node(new_value, NULL);
    q->tail = q->tail->next;
    ++q->size;
}

/*dequeue is deleting at head of list - because it is O(1)*/
int dequeue(queue_t *queue)
{
    if (queue->size == 0)
        return INVALID_NUM;
    int element = queue->head->next->value;
    queue->head->next = queue->head->next->next;
    if (queue->head->next == NULL)
        queue->tail = queue->head;
    --queue->size;
    return element;
}

int dequeue_n(queue_t *queue, unsigned int n)
{
    if (n > queue->size)
    {
        return INVALID_NUM;
    }
    int sum = 0;
    while (n > 0 && queue->size > 0)
    {
        node_t* temp = queue->head->next;
        sum += temp->value;
        queue->head->next = queue->head->next->next;
        if (queue->head->next == NULL)
            queue->tail = queue->head;
        --queue->size;
        free(temp);
        --n;
    }

    return sum;
}

void print_queue(queue_t *queue)
{
    node_t *current = queue->head->next;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void clear(queue_t *queue)
{
    node_t *node = queue->head;
    while (node != NULL)
    {
        node_t *n_temp = node;
        node = node->next;
        free(n_temp);
    }
    queue->size = 0;
}

void dump(queue_t *queue)
{
    clear(queue);
    free(queue);
}

void choose_command(queue_t *q)
{
    char command[MAX_COMMAND];
    int x;
    while (1)
    {
        x = 0;
        scanf("%s", command);
        if (!strcmp(command, "enqueue"))
        {
            scanf("%d", &x);
            enqueue(q, x);
        }
        else if (!strcmp(command, "dequeue"))
        {
            scanf("%d", &x);
            int del = dequeue_n(q, x);
            if (del != INVALID_NUM)
            {
                printf("%d\n", del);
            }
        }
        else
        {
            break;
        }
    }
} 

int main()
{
    int c, n = 0;
    scanf("%d", &c);
    while (c > 0)
    {
        scanf("%d", &n);
        queue_t *q = create_queue();
        choose_command(q);
        dump(q);
        --c;
    }
}