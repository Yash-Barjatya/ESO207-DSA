#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
   clock_t t;
   
   int n;
   const int INF = 1e9;
   scanf("%d",&n);
   int a[n+2];
   int arr[n];
   FILE *fp = fopen("random_number.txt","rb");
   fread (arr,sizeof(int),n,fp);
   int i;
   for(i=1;i<=n;i++)
     {
	a[i]=arr[i-1];
     }
   
   a[0]=-INF;
   a[n+1]=INF;
   fclose(fp);
   printf("\before sorting\n");
   for(i=1;i<=n;i++)
     {
	printf("%d ",a[i]);
     }
  
   
   printf("\n");
  t=clock();
   int k=n,j;
   while(k)
     {
	for(i=k/2;i>k/4;i--)
	  {
	      j =i;
	     while(j<=n/2)
	       {
		  if(a[j]>a[2*j]||a[j]>a[2*j+1])
		    {
		       if(a[2*j]>a[2*j+1])
			 {
			    int temp = a[2*j+1];
			    a[2*j+1]=a[j];
			    a[j]=temp;
			    j=2*j+1;
			 }
		       else
			 {
			    int temp =a[2*j];
			    a[2*j]=a[j];
			    a[j]=temp;
			    j=2*j;
			 }
		    }
		  else
		    {
		       
		     j=2*j;
		    }
		  
	       }
	  }
	k=k/2;
     }
   k=n;
  // printf("\nafter heap\n");
   /*for(i =1;i<=n;i++)
       {
	  printf("%d ",a[i]);
       }
   */
   
   printf("\n after sorting\n");
   while(k>=1)
     {
        printf("%d ",a[1]);
	int temp =a[1];
	a[1]=a[k];
	a[k]=temp;
	k--;
	int j=1;
	while(j<=n/2)
	  {
	     if((2*j<=k &&a[j]>a[2*j])||(2*j+1<=k &&a[j]>a[2*j+1]))
	       {
		  if(2*j+1<=k&&a[2*j]>a[2*j+1])
		    {
		       int temp =a[2*j+1];
		       a[2*j+1]=a[j];
		       a[j]=temp;
		       j=2*j+1;
		    }
		  else
		    {
		       int temp = a[2*j];
		       a[2*j]=a[j];
		       a[j]=temp;
		       j=2*j;
		    }
	       }
	     else
	       {
		  break;
	       }
	  }
     }
   t=clock()-t;
   double time_taken =((double)t)/CLOCKS_PER_SEC;
   printf("\ntime taken= %f sec\n ",time_taken);
   printf("\n");
   return 0;
}

   