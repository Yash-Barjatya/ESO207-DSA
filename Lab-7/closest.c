#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
const int INF = 1e9;
int index_i, index_j;
int min_dist = INF;
float mn_dist = INF;
struct closest_pair_result
{
    int dist;
    int point1[2];
    int point2[2];
};
void print_points(int n, int (*points)[2])
{

       printf("\nThe points are : \n");
       for (int i = 0; i < n; i++)
     {


	        printf("{%d %d} ", points[i][0], points[i][1]);
     }

       printf("\n");
}
void merge(int lo, int mid, int hi, int to_sort, int (*a)[2])
{
    int n1 = mid - lo + 1;
    int n2 = hi - mid;
    int left_arr[n1][2];
    int right_arr[n2][2];
    for (int i = lo; i <= mid; i++)
    {
        left_arr[i - lo][0] = a[i][0];
        left_arr[i - lo][1] = a[i][1];
    }
    for (int i = mid + 1; i <= hi; i++)
    {
        right_arr[i - mid - 1][0] = a[i][0];
        right_arr[i - mid - 1][1] = a[i][1];
    }
    int i = 0;
    int j = 0;
    int k = lo;
    while (i < n1 && j < n2)
    {
        if (left_arr[i][to_sort] > right_arr[j][to_sort])
        {
            a[k][0] = right_arr[j][0];
            a[k][1] = right_arr[j][1];
            j++;
            k++;
        }
        else
        {
            a[k][0] = left_arr[i][0];
            a[k][1] = left_arr[i][1];
            i++;
            k++;
        }
    }
    while (i < n1)
    {
        a[k][0] = left_arr[i][0];
        a[k][1] = left_arr[i][1];
        i++;
        k++;
    }
    while (j < n2)
    {
        a[k][0] = right_arr[j][0];
        a[k][1] = right_arr[j][1];
        j++;
        k++;
    }
}
void merge_sort(int lo, int hi, int to_sort, int (*a)[2])
{
    if (lo >= hi)
    {
        return;
    }
    int mid = (lo + hi) / 2;
    merge_sort(lo, mid, to_sort, a);
    merge_sort(mid + 1, hi, to_sort, a);
    merge(lo, mid, hi, to_sort, a);
}
int distance(int p1[2], int p2[2])
{
    int x = p1[0] - p2[0];
    int y = p1[1] - p2[1];

    return x * x + y * y;
}
int normal_closest_pair(int n, int (*points)[2])
{
    min_dist = INF;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int dist = distance(points[i], points[j]);
            if (dist < min_dist)
            {
                min_dist = dist;
                index_i = i;
                index_j = j;
            }
        }
    }
    return min_dist;
}
int stripClosest(int n, int dist, int (*strip)[2])
{
    for (int i = 0; i < n; i++)
    {

        for (int j = i + 1; j < n && (strip[j][1] - strip[i][1]) < dist; j++)
        {
            if (distance(strip[i], strip[j]) < dist)
            {
                dist = distance(strip[i], strip[j]);
            }
        }
    }
    return dist;
}
struct closest_pair_result closest_pair(int n, int (*X_sort)[2], int (*Y_sort)[2])
{
    struct closest_pair_result result;
    if (n <= 3)
    {
        result.dist = normal_closest_pair(n, X_sort);
        result.point1[0] = X_sort[index_i][0];
        result.point1[1] = X_sort[index_i][1];
        result.point2[0] = X_sort[index_j][0];
        result.point2[1] = X_sort[index_j][1];
        return result;
    }
    int mid = n / 2;
    int mid_point[2];
    mid_point[0] = X_sort[mid][0];
    mid_point[1] = X_sort[mid][1];
    int Y_sort_left[mid][2];
    int Y_sort_right[n - mid][2];
    int left_count = 0, right_count = 0;
    for (int i = 0; i < n; i++)
    {
        if ((Y_sort[i][0] < mid_point[0] || (Y_sort[i][0] == mid_point[0] && Y_sort[i][1] < mid_point[1])) && left_count < mid)
        {
            Y_sort_left[left_count][0] = Y_sort[i][0];
            Y_sort_left[left_count][1] = Y_sort[i][1];
            left_count++;
        }
        else
        {
            Y_sort_right[right_count][0] = Y_sort[i][0];
            Y_sort_right[right_count][1] = Y_sort[i][1];
            right_count++;
        }
    }
  // printf("\n left points\n");
  // print_points(left_count,Y_sort_left);
    struct closest_pair_result left_result = closest_pair(mid, X_sort, Y_sort_left);
    struct closest_pair_result right_result = closest_pair(n - mid, X_sort + mid, Y_sort_right);
// printf("\n right points\n");
//print_points(right_count,Y_sort_right);
    if (left_result.dist <= right_result.dist)
    {
        result = left_result;
    }
    else
    {
        result = right_result;
    }
    int strip[n][2];
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(Y_sort[i][0] - mid_point[0]) < result.dist)
        {
            strip[count][0] = Y_sort[i][0];
            strip[count][1] = Y_sort[i][1];
            count++;
        }
    }
    int strip_dist = stripClosest(count, result.dist, strip);
    if (strip_dist < result.dist)
    {
        result.dist = strip_dist;
       
        for (int i = 0; i < count; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (distance(strip[i], strip[j]) == strip_dist)
                {
                    result.point1[0] = strip[i][0];
                    result.point1[1] = strip[i][1];
                    result.point2[0] = strip[j][0];
                    result.point2[1] = strip[j][1];
                    return result;
                }
            }
        }
       
    }

    return result;
}
int main()
{
    clock_t t;
    FILE *fp = fopen("random_number.txt", "rb");
    int n, query;
    scanf("%d", &n);
    int a[2 * n];
    fread(a, sizeof(int), 2 * n, fp);
    fclose(fp);
    int points[n][2];
    for (int i = 0; i < n; i++)
    {
        points[i][0] = a[2 * i];
        points[i][1] = a[2 * i + 1];
    }
    printf("1 : closest pair in O(n^2)\n");
    printf("2 : closest pair in O(nlogn)\n");
    printf("-1 : exit\n");
    scanf("%d", &query);
    while (query < 3 && query > 0)
    {
        print_points(n, points);
        if (query == 1)
        {
            t = clock();
            min_dist = normal_closest_pair(n, points);
            t = clock() - t;
            printf("\nThe closest pair is {%d %d} and{%d %d}\n", points[index_i][0], points[index_i][1], points[index_j][0], points[index_j][1]);
        }
        else if (query == 2)
        {
            
            int X_sort[n][2], Y_sort[n][2];
            for (int i = 0; i < n; i++)
            {
                X_sort[i][0] = points[i][0];
                X_sort[i][1] = points[i][1];
                Y_sort[i][0] = points[i][0];
                Y_sort[i][1] = points[i][1];
            }
            merge_sort(0, n - 1, 0, X_sort);
            merge_sort(0, n - 1, 1, Y_sort);
	  // print_points(n,Y_sort);
	   struct closest_pair_result result;
	   t=clock();
	   result = closest_pair(n, X_sort, Y_sort);
            t = clock() - t;
            min_dist = result.dist;
            printf("\nThe closest pair is {%d %d} and{%d %d}\n", result.point2[0], result.point2[1], result.point1[0], result.point1[1]);
        }
        else
        {
            break;
        }
        mn_dist = sqrt((float)min_dist);

        printf("\nThe min distance is %f\n", mn_dist);
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        printf("\ntime taken = %f sec\n", time_taken);
        scanf("%d", &query);
    }
    return 0;
}