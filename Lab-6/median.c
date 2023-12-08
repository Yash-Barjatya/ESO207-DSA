#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void print_arr(int n, int a[n])
{

    for (int j = 0; j < n; j++)
    {
        printf("%d ", a[j]);
    }
    printf("\n");
}
void insertionsort(int a[], int lo, int hi)
{
    for (int i = lo; i <= hi; i++)
    {
        int j = i;
        while (j > lo && a[j] < a[j - 1])
        {
            if (a[j] < a[j - 1])
            {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
            j--;
        }
    }
}
int find_median(int a[], int n, int k)
{
    if (n <= 5)
    {
        insertionsort(a, 0, n - 1);
        return a[k];
    }
    int items = 5;
    int grp = n / 5 + n % 5;
    int m[grp];// to store median of grp
    int m_size = 0;
    for (int i = 0; i < grp; i++)
    {
        int st = i * items;
        int end = (i + 1) * items - 1;
        if (end > n - 1)
            end = n - 1;
        insertionsort(a, st, end);
        m[m_size] = a[(st + end) / 2];
        m_size++;
    }
   // median of median
    int mm =0;
     mm=find_median(m, m_size, m_size / 2);
    int s1[n], s2[n], s3[n];
    int s1_size = 0, s2_size = 0, s3_size = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < mm)
        {
            s1[s1_size] = a[i];
            s1_size++;
        }
        else if (a[i] > mm)
        {
            s3[s3_size] = a[i];
            s3_size++;
        }
        else
        {
            s2[s2_size] = a[i];
            s2_size++;
        }
    }
    if (s1_size >= k)
    {
        return find_median(s1, s1_size, k);
    }
    else if (s1_size + s2_size >= k)
    {
        return mm;
    }
    else
    {
        return find_median(s3, s3_size, k - s1_size - s2_size);
    }
}
int main()
{
    int n,k;
    scanf("%d", &n);
    clock_t t;
   int a[n];
    FILE *fp = fopen("random_number1.txt", "rb");
    fread(a, sizeof(int), n, fp);
   fclose(fp);
   /* 
   for(int i=0;i<n;i++)
     scanf("%d",&a[i]);
    */
    print_arr(n, a);
    t = clock();
    k=n/2-1;
    printf("\n median : %d\n", find_median(a, n, k));
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("\ntime taken = %f sec\n", time_taken);
    return 0;
}