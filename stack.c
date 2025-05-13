#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND 9

typedef struct node_s
{
    int value;
    struct node_s *next;
} node_t;

typedef struct
{
    node_t *top;
    int size;
} stack_t;

void push(stack_t *s, int new_value);
void clear(stack_t *s);
void dump(stack_t *s);
int pop(stack_t *s);
int pop_n(stack_t *s, unsigned int n);
int length(stack_t *s);
int get_top(stack_t *s);
void print_stack(stack_t *s);
node_t *create_node(int new_value, node_t *next_node);
stack_t *create_stack();

#define INVALID_NUM -999

int length(stack_t *s)
{
    return s->size;
}

int get_top(stack_t *s)
{
    return s->top->next->value;
}

node_t *create_node(int new_value, node_t *next_node)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = new_value;
    node->next = next_node;
    return node;
}

stack_t *create_stack()
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    stack->top = create_node(INVALID_NUM, NULL);
    stack->size = 0;
    return stack;
}

void push(stack_t *s, int new_value)
{
    s->top->next = create_node(new_value, s->top->next);
    ++s->size;
}

void print_stack(stack_t *stack)
{
    node_t *current = stack->top->next;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void clear(stack_t *stack)
{
    node_t *node = stack->top;
    while (node != NULL)
    {
        node_t *n_temp = node;
        node = node->next;
        free(n_temp);
    }
    stack->size = 0;
}

void dump(stack_t *stack)
{
    clear(stack);
    free(stack);
}

int pop(stack_t *stack)
{
    if (stack->size == 0)
    {
        // printf("Error: no values at right of cursor - couldn't delete\n");
        return INVALID_NUM;
    }
    int element = stack->top->next->value;
    node_t *temp = stack->top->next;
    stack->top->next = temp->next;
    free(temp);
    --stack->size;
    return element;
}
int pop_n(stack_t *stack, unsigned int n)
{
    if (stack->size == 0)
    {
        // printf("Error: no values at right of cursor - couldn't delete\n");
        return INVALID_NUM;
    }
    int sum = 0;
    while (n > 0 && stack->size>0)
    {
        sum += stack->top->next->value;
        node_t *temp = stack->top->next;
        stack->top->next = temp->next;
        free(temp);
        --stack->size;
        --n;
    }

    return sum;
}

void choose_command(stack_t *s)
{
    char command[MAX_COMMAND];
    int x;
    while (1)
    {
        x = 0;
        scanf("%s", command);
        if (!strcmp(command, "push"))
        {
            scanf("%d", &x);
            push(s, x);
        }
        else if (!strcmp(command, "pop"))
        {
            scanf("%d", &x);
            int pop_result = pop_n(s,x);
            if (pop_result != INVALID_NUM)
            {
                printf("%d\n", pop_result);
            }
            
        }else{
            break;
        }
        //print_stack(s);
    }
}

int main()
{
    int c, n = 0;
    scanf("%d", &c);
    while (c > 0)
    {
        scanf("%d", &n);
        stack_t *s = create_stack();
        choose_command(s);
        dump(s);
        --c;
    }
}