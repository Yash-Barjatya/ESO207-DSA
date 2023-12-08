#include <stdio.h>
#include <stdlib.h>
struct TreeNode
{
    int data;
    struct TreeNode *right;
    struct TreeNode *left;
};
typedef struct TreeNode node;
node *make_node(int val)
{
    node *temp;
    temp = calloc(1, sizeof(node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
node *search(node *root, int val)
{
    if (!root)
        return root;
    if (root->data > val)
        return search(root->left, val);
    else if (root->data < val)
        return search(root->right, val);
    return root;
}
node *insert(node *root, int val)
{
    if (!root)
    {
        node *to_insert = make_node(val);
        return to_insert;
    }
    if (root->data > val)
        root->left = insert(root->left, val);
    else if (root->data < val)
        root->right = insert(root->right, val);
    return root;
}
void inorderTranversal(node *root)
{
    if (!root)
        return;
    inorderTranversal(root->left);
    printf("%d ", root->data);
    inorderTranversal(root->right);
}
int deleteMin(node *root)
{
    if (!root)
    {

        printf("\nPlease insert a node first\n");
        return -1;
    }
    else
    {
        node *to_delete = root;
        node *parent;
        parent = NULL;
        while (to_delete->left)
        {
            parent = to_delete;
            to_delete = to_delete->left;
        }
        parent->left = to_delete->right;
        return to_delete->data;
        free(to_delete);
    }
}
node *findLastRight(node *root)
{
    if (root->right == NULL)
        return root;
    return findLastRight(root->right);
}
node *transplant(node *root)
{
    if (!root->left)
        return root->right;
    else if (!root->right)
        return root->left;
    node *rightChild = root->right;
    node *lastRight = findLastRight(root->left);
    lastRight->right = rightChild;
    return root->left;
}
node *delete(node *root, int val)
{	
    node *to_delete = root;
    node *parent = NULL;
    while (to_delete->data != val)
    {
        if (!to_delete || to_delete->data == val)
        {
            break;
        }
        if (to_delete->data > val)
        {
            parent = to_delete;
            to_delete = to_delete->left;
        }
        else if (to_delete->data < val)
        {
            parent = to_delete;
            to_delete = to_delete->right;
        }
    }
    if (!to_delete)
    {
        printf("\nNo such key found!!\n");
        return root;
    }
    if (!parent)
    {
        // to delele ==root;
        root = transplant(root);
        return root;
    }
    if (!to_delete->left || !to_delete->right)
    {
        if (parent->data > to_delete->data)
        {
            if (!to_delete->left)
                parent->left = to_delete->right;
            else
                parent->left = to_delete->left;
        }
        else
        {
            if (!to_delete->left)
                parent->right = to_delete->right;
            else
                parent->right = to_delete->left;
        }
    }
    else
    { // node to be deleted has 2 children
        if (parent->left && parent->left->data == to_delete->data)
        {
            parent->left = transplant(to_delete);
        }
        else if (parent->right && parent->right->data == to_delete->data)
        {
            parent->right = transplant(to_delete);
        }
    }
    free(to_delete);
    return root;
}
int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    FILE *fp = fopen("random_number.txt", "rb");
    fread(a, sizeof(int), n, fp);
    node *root = malloc(sizeof(node));
    root = NULL;
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
        root = insert(root, a[i]);
    }
    printf("\ntype your query :\n");
    printf("1 -insertion\n");
    printf("2 -delete Min\n");
    printf("3 -delete random key\n");
    printf("4 -inorder traversal\n");
    printf("5 -search\n");
    printf("-1 -exit\n");
    int query;
    scanf("%d", &query);
    while (query != -1)
    {
        int key;
        if (query == 1)
        {
            scanf("%d", &key);
            root = insert(root, key);
            printf("\ninorder traversal after inserting %d:\n", key);
            inorderTranversal(root);
            printf("\n");
        }
        else if (query == 2)
        {
            int mn = deleteMin(root);
            if (mn != -1)
            {
                printf("\nThe minimum number deleted is : %d\n", mn);
            }
        }
        else if (query == 3)
        {
            scanf("%d", &key);
	   node *curr=root;
	   node *to_search=search(curr,key);
	   if(to_search)
	     {
            root = delete (root, key);
	     }
	   else
	     printf("\nNo such key found!\n");
        }
        else if (query == 4)
        {
            printf("\ninorder traversal:\n");
            inorderTranversal(root);
            printf("\n");
        }
        else if (query == 5)
        {
            scanf("%d", &key);
            node *to_search = search(root, key);
            if (to_search)
            {
                printf("\nThe key has been found\n");
            }
            else
                printf("\nNo such key found!!\n");
        }
        else
        {
            printf("\n bad query.Exiting\n");
        }
        scanf("%d", &query);
    }
    return 0;
}