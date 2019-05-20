/*
This code is created by Mehul Patni in c++
Last Updated Date : 20/05/2019

This is Implementation of Worst Fit strategy used in memory management of computers.
*/


#include<iostream>
using namespace std;

struct node{										// Defining Structures.
	int size;
	int mem;
	struct node *next;
};
struct node *head;
struct node *FreeList;
struct node *Allocated;

void SortedInsert(struct node** head, struct node* newNode);
void InsertSort(struct node** head);

void push(struct node **head, int a, int b){		// Inserting nodes into the Linked List.
	struct node *newnode = new node;
	newnode->mem = a;
	newnode->size = b;
	newnode->next = *head;
	*head = newnode;
}

void deleteNode(struct node **head_ref, int key) 	// Deleting node which have size == 0 i.e., you are allocating all the size of free list into allocated list. 
{ 
    struct node* temp = *head_ref, *prev; 
    if (temp != NULL && temp->size == key) 
    { 
        *head_ref = temp->next;   // Changed head 
        return; 
    } 
      while (temp != NULL && temp->size != key) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
    if (temp == NULL) return; 
    prev->next = temp->next; 
} 

void traversal(struct node *current)				// For traversal of all nodes present in the Linked List.
{
	struct node *ptr;
	ptr = current;
	cout<<"List is :-\n";
	while(ptr != NULL){
		cout<<ptr->mem<<" : "<<ptr->size<<" -> ";
		ptr = ptr->next;
	}
	cout<<" NULL\n";
}

// In the WorstFit, the partition is allocated which has highest memory block size.
void worstfit(struct node **temp1, struct node **temp2, int a)		// This is the First Fit Strategy which is implemented using Linked List.
{
	struct node *ptr1 = *temp1;
	struct node *ptr2 = *temp2;
	struct node *ptr3 = *temp1;
	int worstfit = -1;
	while(ptr1 != NULL){
		if(ptr1->size >= a){
			if(worstfit == -1)
				worstfit = ptr1->size;
			else if(worstfit < ptr1->size)
				worstfit = ptr1->size;
		}
		ptr1 = ptr1->next;
	}
	if(worstfit != -1){		
		while(ptr3 != NULL){
			if(ptr3->size == worstfit)
			{
				if(ptr3->size == a)
				{
					push(&ptr2,ptr3->mem,a);
				    InsertSort(&ptr2);
					deleteNode(temp1, ptr3->size);
				}
				else
				{
				    push(&ptr2,ptr3->mem,a);
				    InsertSort(&ptr2);
					ptr3->mem +=a;
					ptr3->size -= a;
				}
				break;
			}
			ptr3 = ptr3->next;
		}		
	cout<<"----------FREE LIST ------------";
	traversal(*temp1);
	
	cout<<"----------ALLOCATED LIST ------------";
	traversal(ptr2);
	}
	else{
		cout<<"Such huge Size cannot be accomodated\n";
	}
}

void SortedInsert(struct node** head, struct node* newNode)
{
	struct node dummy;
	struct node* current = &dummy;
	dummy.next = *head;

	while (current->next != NULL && current->next->mem < newNode->mem)
		current = current->next;

	newNode->next = current->next;
	current->next = newNode;
	*head = dummy.next;
}

void InsertSort(struct node** head)					// This is for sorting the Linked List in increasing order.
{
	struct node* result = NULL; 	// build the answer here
	struct node* current = *head;	// iterate over the original list
	struct node* next;

	while (current != NULL)
	{
		// tricky - note the next pointer before we change it
		next = current->next;

		SortedInsert(&result, current);
		current = next;
	}

	*head = result;
}

int main()
{
	char ch = 'y';
	int a,b;
	cout<<"----------FREE LIST ------------\nCan contain 0-512 memory block.\n";
	while(ch == 'y' || ch == 'Y'){					// Creating FreeList Linked List.
		cout<<"Enter the Starting address and the size of the node in the Free list --> ";
		cin>>a>>b;
		push(&FreeList,a,b);
		cout<<"Do you want to enter more nodes in the Free list?(y/n) ";
		cin>>ch;
	}
	struct node *head = FreeList;
    InsertSort(&head);
    traversal(head);
    int s;
	cout<<"----------ALLOCATED LIST ------------\n";
	struct node *ptr;
	ptr = head;
	if(head->mem != 0)					// Remaining memeory block is assigned to Allocated list.
		push(&Allocated,0,head->mem);	
	while(head->next != NULL){
		s = head->next->mem - head->mem -head->size;	
		if(s>0)
		{
			push(&Allocated, head->mem +head->size, head->next->mem - head->mem - head->size);
		}
		head = head->next;
		if(head->next == NULL && head->mem+head->size < 512)
			push(&Allocated,head->mem+head->size,512-(head->mem+head->size));
	}
	struct node *head1 = Allocated;
	InsertSort(&head1);
	traversal(head1);
	ch = 'y';
	cout<<"\n";
	while(ch == 'y' || ch == 'Y'){		// For allocating space from Freelist.
		cout<<"Enter the size of the node you want to be allocated in the memory --> ";
		cin>>a;  
		worstfit(&ptr, &head1, a);
		cout<<"Do you want to enter more nodes??";
		cin>>ch;
	}
	return 0;
}
