#include <stdio.h>
#include <stdlib.h>
const int INF = 1e9;
void restoreDown(int arr[], int size, int index, int k)
{
    int child[k + 1];
    while (1)
    {
        for (int i = 1; i <= k; i++)
            child[i] = ((k * index + i) < size) ? (k * index + i) : -1;

        int min_child = INF, min_child_index;
        for (int i = 1; i <= k; i++)
        {
            if (child[i] != -1 &&
                arr[child[i]] < min_child)
            {
                min_child_index = child[i];
                min_child = arr[child[i]];
            }
        }
        if (min_child == INF)
            break;
        if (arr[index] > arr[min_child_index])
        {
            int temp = arr[index];
            arr[index] = arr[min_child_index];
            arr[min_child_index] = temp;
        }
        index = min_child_index;
    }
}
void restoreUp(int arr[], int index, int k)
{
    int parent = (index - 1) / k;
    while (parent >= 0)
    {
        if (arr[index] < arr[parent])
        {
            int temp = arr[index];
            arr[index] = arr[parent];
            arr[parent] = temp;
            index = parent;
            parent = (index - 1) / k;
        }
        else
            break;
    }
}
void buildHeap(int arr[], int n, int k)
{
    for (int i = (n - 1) / k; i >= 0; i--)
        restoreDown(arr, n, i, k);
}
void insert(int arr[], int *n, int k, int key)
{
    arr[*n] = key;
    *n = *n + 1;
    restoreUp(arr, *n - 1, k);
}
void reduceKey(int arr[], int *n, int k, int *i, int key)
{
    if (arr[*i] < key)
    {
        printf("\nNew key is greater than current key\n");
        return;
    }
    arr[*i] = key;
    restoreUp(arr, *i, k);
}
int extractMin(int arr[], int *n, int k)
{
    int min = arr[0];
    arr[0] = arr[*n - 1];
    *n = *n - 1;
    restoreDown(arr, *n, 0, k);
    return min;
}
void printArray(int n, int arr[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main()
{
    const int capacity = 5001;
    int arr[capacity];
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    FILE *fp = fopen("random_number.txt", "rb");
    fread(a, sizeof(int), n, fp);
    for (int i = 0; i < n; i++)
    {
        arr[i] = a[i];
    }
    buildHeap(arr, n, k);
    printf("Built Heap : \n");
    printArray(n, arr);
    printf("\ntype your query :\n");
    printf("1 -insertion\n");
    printf("2 -delete Min\n");
    printf("3 -reduce key\n");
    printf("4 -print array\n");
    printf("-1 -exit\n");
    int query;
    scanf("%d", &query);
    while (query != -1)
    {
        int key, index;
        if (query == 1)
        {
            scanf("%d", &key);
            insert(arr, &n, k, key);
            printf("\n\nHeap after insertion of %d: \n", key);
            printArray(n, arr);
        }
        else if (query == 2)
        {
            printf("\nExtracted min is %d", extractMin(arr, &n, k));
            printf("\n\nHeap after deleting  min: \n");
            printArray(n, arr);
        }
        else if (query == 3)
        {
            scanf("%d %d", &index, &key);
            reduceKey(arr, &n, k, &index, key);
            printf("\n\nHeap after reducing key: \n");
            printArray(n, arr);
        }
        else if(query==4)
        {
            printf("\nBuilt Heap:\n");
            printArray(n, arr);
        }
       else
	 {
	    printf("\nbad query..exiting\n");
	 }
       
        scanf("%d", &query);
    }
    return 0;
}