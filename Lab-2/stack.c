#include <stdio.h>
#include <stdlib.h>
struct linked_list
{
	int data;
	struct linked_list *next;
	struct linked_list *prev;
};
typedef struct linked_list node;
node *make_node(int val)
{
	node *temp;
	temp = calloc(1, sizeof(node));
	temp->data = val;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}
void insert_at_front(node **head, int val)
{
	node *to_insert = make_node(val);
	if (!(*head))
	{
		*head = to_insert;
		return;
	}
	(*head)->prev = to_insert;
	to_insert->next = *head;
	*head = to_insert;
}
void insert_at_back(node **head, int val)
{
	node *to_insert = make_node(val);
	if (!(*head))
	{
		*head = to_insert;
		return;
	}
	node *current = *head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = to_insert;
	to_insert->prev = current;
}
void delete_at_front(node **head)
{
	if (!(*head))
	{
		printf("Empty list.Please insert first\n");
		return;
	}
	node *to_delete = *head;
	(*head) = to_delete->next;
	(*head)->prev = NULL;
	free(to_delete);
}
void delete_at_back(node **head)
{
	if (!*head)
	{
		printf("Empty list.Please insert first\n");
		return;
	}

	node *current = *head;
	if (!current->next)
	{
		free(current);
		*head = NULL;
		return;
	}

	while (current->next)
	{

		current = current->next;
	}
	current->prev->next = NULL;
	free(current);
}

void delete_search_key(node **head, int key)
{
	if (!*head)
	{
		printf("Empty list.Please insert first\n");
		return;
	}
	node *current = *head;
	if (current->data == key)
	{
		delete_at_front(head);
		return;
	}
	while (current && current->data != key)
	{
		current = current->next;
	}
	if (!current)
	{
		printf("no such key found\n");
		return;
	}
	if (!current->next)
	{
		delete_at_back(head);
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	free(current);
}
void print_list(node *head)
{
	if (!head)
	{
		printf("Empty list.Please insert first\n");
		return;
	}

	while (head)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}
void print_list_from_back(node *head)
{
	if (!head)
	{
		printf("The list is empty.Please insert something to the list first\n");
		return;
	}

	node *current = head;
	while (current->next)
	{
		current = current->next;
	}
	while (current)
	{
		printf("%d ", current->data);
		current = current->prev;
	}
	printf("\n");
}
void free_list(node **head)
{
	node *current = *head;
	while (current != NULL)
	{
		node *temp = current->next;
		free(current);
		current = temp;
	}
	*head = NULL;
	printf("allocated memory deleted\n");
}
int main()
{
	/*printf("1 : insert at front\n");*/
	printf("1: Push \n");
	printf("2: pop \n");
	printf("3:  print stack\n");
	// printf("5: reverse traverse and print list\n");
	printf("4: delete the stack\n");
	printf("-1: to exit\n");
	node *head = malloc(sizeof(node));
	head = NULL;
	int query;
	scanf("%d", &query);
	while (query > 0 && query < 5)
	{
		if (query == 1)
		{
			printf("type the number you wish to push\n");
			int x;
			scanf("%d", &x);
			insert_at_back(&head, x);
		} /*
	   else if(query==2)
		 { printf("type the number you wish to insert at back\n");
			int x;
			scanf("%d",&x);
			insert_at_back(&head,x);
		 }*/
		else if (query == 2)
		{
			// printf("type the number you wish to delete from the list\n");
			// int x;
			// scanf("%d",&x);
			// delete_search_key(&head,x);
			delete_at_back(&head);
		}
		else if (query == 3)
		{
			print_list(head);
		}
		/*else if(query==5)
		  {
			 print_list_from_back(head);
		  }*/
		else if (query == 4)
		{
			free_list(&head);
		}
		scanf("%d", &query);
	}
	return 0;
}
