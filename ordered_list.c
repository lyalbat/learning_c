#include <stdio.h>
#include <stdlib.h>

#define SENT -1

typedef struct node_s
{
    int key;
    struct node_s *next;
} node_t;

typedef struct
{
    node_t *head;
    int size;
} list_t;

void insert_node(int key, list_t *list_info);
node_t *get_next_node(int key, node_t *node);
void free_linked_list(list_t *list_info);
void print_list(list_t *list_info);

int delete_node(list_t *list_info, int target);

int main()
{
    int new_key = 0;
    list_t list_info = {NULL, 0};
    int i = 0;

    int key_input[] = {5,4,8,9,-1};

    printf("Enter integer keys. If you want to break, type %d\n", SENT);
    while (new_key != SENT)
    {
        new_key = key_input[i];
        //scanf("%d", &new_key);
        if (new_key != SENT)
        {
            insert_node(new_key, &list_info);
        }
        ++i;
    }
    print_list(&list_info);
    
    int key_input_delete[] = {4,2,-1};
    
    new_key = 0;
    i = 0;
    printf("\nEnter a value to delete or %d to quit> ", SENT);
    while (new_key != SENT)
    {
        new_key = key_input_delete[i];
        if (delete_node(&list_info, new_key))
        {
            printf("%d deleted. New list:\n", new_key);
            print_list(&list_info);
        }
        else
        {
            printf("No deletion. %d not found\n", new_key);
        }
        ++i;
    }
        
    free_linked_list(&list_info);
    return 0;
}

void insert_node(int key, list_t *list_info)
{
    ++(list_info->size);
    list_info->head = get_next_node(key, list_info->head);
}

node_t *get_next_node(int new_key, node_t *head)
{
    node_t *new_head;
    new_head = (node_t *)malloc(sizeof(node_t));
    new_head->key = new_key;

    if (head == NULL)
    {
        new_head->next = NULL;
    }
    else if (head->key >= new_key)
    {
        new_head->next = head;
    }
    else
    {
        node_t *temp = head;
        while (temp->next != NULL || temp->key >= new_key)
        {
            temp->next = temp;
        }
        new_head->next = temp;
    }
    return (new_head);
}

void print_list(list_t *list_info)
{
    node_t *current = list_info->head;
    while (current != NULL)
    {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

void free_linked_list(list_t *list_info)
{
    node_t *node = list_info->head;
    while (node != NULL)
    {
        node_t *n_temp = node;
        node = node->next;
        free(n_temp);
    }
}

// algoritmo do livro
int delete_node(list_t *list_info, int target)
{
    node_t *to_freep;
    node_t *cur_nodep;
    int is_deleted;
    if (list_info->size == 0)
    {
        is_deleted = 0;
    }
    else if (list_info->head->key == target)
    {
        to_freep = list_info->head;
        list_info->head = to_freep->next;
        free(to_freep);
        --(list_info->size);
        is_deleted = 1;
    }
    else
    {
        for (cur_nodep = list_info->head;
             cur_nodep->next != NULL && cur_nodep->next->key < target;
             cur_nodep = cur_nodep->next)
        {
        }
        if (cur_nodep->next != NULL && cur_nodep->next->key == target)
        {
            to_freep = cur_nodep->next;
            cur_nodep->next = to_freep->next;
            free(to_freep);
            --(list_info->size);
            is_deleted = 1;
        }
        else
        {
            is_deleted = 0;
        }
    }
    return (is_deleted);
}
