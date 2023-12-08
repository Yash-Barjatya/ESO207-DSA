#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int random_pivot(int lo,int hi)
{
   int pivot = (rand()%(hi-lo))+lo;
   return pivot;
}
void swap(int *a,int*b)
{
   int temp =*a;
   *a=*b;
   *b=temp;
}
void print_array(int a[],int n)
{
   for(int i=0;i<n;i++)
     {
	printf("%d ",a[i]);
     }
   printf("\n");
}
void quick_sort(int a[],int lo,int hi)
{
   if(lo>=hi)
     return;
   int pivot_pos=random_pivot(lo,hi);
   int pivot =a[pivot_pos];
   int i=lo;
   int j=hi;
   while(i<=j)
     {
	while(i<=hi&&a[i]<pivot)
	  i++;
	while(j>=lo&&a[j]>pivot)
	  j--;
	if(i<=j)
	  {
	     swap(&a[i],&a[j]);
	     i++;
	     j--;
	  }
     }
   quick_sort(a,lo,j);
   quick_sort(a,i,hi);
}
void merge_sort(int lo,int mid,int hi,int a[])
{
   int n1=mid-lo+1;
   int n2=hi-mid;
   int left_arr[n1];
   int right_arr[n2];
   for(int i=lo;i<=mid;i++)
     {
	left_arr[i-lo]=a[i];
     }
   for(int i=mid+1;i<=hi;i++)
     {
	right_arr[i-mid-1]=a[i];
     }
   int i=0;
   int j=0;
   int k=lo;
   while(i<n1&&j<n2)
     {
	if(left_arr[i]>right_arr[j])
	  {
	     a[k]=right_arr[j];
	     j++;
	     k++;
	  }
	else
	  {
	     a[k]=left_arr[i];
	     i++;
	     k++;
	  }
     }
   while(i<n1)
     {
	a[k]=left_arr[i];
	i++;
	k++;
     }
   while(j<n2)
     {
	a[k]=right_arr[j];
	j++;
	k++;
     }
}
void merge(int a[],int n)
{
   int grp=n/2;
   int item =2;
   while(grp)
     {
	for(int i=0;i<grp;i++)
	  {
	     int left=i*item;
	     int right= (i+1)*item-1;
	     if(right>n-1)
	       right=n-1;
	     int mid=(left+right)/2;
	     merge_sort(left,mid,right,a);
	     if((i==grp-1)&&n%item)
	       {
		  right=n-1;
		  mid=(i+1)*item-1;
		  merge_sort(left,mid,right,a);
	       }
	  }
	item*=2;
	grp/=2;
     }
}
void merge_rec(int lo,int hi,int a[])
{
   if(lo>=hi)
     {
	return;
     }
   int mid=(lo+hi)/2;
   merge_rec(lo,mid,a);
   merge_rec(mid+1,hi,a);
   merge_sort(lo,mid,hi,a);
}
int main()
{
   clock_t t;
   FILE *fp=fopen("random_number.txt","rb");
   int n,query;
   scanf("%d",&n);
   int a[n];
   fread(a,sizeof(int),n,fp);
   fclose(fp);
   printf("\nEnter your query:\n");
   printf("1 : Quick sort\n");
   printf("2 : Merge sort\n");
   printf("3 : Merge sort(recursive)\n");
   scanf("%d",&query);
   printf("\n Before sorting\n");
   print_array( a, n);
	t=clock();
	printf("\n After sorting \n");
	if(query==1)
	  {
	     printf("using quick sort\n");
	     quick_sort(a,0,n-1);
	  }
	else if(query==2)
	  {
	     printf("using merge sort\n");
	     merge(a,n);
	  }
        else if(query==3)
          {
	     printf("using recursive merge sort\n");
	     merge_rec(0,n-1,a);
	  }
        else
          {
	     printf(" Wrong input provided, exiting\n");
	     return 0;
	  }
   t=clock()-t;
   print_array(a,n);
   double time_taken =((double)t)/CLOCKS_PER_SEC;
   printf("\n time taken =%f sec\n\n",time_taken);
   return 0;
}

	
   
	
	
	     
