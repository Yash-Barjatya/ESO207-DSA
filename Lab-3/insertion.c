#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
   clock_t t;
   FILE *fp =fopen("random_number.txt","rb");
   int n;
   scanf("%d",&n);
   int a[n];
   fread(a,sizeof(int),n,fp);
   fclose(fp);
   int i;
   printf("\nbefore sorting\n");
   for(i=0;i<n;i++)
     {
	printf("%d ",a[i]);
     }
   
   t=clock();
   for(i=0;i<n;i++)
     {
	int j=i;
	while(j>0 &&a[j]<a[j-1])
	  {
	     if(a[j]<a[j-1])
	       {
		  int temp =a[j];
		  a[j]=a[j-1];
		  a[j-1]=temp;
	       }
	     j--;
	  }
     }
   t=clock()-t;
   printf("\n after sorting\n");
   for(i=0;i<n;i++)
     {
	printf("%d ",a[i]);
     }
   
   double time_taken=((double)t)/CLOCKS_PER_SEC;
   printf("time taken = %f sec",time_taken);
   return 0;
}

	

