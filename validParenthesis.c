/*
  Given an expression as string comprising of opening and closing characters
  of parentheses - (), curly braces - {} and square brackets - [], we need to 
  check whether symbols are balanced or not. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_NUM '#'
#define MAX_STR 20

typedef struct node_s
{
    char value;
    struct node_s *next;
} node_t;

typedef struct
{
    node_t *top;
    int size;
} stack_t;


node_t *create_node(char new_value, node_t *next_node)
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
        return INVALID_NUM;
    }
    int element = stack->top->next->value;
    node_t *temp = stack->top->next;
    stack->top->next = temp->next;
    free(temp);
    --stack->size;
    return element;
}

int valid_pair(char opening,char closing)
{
	if(opening == '(' && closing == ')')
        return 1;
	else if(opening == '{' && closing == '}')
        return 1;
	else if(opening == '[' && closing == ']')
        return 1;
	return 0;
}
int are_parantheses_balanced(char* exp)
{
    stack_t* stack = create_stack();
	for(int i =0;i<strlen(exp);i++)
	{
		if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
			push(stack,exp[i]);
		else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
		{
			if(stack->size == 0 || !valid_pair(stack->top->next->value,exp[i])){
				return 0;
            }
			else
				pop(stack);
		}
	}
    dump(stack);
    return 1;
}

int main()
{
	char expression[MAX_STR];
    printf("Enter an expression:  \n");
    scanf("%s",expression);
	if(are_parantheses_balanced(expression))
        printf("true\n");
	else
        printf("false\n");
}