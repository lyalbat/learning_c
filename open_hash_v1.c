#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND 8
#define MAX_NAME 21
#define MAX_CPF 15
#define MAX_ENTRIES 3
#define MAX_SLICE 4

unsigned int sfold(char *K, int m);

typedef struct node_s
{
    char* cpf_t;
    char* name_t;
    struct node_s *next;
} node_t;

typedef struct hash_map_s {
    int num_keys, capacity;
    node_t** list_ptrs;
} hash_map_t;

node_t *create_node(char* key, char* value, node_t *next_node)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    strcpy(node->cpf_t,key);
    strcpy(node->cpf_t,key);
    node->cpf_t = key;
    node->name_t = value;
    node->next = next_node;
    return node;
}

hash_map_t* create_dictionary()
{
    hash_map_t* dictionary = (hash_map_t*)malloc(sizeof(hash_map_t));
    dictionary->capacity = MAX_ENTRIES;
    dictionary->num_keys = 0;

    dictionary->list_ptrs =
    (node_t**)malloc(sizeof(node_t*)*dictionary->capacity); //dicionario com ponteiro para as listas
    return dictionary;
}

void print_person(char* cpf, char*nome){
    printf("you found %s (cpf: %s)\n", nome, cpf);
}

void insert(hash_map_t* dict, char* key, char* value)
{
    int h = sfold(key, MAX_ENTRIES);

    if (dict->list_ptrs[h] == NULL) { //sem colisao
        print_person(key,value);
        dict->list_ptrs[h] = create_node(key,value,NULL);
        print_person(dict->list_ptrs[h]->cpf_t,dict->list_ptrs[h]->name_t);
    }
    else { //com colisao
        node_t* new_node = create_node(key,value,dict->list_ptrs[h]);
        dict->list_ptrs[h] = new_node;
    }
    ++dict->num_keys;
    return;
}

void delete(hash_map_t* dict, char* cpf)
{
    int h = sfold(cpf, MAX_ENTRIES);

    node_t* prev_node = NULL;
    node_t* temp = dict->list_ptrs[h];

    while (temp != NULL) {
        if (strcmp(cpf, temp->cpf_t) == 0) {
            if (temp == dict->list_ptrs[h]) {
                dict->list_ptrs[h] = temp->next;
            }
            else {
                prev_node->next = temp->next;
            }
            free(temp);
            break;
        }
        prev_node = temp;
        temp = temp->next;
    }
    return;
}

char* search(hash_map_t* hash_map, char* cpf)
{
    int h = sfold(cpf, MAX_ENTRIES);
    node_t* head = hash_map->list_ptrs[h];
    while (head != NULL) {
        if(strcmp(cpf, head->cpf_t) == 0) {
            print_person(head->cpf_t,head->name_t);
            return head->name_t;
        }
        head = head->next;
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
        printf("please type the desired command:\n");
        scanf("%s", command);
        printf("please type the desired cpf:\n");
        if (!strcmp(command, "insert"))
        {
            char name[MAX_NAME];
            scanf(" %s", cpf);
            printf("now please type the desired name:\n");
            scanf(" %s", name);
            insert(dictionary,cpf,name);
            printf("sucessfull insert\n");
        }
        else if (!strcmp(command, "remove"))
        {
            scanf(" %s", cpf);
            delete(dictionary,cpf);    
            printf("sucessfull deletion\n");        
        }
        else if (!strcmp(command, "search"))
        {
            scanf(" %s", cpf);
            char* result = search(dictionary,cpf);
            printf("%s\n",result);
        }
        else{
            break;
        }
        printf("\n");
    }
}

int main(){
    choose_command();
    return 0;
}
