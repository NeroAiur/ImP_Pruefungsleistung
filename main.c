#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include ".\headers\DVL.h" /*functions for doubly linked list*/
#include ".\headers\worker.h" /*functions for the worker of the post*/
#include ".\headers\structs.h"

#define screenCharX 40
#define screenCharY 30

/*Define package sizes/"weights"*/
#define XS_size 1
#define S_size 2
#define M_size 3
#define L_size 5
#define XL_size 8

#define TRUE 1
#define FALSE 0

void drawScreen();
int calculateTimeStep();
int Initialize();

struct listAdress transactionQueue; /* global variable - pointer to head node.*/

char pseudoGrafix[screenCharX][screenCharY];

struct customer customer_list[250];

int main(int argc, char *argv[]) {
	
	char InputChar;
	int iteration;
	
	Initialize();
	
	while(TRUE){
		
		calculateTimeStep();
		
		Sleep(500);
		
		if(kbhit()){
			
			InputChar= toupper(getch());
			
			switch (InputChar){
				
				case 'T': return 1;
				case 'P': return 2;
				case 'A': return 0;
				
			}
				
		}
		
		printf("%d",InputChar);
		printf("%d",iteration);
		iteration++;
		
	}
	
	return 0;
	
}

int Initialize(){
	
	int x,y,i=0;
	
	for(x=0; x<screenCharX; x++){

		for(y=0; y<screenCharY; y++){
			
			pseudoGrafix[x][y]='X';
			
		}
		
		
	}
	
	/*Initialize the customer id*/
	for(i=0;i<=(sizeof(customer_list)/sizeof(customer_list[0]));i++){
	
		customer_list[i].customer_id = i;
		
	}
	
	srand(time(0));
	
	transactionQueue.headAdress = NULL; /* empty list. set head as NULL. */
	
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

