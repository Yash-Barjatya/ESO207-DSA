#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
void print_array(int n,int a[n][n])
{
   for(int i=0;i<n;i++)
     {
	for(int j=0;j<n;j++)
	  {
	     printf("%d ",a[i][j]);
	  }
	printf("\n");
     }
}
void normal_matrix_mul(int n,int a[n][n],int b[n][n],int c[n][n])
{
   for(int i=0;i<n;i++)
     {
	for(int j=0;j<n;j++)
	  {
	     c[i][j]=0;
	     for(int k=0;k<n;k++)
	       {
		  c[i][j]+=a[i][k]*b[k][j];
	       }
	  }
     }
}
void add_matrices(int n,int add,int a[n][n],int b[n][n],int c[n][n])
{
   for(int i=0;i<n;i++)
     {
	for(int j=0;j<n;j++)
	  {
	     c[i][j]=a[i][j]+ add*b[i][j];
	  }
     }
}
void strassen_multiply_matrices(int n,int a[n][n],int b[n][n],int c[n][n])
{
   if(n==1)
     {
	c[0][0]=a[0][0]*b[0][0];
	return ;
     }
   n=n/2;// for partition(divide and conquer)
   int a11[n][n];
   int a12[n][n];
   int a21[n][n];
   int a22[n][n];
   int b11[n][n];
   int b12[n][n];
   int b21[n][n];
   int b22[n][n];
   for(int i=0;i<n;i++)
     {
	for(int j=0;j<n;j++)
	  {
	     a11[i][j]=a[i][j];
	     a12[i][j]=a[i][j+n];
	     a21[i][j]=a[i+n][j];
	     a22[i][j]=a[i+n][j+n];
	     b11[i][j]=b[i][j];
	     b12[i][j]=b[i][j+n];
	     b21[i][j]=b[i+n][j];
	     b22[i][j]=b[i+n][j+n];
	  }
     }
   int p[n][n];
   int q[n][n];
     int r[n][n];
     int s[n][n];
     int t[n][n];
     int u[n][n];
     int v[n][n];
   int dummy_mat1[n][n];// extra matrix for storing purpose
   int alpha[n][n];
   int beta[n][n];
   int gamma[n][n];
   int delta[n][n];
   int dummy2[n][n];
   int dummy1[n][n];
   int dummy3[n][n];
   int dummy4[n][n];
   int dummy5[n][n];
   int dummy6[n][n];
   int dummy7[n][n];
   int dummy8[n][n];
   int dummy9[n][n];
   int dummy10[n][n];
   int dummy11[n][n];
   int dummy12[n][n];
   int dummy13[n][n];
   int dummy14[n][n];
   add_matrices(n,-1,a12,a22,dummy1);
  add_matrices(n,1,b21,b22,dummy_mat1);
   strassen_multiply_matrices(n,dummy1,dummy_mat1,p);
   
   add_matrices(n,1,a11,a22,dummy2);
   add_matrices(n,1,b11,b22,dummy3);
   strassen_multiply_matrices(n,dummy3,dummy2,q);
   
   add_matrices(n,-1,a11,a21,dummy4);
   add_matrices(n,1,b11,b12,dummy5);
   strassen_multiply_matrices(n,dummy4,dummy5,r);

   add_matrices(n,1,a11,a12,dummy6);
   strassen_multiply_matrices(n,dummy6,b22,s);                                                                   
   
   add_matrices(n,1,a21,a22,dummy7);
   strassen_multiply_matrices(n,dummy7,b11,t);
   
   add_matrices(n,-1,b12,b22,dummy8);
   strassen_multiply_matrices(n,a11,dummy8,u);

   add_matrices(n,-1,b21,b11,dummy9);
   strassen_multiply_matrices(n,a22,dummy9,v);

   strassen_multiply_matrices(n,a11,b11,dummy10);
   strassen_multiply_matrices(n,a12,b21,dummy11);
   add_matrices(n,1,dummy10,dummy11,alpha);

   strassen_multiply_matrices(n,a21,b12,dummy12);
   strassen_multiply_matrices(n,a22,b22,dummy13);
   add_matrices(n,1,dummy12,dummy13,beta);
     /*
     add_matrices(n,1,u,q,beta);
      add_matrices(n,-1,beta,r,beta);
      add_matrices(n,-1,beta,t,beta);
   
   add_matrices(n,1,v,t,gamma);
   
   add_matrices(n,1,s,u,delta);
*/
  
   for(int i=0;i<n;i++)
     {
	for(int j=0;j<n;j++)
	  {
	     c[i][j]=alpha[i][j];
	    // c[i][j]=p[i][j]+q[i][j]-s[i][j]+v[i][j];
	     //c[i][j+n]=delta[i][j];
	     c[i][j+n]=s[i][j]+u[i][j];
	     
	     c[i+n][j]=v[i][j]+t[i][j];
	     
	     //c[i+n][j+n]=q[i][j]-r[i][j]+u[i][j]-t[i][j];
	     c[i+n][j+n]=beta[i][j];
	     
	  }
     }
   
}
int power(int n, int k)
{
   int ans=1;
   
   for(int i=0;i<k;i++)
     {
	ans=ans*n;
     }
return ans;
}

int main()
{
   clock_t t;
   int k,n;
   FILE *fp =fopen("random_number.txt","rb");
   scanf("%d",&k);
   n=power(2,k);
   int a[n][n];
   int b[n][n];
   int c[n][n];
   fread(a,sizeof(a),1,fp);
   fread(b,sizeof(b),1,fp);
   fclose(fp);
   printf("\n matrix a: \n");
   print_array(n,a);
   printf("\n matrix b: \n");
   print_array(n,b);
   printf("\ntype 1 : normal matrix multiplicaion\n");
   printf("\ntype 2: strassen matrix multiplication\n");
   int query;
   scanf("%d",&query);
   t=clock();
   if(query==1)
     {
	
	normal_matrix_mul(n,a,b,c);
     }
   else if(query==2)
     {
	strassen_multiply_matrices(n,a,b,c);
     }
   else
     {
	printf("\n please provide a valid query!!\n");
	return 0;
     }
   t=clock()-t;
   printf("matrix c: \n");
   print_array(n,c);
   double time_taken =((double)t)/CLOCKS_PER_SEC;
   printf("\n time taken= %f sec\n",time_taken);
   return 0;
}

   
		  
		  