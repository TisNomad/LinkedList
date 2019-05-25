#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct node_s{
	int data;
	struct node_s *next;
}node_t;

void display_list(node_t *headp){
	node_t *p;
	
	if (headp ==NULL)
		printf("The List is EMPTY !!!");
	else{
		p = headp;
		while(p != NULL){
			printf("%d", p->data);
			if(p->next != NULL)
				printf("-->");
			p = p->next;
		}
	}
	printf("\n");
}

int find_size_list(node_t *headp){
	node_t *p;
	int count = 0;
	
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

node_t *search_node(node_t *headp, int item){
	node_t *p;
	
	p = headp;
	
	while(p != NULL && p->data != item){
		p = p->next;
	}
	return p;
}

/////////////////////////////////CONVENIENT FUNCTION
node_t *Getnode(int item){
	node_t *node;
	node = (node_t*)malloc(sizeof(node_t));
	node->data = item;
	node->next = NULL;
	return node;
}

typedef struct{
	int item;
}Getnode_args;

node_t *var_Getnode(Getnode_args in){
    int item_out = in.item ? in.item : 0;
    return Getnode(item_out);
}
#define Getnode(...) var_Getnode((Getnode_args){__VA_ARGS__});
//////////////////////////////////////////////////////////////

void add_after(node_t *p, int item){
	node_t *newp;
	newp = Getnode(item);
	newp->next = p->next;
	p->next = newp;
}

node_t *add_beginning(node_t *headp, int item){
	node_t *newp = Getnode(item);
	newp->next = headp;
	return newp;
}

node_t *create_list(int ar[], int size){
	node_t *headp, *p;
	int i;
	headp = NULL;
	headp = add_beginning(headp, ar[0]);
	p = headp;
	for(i = 0; i < size; i++){
		add_after(p, ar[i]);
		p = p->next;
	}
	return headp;
}

node_t *create_list2(int ar[], int size){
	node_t *headp = NULL;
	int i;
	for(i = 0; i < size; i++){
		headp = add_beginning(headp, ar[i]);
	}
	return headp;
}

node_t *return_address(node_t *headp, int nitem){
	node_t *new_address = headp;
	int i = 0;
	
	for(i = 0; i < nitem; i++){
		if(new_address->next != NULL)
			new_address = new_address->next;
	}
	return new_address;
}

void delete_after(node_t *p, int *item){
	node_t *del;
	del = p->next;
	*item = del->data;
	p->next = del->next;
	free(del);
}

int main()
{
	int i = 0, temp, *ptr = (int*)malloc(sizeof(int) * 20);
	printf("Please enter intigers to fill linked list (0 to stop) : ");
	scanf("%d", &temp);
	while(temp != 0){
		ptr[i++] = temp;
		scanf("%d", &temp);
	}
	
	int ar_size = i;
	
	node_t *headp = NULL;
	for(i = ar_size; i > 0; i--){
		headp = add_beginning(headp, ptr[i-1]);
	}
	free(ptr);
	
	display_list(headp);

	printf("Do you want to delete anything ? (0 or 1 to reply) : ");
	int choice;
	scanf("%d", &choice);
	
	int order, *temp_item;
	
	switch(choice){
		case 0:
			break;
		case 1:
			printf("Which node ? (begins from 1) : ");
			scanf("%d", &order);
			node_t *del_address = return_address(headp, order - 1);
			delete_after(del_address, temp_item);
			display_list(headp);
			break;
	}
	
	return 0;
}
