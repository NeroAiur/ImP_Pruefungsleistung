#ifndef DVL_H
#define DVL_H

/* Doubly Linked List implementation */
#include<stdio.h>
#include<stdlib.h>
#include ".\structs.h"


/*Creates a new Node and returns pointer to it. */
struct Node* GetNewNode(struct package package) {
	struct Node* newNode
		= (struct Node*)malloc(sizeof(struct Node));
	newNode->data = package;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}


/*Inserts a Node at tail of Doubly linked list*/
struct Node* InsertAtTail(struct package package, struct listAdress head) {
	struct Node* temp = head.headAdress;
	struct Node* newNode = GetNewNode(package);
	if(head.headAdress == NULL) {

		head.headAdress = newNode;
		return head.headAdress;
	}
	while(temp->next != NULL) temp = temp->next; /* Go To last Node*/
	temp->next = newNode;
	newNode->prev = temp;
	return head.headAdress;
}


struct Node* dequeue(struct listAdress head){
	
	struct Node* temp = head.headAdress;
	struct Node* tempNext;
	
	if(temp==NULL){
		
		return NULL;
	
	}
	
	if(temp->next!= NULL){
		
		tempNext= temp->next;
		free(temp);
		tempNext->prev=NULL;
		
		return tempNext;
		
	}

	return NULL;
	
}


/*Prints all the elements in linked list in forward traversal order*/
void Print(struct listAdress head) {
	struct Node* temp = head.headAdress;
	printf("Transaction Queue: ");
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

#endif
