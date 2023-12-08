#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int power(int n,int k)
{
   int ans=1;
   for(int i=0;i<k;i++)
     {
	ans=ans*n;
     }

   return ans;
}

void generateRandoms(int lower, int upper, int count, int a[count][count])
{

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            int num = (rand() %
                       (upper - lower + 1)) +
                      lower;
            a[i][j] = num;
        }
    }
}
int main()
{
    int k, count, lower = 1, upper = 10;
    scanf("%d", &k);
    count = power(2, k);
    int a[count][count];
    int b[count][count];
    srand(time(0));
    generateRandoms(lower, upper, count, a);
    generateRandoms(lower, upper, count, b);
    FILE *fp = fopen("random_number.txt", "wb");
    fwrite(a, sizeof(int), count * count, fp);
    fwrite(b, sizeof(int), count * count, fp);
    fclose(fp);
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    return 0;
}