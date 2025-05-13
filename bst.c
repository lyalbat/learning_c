#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode_t;

TreeNode_t *create_node(int value)
{
    TreeNode_t *node = (TreeNode_t *)malloc(sizeof(TreeNode_t));
    node->value = value;
    node->left = node->right = NULL;
    return node;
};

TreeNode_t *insert_to_bst(TreeNode_t *root, int value)
{
    // this is a binary search tree (BST)
    if (root == NULL)
    {
        root = create_node(value);
        return root;
    }
    TreeNode_t *temp = root;
    while (1)
    {
        if (value <= temp->value)
        {
            if (temp->left == NULL)
            {
                temp->left = create_node(value);
                free(temp);
                return root;
            }
            temp = temp->left;
        }
        else
        {
            if (temp->right == NULL)
            {
                temp->right = create_node(value);
                free(temp);
                return root;
            }
            temp = temp->right;
        }
    }
}
int search_bst(TreeNode_t *root, int value)
{
    if (root == NULL)
        return 0;
    TreeNode_t *temp = root;
    while (1)
    {
        if (temp->value == value)
        {
            free(temp);
            return 1;
        }
        
        else if (value <= temp->value)
        {
            if (temp->left == NULL)
            {
                free(temp);
                return 0;
            }
            temp = temp->left;
        }
        else
        {
            if (temp->right == NULL)
            {
                free(temp);
                return 0;
            }
            temp = temp->right;
        }
    }
}

void print_search_result(int result, int data){
    if(result>0)
        printf("%d is in the binary tree!\n",data);
    else
        printf("%d is not in the binary tree!\n",data);
}

int main()
{
    TreeNode_t *root = NULL;
    int nodes[] = {15, 10, 20, 25, 8, 12};
    for (int i = 0; i < 7; i++)
    {
        root = insert_to_bst(root, nodes[i]);
    }
    int search;
    search = search_bst(root,15);
    print_search_result(search,15);
    search = search_bst(root,7);
    print_search_result(search,7);
    search = search_bst(root,12);
    print_search_result(search,12);
    return 0;
}