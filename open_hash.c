#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND 8
#define MAX_NAME 21
#define MAX_CPF 15
#define MAX_ENTRIES 15
#define MAX_SLICE 4
#define CHOSEN_M 1000
#define INVALID_STR "#!"

unsigned int sfold(char *K, int m);

typedef struct node_s
{
    char* cpf_t;
    char* name_t;
    struct node_s *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
    int size;
} list_t;

typedef struct hash_map_s {
    int num_keys, capacity;
    list_t** lists_ptr;
} hash_map_t;

node_t *create_node(char* key, char* value, node_t *next_node)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->cpf_t = key;
    node->name_t = value;
    node->next = next_node;
    return node;
}

list_t *create_list()
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->head = list->tail = create_node(INVALID_STR, INVALID_STR, NULL);
    list->size = 0;
    return list;
}

hash_map_t* create_dictionary()
{
    hash_map_t* dictionary = (hash_map_t*)malloc(sizeof(hash_map_t));
    dictionary->capacity = MAX_ENTRIES;
    dictionary->num_keys = 0;
    
    //criando um array de ponteiros para listas ligadas
    dictionary->lists_ptr =
    (list_t**)malloc(sizeof(list_t*)*dictionary->capacity);
    return dictionary;
}

void add_to_list(list_t *l, char* cpf, char* name)
{
    l->head->next = create_node(cpf,name, l->head->next);
    if (l->tail == l->head)
    {
        l->tail = l->head->next;
    }
    ++l->size;
}

// int get_value(list_t *l)
// {
//     if (l->cursor->next == NULL)
//     {
//         //printf("error: there are no values after the cursor!\n");
//         return INVALID_NUM;
//     }
//     return l->cursor->next->value;
// }


void insert(hash_map_t* dict, char* key, char* value)
{
    int h = sfold(key, CHOSEN_M);

    if (dict->lists_ptr[h] == NULL) { //sem colisao
        dict->lists_ptr[h] = create_list();
        add_to_list(dict->lists_ptr[h],key,value);
    }
    else { //com colisao
        add_to_list(dict->lists_ptr[h],key,value);
    }
    ++dict->num_keys;
    return;
}

int delete_list(list_t* l, char* cpf){
    node_t *current = l->head->next;
    node_t *previous = l->head;
    while (current != NULL)
    {
        if(strcmp(cpf, current->cpf_t) == 0){
            previous->next = current->next;
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}

int delete(hash_map_t* dict, char* cpf)
{
    int h = sfold(cpf, CHOSEN_M);
    node_t* prev_node = NULL;
    list_t* temp = dict->lists_ptr[h];
    if(delete_list(temp, cpf)){
        if(temp->size == 0){
            free(temp);
        }
        return 1;
    }
    return 0;
}

char* search(hash_map_t* dict, char* cpf)
{
    int h = sfold(cpf, CHOSEN_M);
    node_t* current = dict->lists_ptr[h]->head->next;
    while (current != NULL) {
        if (strcmp(cpf, current->cpf_t) == 0) {
            printf("your desired cpf: %s\n",cpf);
            printf("current cpf: %s\n",current->cpf_t);
            return current->name_t;
        }
        current = current->next;
    }

    char* error_msg = "Name is not in dictionary.";
    return error_msg;
}

unsigned int sfold(char *K, int m)
{
    int slices = strlen(K) / 4;
    int sum = 0;
    int mult = 1;
    char sub[MAX_SLICE + 1];
    for (int i = 0; i < slices; i++)
    {
        memcpy(sub, &K[i * 4], 4);
        sub[MAX_SLICE] = '\0';
        mult = 1;
        for (int j = 0; j < 4; j++)
        {
            sum += sub[j] * mult;
            mult *= 256;
        }
    }
    int sub_size = strlen(K) - (4 * slices);
    if (sub_size != 0)
    {
        memcpy(sub, &K[slices * 4], sub_size);
        sub[sub_size] = '\0';
        mult = 1;
        for (int i = 0; i < sub_size; i++)
        {
            sum += sub[i] * mult;
            mult *= 256;
        }
    }
    return abs(sum)%m;
}

void choose_command()
{
    hash_map_t* dictionary = create_dictionary();
    char command[MAX_COMMAND];
    char cpf[MAX_CPF];
    while (1)
    {
        printf("please type your desired command:\n");
        scanf("%s", command);
        if (!strcmp(command, "insert"))
        {
            char name[MAX_NAME];
            printf("please type the desired cpf:\n");
            scanf(" %s", cpf);
            printf("now please type the desired name:\n");
            scanf(" %s", name);
            insert(dictionary,cpf,name);
            printf("sucessfull insert\n");
        }
        else if (!strcmp(command, "remove"))
        {
            printf("please type the desired cpf:\n");
            scanf(" %s", cpf);
            delete(dictionary,cpf);    
            printf("sucessfull deletion\n");        
        }
        else if (!strcmp(command, "search"))
        {
            printf("please type the desired cpf:\n");
            scanf(" %s", cpf);
            char* result = search(dictionary,cpf);
            printf("%s\n",result);
        }
        else{
            break;
        }
    }
}

int main(){
    choose_command();
    return 0;
}