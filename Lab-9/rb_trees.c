#include <stdlib.h>
#include <stdio.h>
struct Node
{
    int key;
    int rank;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;

Node *newNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->rank = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void updateRank(Node *node)
{
    int leftRank = node->left ? node->left->rank : -1;
    int rightRank = node->right ? node->right->rank : -1;
    node->rank = leftRank > rightRank ? leftRank + 1 : rightRank + 1;
}

Node *rotateLeft(Node *node)
{
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateRank(node);
    updateRank(newRoot);
    return newRoot;
}

Node *rotateRight(Node *node)
{
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateRank(node);
    updateRank(newRoot);
    return newRoot;
}

Node *rebalance(Node *node)
{
    int leftRank = node->left ? node->left->rank : -1;
    int rightRank = node->right ? node->right->rank : -1;
    if (leftRank - rightRank > 1)
    {
        int leftLeftRank = node->left->left ? node->left->left->rank : -1;
        int leftRightRank = node->left->right ? node->left->right->rank : -1;
        if (leftLeftRank >= leftRightRank)
        {
            node = rotateRight(node);
        }
        else
        {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    }
    else if (rightRank - leftRank > 1)
    {
        int rightRightRank = node->right->right ? node->right->right->rank : -1;
        int rightLeftRank = node->right->left ? node->right->left->rank : -1;
        if (rightRightRank >= rightLeftRank)
        {
            node = rotateLeft(node);
        }
        else
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }
    return node;
}

Node *insert(Node *node, int key)
{
    if (!node)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    updateRank(node);
    return rebalance(node);
}

Node *delete(Node *node, int key)
{
    if (!node)
    {
        return NULL;
    }
    if (key < node->key)
    {
        node->left = delete (node->left, key);
    }
    else if (key > node->key)
    {
        node->right = delete (node->right, key);
    }
    else
    {
        if (!node->left)
        {
            Node *temp = node->right;
            free(node);
            return temp;
        }
        else if (!node->right)
        {
            Node *temp = node->left;
            free(node);
            return temp;
        }
        else
        {
            Node *temp = node->right;
            while (temp->left)
            {
                temp = temp->left;
            }
            node->key = temp->key;
            node->right = delete (node->right, temp->key);
        }
    }
    updateRank(node);
    return rebalance(node);
}
Node *search(Node *node, int key)
{
    while (node)
    {
        if (key < node->key)
        {
            node = node->left;
        }
        else if (key > node->key)
        {
            node = node->right;
        }
        else
        {
            return node;
        }
    }
    return NULL;
}
Node *findMin(Node *node)
{
    if (!node)
    {
        return NULL;
    }
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

void preorder(struct Node *root)
{
    if (!root)
        return;
    printf("(%d,%d)", root->key, root->rank);
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    printf("HOW MANY NUMBERS TO BE INSERTED FROM THE RANDOM NUMBER GENERATOR FILE \n");
    int n;
    scanf("%d", &n);
    int a[n];
    FILE *fp = fopen("random_number.txt", "rb");
    fread(a, sizeof(int), n, fp);
    fclose(fp);
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        root = insert(root, a[i]);
    }
    int query, data;
    struct Node *result = NULL;

    while (query != -1)
    {
        printf("\n\n------- RB TREE --------\n");
        printf("\n1. Insert");
        printf("\n2. Delete");
        printf("\n3. Search");
        printf("\n4. Preorder");
        printf("\n5. Delete Min Element");
        printf("\n-1. EXIT");
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &query);

        switch (query)
        {
        case 1:
            printf("\nEnter data: ");
            scanf("%d", &data);
            root = insert(root, data);
            break;

        case 2:
            printf("\nEnter data: ");
            scanf("%d", &data);
            result = search(root, data);
            if (result == NULL)
            {
                printf("\nNode not found!");
            }
            else
                root = delete (root, data);
            break;

        case 3:
            printf("\nEnter data: ");
            scanf("%d", &data);
            result = search(root, data);
            if (result == NULL)
            {
                printf("\nNode not found!");
            }
            else
            {
                printf("\n Node found");
            }
            break;
        case 4:

            if (!root)
                printf("The tree is empty!");
            else
                preorder(root);

            break;
        case 5:

            result = root;
            result = findMin(result);
            int val = result->key;
            printf("The minimum element is : %d\n", val);
            root = delete (root, val);

            break;
        case -1:
            printf("\nProgram Terminated\n");
            return 1;

        default:
            printf("\nInvalid Choice\n");
        }
    }

    return 0;
}
