#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct linked_list
{
   int data;
   struct linked_list *prev;
   struct linked_list *next;
};
typedef struct linked_list node;
node *make_node(int val)
{
   node *temp;
   temp =calloc(1,sizeof(node));
   temp->data=val;
   temp->next=NULL;
   temp->prev=NULL;
   return temp;
}
void insert_at_back(node **head,int val)
{
   node* to_insert =make_node(val);
   if(!*head)
     {
	*head=to_insert;
	return;
     }
   node *current=*head;
   while(current->next)
     {
	current=current->next;
     }
   current->next=to_insert;
   to_insert->prev=current;
}
void print_list(node *head)
{
   while(head)
     {
	printf("%d ",head->data);
	head=head->next;
     }
}
void free_list(node**head)
{
   node *current =*head;
   while(current!=NULL)
     {
	node*temp=current->next;
	free(current);
	current=temp;
     }
   *head=NULL;
}
int main()
{
   clock_t start,end;
  // double cpu_time_used;
   int count,upper,i;
   printf("\ntype the count and upper bound\n");
   scanf("%d %d",&count,&upper);
   int a[count];
   FILE *fp =fopen("random_number.txt","rb");
   fread(a,sizeof(int),count,fp);
   fclose(fp);
   node* head[upper+1];
   printf("\n before sorting\n");
   for(i=0;i<count;i++)
     {
	printf("%d ",a[i]);
     }
   
   start=clock();
   for( i=0;i<upper+1;i++)
     { head[i]=NULL;}
   for( i=0;i<count;i++)
     {
	//node *to_insert =make_node(a[i]);
	insert_at_back(&head[a[i]],a[i]);
     }
   end=clock();
  double time_taken=((double) (end-start))/CLOCKS_PER_SEC;
   printf("\nafter sorting\n");
  
   for(i=0;i<upper+1;i++)
     {
	if(head[i])
	  print_list(head[i]);
     }
    
   
   for(i=0;i<upper+1;i++)
     {
	free_list(&head[i]);
     }
       printf("\ntime taken = %f seconds\n",time_taken);
   return 0;
}

   
	
	
   
   