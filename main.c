#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include ".\headers\DVL.h" /*functions for doubly linked list*/
#include ".\headers\worker.h" /*functions for the worker of the post*/

#define screenCharX 40
#define screenCharY 30

/*Define package sizes/"weights"*/
#define XS_size 1
#define S_size 2
#define M_size 3
#define L_size 5
#define XL_size 8

void drawScreen();
int calculateTimeStep();
int Initialize();

struct listAdress transactionQueue; /* global variable - pointer to head node.*/

struct package {
	
	int package_id;
	int package_size;
	int package_sender_id;
	int package_recipient_id;
	
};

struct locker {
	
	int locker_id;
	int locker_size;
	struct package locker_content;
	int locker_age;
	
};

struct customer {
	
	int customer_id;
	struct package packages_in_possession[256];
	
};

char pseudoGrafix[screenCharX][screenCharY];



int main(int argc, char *argv[]) {
	
	Initialize();
	
	drawScreen();
	
	transactionQueue.headAdress = NULL; /* empty list. set head as NULL. */

	transactionQueue.headAdress = InsertAtTail(2, transactionQueue);
	transactionQueue.headAdress = InsertAtTail(4, transactionQueue);
	transactionQueue.headAdress = InsertAtTail(6, transactionQueue);
	transactionQueue.headAdress = InsertAtTail(8, transactionQueue);
	printf("%d",transactionQueue.headAdress->data);
	transactionQueue.headAdress = dequeue(transactionQueue);
	printf("%d",transactionQueue.headAdress->data);
	Print(transactionQueue);
	
	return 0;
	
}

int Initialize(){
	
	int x,y=0;
	
	for(x=0; x<screenCharX; x++){

		for(y=0; y<screenCharY; y++){
			
			pseudoGrafix[x][y]='X';
			
		}
		
		
	}
	
	srand(time(0));
	
	return 0;
	
}

void drawScreen(){
	
	int x,y=0;
	
	system("cls");
	
	for(x=0; x<screenCharX; x++){

		for(y=0; y<screenCharY; y++){
			
			printf("%c", pseudoGrafix[x][y]);
			
		}
		
		printf("\n");
		
	}
	
	return;
	
}



int calculateTimeStep(){
	
	
	return 0;
}

