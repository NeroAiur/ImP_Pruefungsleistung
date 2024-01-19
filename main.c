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
int generatePackage();
int Initialize();

struct listAdress transactionQueue; /* global variable - pointer to head node.*/
struct listAdress customerQueue; 

char pseudoGrafix[screenCharX][screenCharY];

struct customer customer_list[250];

int main(int argc, char *argv[]) {
	
	char InputChar;
	int iteration=0;
	int iterationsPerStep=10;
	
	Initialize();
	
	while(iteration<=20160){

		calculateTimeStep(iterationsPerStep);
		
		Sleep(50);
		
		if(kbhit()){
			
			InputChar= toupper(getch());
			
			switch (InputChar){
				
				case 'T':	if(	iterationsPerStep==10) {iterationsPerStep=100;
							}else{iterationsPerStep=10;}	
							break; /*Todo */
							
				case 'P': return 2; /*Todo*/
				case 'A': return 0;
				
			}
				
		}

		iteration= iteration + iterationsPerStep;
		
	}
	Print(transactionQueue);
	printf("Generierte Pakete: %d",transactionQueue.length);
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
	transactionQueue.length = 0;
	customerQueue.headAdress = NULL;
	customerQueue.length = 0;
	
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



int calculateTimeStep(int iterationsPerStep){
	
	int iteration;
	
	for(iteration=0; iteration < iterationsPerStep; iteration++){
		
		generatePackage();
		
		
	}

	return 0;
	
}



int generatePackage(){
	
	int chance;
	int packageSize;
	struct package newPackage;
	
	chance=rand()%10000; /*Rand_max is too small (0x7fff~32.600) for any more precision*/
	
	if(chance<=416){ /*rounded chance x number of customers*/
		
		newPackage.package_id= 1;
		newPackage.package_sender_id= rand()%249+1;
		newPackage.package_recipient_id= rand()%249+1; /*Todo: sender/reciever cant be the same id*/
		
		packageSize=rand()%5+1;
		
		switch(packageSize){
			case 1: packageSize = XS_size; break;
			case 2: packageSize = S_size; break;
			case 3: packageSize = M_size; break;
			case 4: packageSize = L_size; break;
			case 5: packageSize = XL_size; break;
		}
		
		newPackage.package_size=packageSize;
		
		transactionQueue.headAdress = InsertAtTail(newPackage,transactionQueue);
		transactionQueue.length++;
		
		return 1;
		
	}
	
	return 0;
	
}



