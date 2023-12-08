#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
    int key;
    int rank;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} node;
node *root1 = NULL;
node *root2 = NULL;

node *newNode(int key)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    temp->rank = 0;
    temp->key = key;
    return temp;
}
int get_rank(node *z)
{
    if (!z)
        return 0;
    else
        return z->rank;
}
int isRed(node *z)
{
    if (z->parent->rank == z->rank)
        return 1;
    else
        return 0;
}
node *findMin(node *z)
{
    if (!z)
        return z;
    else
    {
        while (z->left)
        {
            z = z->left;
        }
    }
    return z;
}
node *searchNode(node *T, int k)
{
    if (!T)
    {
        printf("\nGiven key not found ");
        return NULL;
    }
    if (k > T->key)
        return searchNode(T->right, k);
    else if (k < T->key)
        return searchNode(T->left, k);
    else
    {
        printf("\nGiven key found ");
        return T;
    }
}
node *TriNode(node *T, node *z)
{
    node *g = z->parent->parent;
    node *p = z->parent;
    if ((g->key > p->key) && (p->key < z->key))
    {
        p->right = z->left;
        if (z->left)
            z->left->parent = p;
        g->left = z->right;
        if (z->right)
            z->right->parent = g;
        z->parent = g->parent;
        if (!g->parent)
            T = z;
        else if (g == g->parent->left)
            g->parent->left = z;
        else
            g->parent->right = z;
        z->left = p;
        z->right = g;
        p->parent = z;
        g->parent = z;
    }

    else if ((g->key > p->key) && (p->key > z->key))
    {
        g->left = p->right;
        if (p->right)
            p->right->parent = g;
        p->parent = g->parent;
        if (!g->parent)
            T = p;
        else if (g == g->parent->left)
            g->parent->left = p;
        else
            g->parent->right = p;
        p->right = g;
        g->parent = p;
    }
    else if ((g->key < p->key) && (p->key < z->key))
    {
        g->right = p->left;
        if (p->left)
            p->left->parent = g;
        p->parent = g->parent;
        if (!g->parent)
            T = p;
        else if (g == g->parent->left)
            g->parent->left = p;
        else
            g->parent->right = p;
        p->left = g;
        g->parent = p;
    }
    else if ((g->key < p->key) && (p->key > z->key))
    {
        p->left = z->right;
        if (z->right)
            z->right->parent = p;
        g->right = z->left;
        if (z->left)
            z->left->parent = g;
        z->parent = g->parent;
        if (!g->parent)
            T = z;
        else if (g == g->parent->left)
            g->parent->left = z;
        else
            g->parent->right = z;
        z->left = g;
        z->right = p;
        g->parent = z;
        p->parent = z;
    }

    return T;
}
node *FixInsert(node *T, node *z)
{
    node *p = z->parent;
    node *g = p->parent;

    while (p && g)
    { // if rank of z,p,g are all same
        if (isRed(z) == isRed(p))
        {
            // if g.key<p.key
            if (p == g->right)
            {
                if (!g->left)
                    T = TriNode(T, z);
                else
                {
                    if (g->rank == g->left->rank)
                    {
                        g->rank = g->rank + 1;

                        z = g;
                        p = g->parent;
                        if (g->parent != NULL)
                            g = g->parent->parent;
                        continue;
                    }
                    else
                        T = TriNode(T, z);
                }
            }
            // if g.key>p.key
            else if (p == g->left)
            {
                if (!g->right)
                    T = TriNode(T, z);
                else
                {
                    if (g->right->rank == g->rank)
                    {
                        g->rank++;
                        z = g;
                        p = g->parent;
                        if (g->parent != NULL)
                            g = g->parent->parent;
                        continue;
                    }
                    else
                        T = TriNode(T, z);
                }
            }
            return T;
        }
        else /*rank of z,p,g are not all same*/
            return T;
    }
    return T;
}

node *insertNode(node *T, int key)
{
    // similar to insertion of a node in a BST
    node *z = newNode(key);
    if (!T)
    {
        z->rank = 1;
        T = z;
        return T;
    }

    else
    {
        node *x = T;
        node *y = NULL;
        while (x != NULL)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else if (z->key == x->key)
                return T;
            else
                x = x->right;
        }
        z->parent = y;
        z->rank = 1;
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        T = FixInsert(T, z);
    }
    return T;
}
node *joinTree(node *T1, node *T2, int to_join)
{

    // All the nodes in T1 have keys less than 'to_join' and all the nodes in T2 have keys greater than 'to_join'
    node *new_root = NULL;
    if (get_rank(T1) > get_rank(T2))
    {
        node *temp = T1;

        // Take right pointers till we reach a node with same rank as T2
        while (get_rank(temp) != get_rank(T2))
        {
            temp = temp->right;
        }

        node *z = (node *)malloc(sizeof(node));
        z->parent = temp->parent;
        temp->parent->right = z;
        z->left = temp;
        z->right = T2;
        z->key = to_join;
        z->rank = get_rank(T2) + 1;
        new_root = FixInsert(T1, z);
    }
    else if (get_rank(T1) == get_rank(T2))
    {
        node *z = (node *)malloc(sizeof(node));
        z->parent = NULL;
        z->left = T1;
        z->right = T2;
        z->key = to_join;
        z->rank = get_rank(T1) + 1;
        new_root = z;
    }
    else
    {
        node *temp = T2;

        // Take left pointers till we reach a node with same rank as T1
        while (get_rank(temp) != get_rank(T1))
        {
            temp = temp->left;
        }

        node *z = (node *)malloc(sizeof(node));
        z->parent = temp->parent;
        temp->parent->left = z;
        z->left = T1;
        z->right = temp;
        z->key = to_join;
        z->rank = get_rank(T1) + 1;
        new_root = FixInsert(T2, z);
    }
    return new_root;
}
void splitTree(node *T, int split_at, node **T1, node **T2)
{
    node *z = searchNode(T, split_at);
    if (!z)
    {
        printf("Given key not found\n");
        return;
    }
    // All the nodes in T1 have keys less than 'split_at' and all the nodes in T2 have keys greater than 'split_at'
    *T2 = z->right;
    *T1 = z->left;
    while (z->parent)
    {
        node *y = z->parent;
        if (y->right == z)
        {
            *T1 = joinTree(*T1, y->left, y->key);
        }
        else
        {
            *T2 = joinTree(*T2, y->right, y->key);
        }
        z = y;
    }
    return;
}
void inorder(node *T)
{
    if (!T)
        return;
    else
    {
        inorder(T->left);
        printf("(%d : %d) ", T->key, T->rank);
        inorder(T->right);
    }
}
int main()
{
    int n1 = 4;
    int n2 = 10;
    int arr1[4] = {1, 2, 3, 4};
    int arr2[10] = {6, 7, 8, 9, 10, 13, 14, 15, 16, 17};

    for (int i = 0; i < n1; i++)
    {
        root1 = insertNode(root1, arr1[i]);
    }
    for (int i = 0; i < n2; i++)
    {
        root2 = insertNode(root2, arr2[i]);
    }

    printf("\nInorder traversal of Tree1 is: ");
    inorder(root1);
    printf("\n");
    printf("\nInorder traversal of Tree2 is: ");
    inorder(root2);
    printf("\n");
    int to_join = 5;
    printf("\nAfter joining %d to the tree :\n", to_join);
    root1 = joinTree(root1, root2, to_join);
    printf("\nInorder traversal of new tree is: ");
    inorder(root1);
    printf("\n");
    printf("\nNew root is: %d", root1->key);
    printf("\nNew root rank: %d", root1->rank);

    node *T1 = NULL;
    node *T2 = NULL;
    int split_at = 5;
    printf("\n\nAfter spliting the tree at %d :", split_at);
    splitTree(root1, split_at, &T1, &T2);
    printf("\n\nInorder traversal of T1 is:\n");
    inorder(T1);
    printf("\nRoot of T1 is: %d", T1->key);
    printf("\nRank of T1 is: %d", T1->rank);
    printf("\n\nInorder traversal of T2 is: ");
    inorder(T2);
    printf("\nRoot of T2 is: %d", T2->key);
    printf("\nRank of T2 is: %d", T2->rank);

    return 0;
}