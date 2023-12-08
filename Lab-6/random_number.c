#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void generate_random(int count,int lower,int upper,int a[])
{ 
   int i;
   for( i=0;i<count;i++)
     {
	int num =(rand()%(upper-lower+1)) +lower;
	a[i]=num;
     }
}
int main()
{
   int count,lower,upper;
   scanf("%d %d %d",&count,&lower,&upper);
   int a[count];
   srand(time(0));
   generate_random(count,lower,upper,a);
   FILE *fp = fopen("random_number1.txt","wb");
   fwrite(a,sizeof(int),count,fp);
   fclose(fp);
   int i;
   for( i=0;i<count;i++)
     {
	printf("%d ",a[i]);
     }
   printf("\n");
   return 0;
}

   