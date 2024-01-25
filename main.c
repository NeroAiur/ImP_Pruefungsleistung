#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#include ".\headers\DVL.h" /*functions for doubly linked list*/
#include ".\headers\worker.h" /*functions for the worker of the post*/
#include ".\headers\structs.h"/*header file for all structs and custom datatypes*/
#include ".\headers\helperFunc.h"

/*number of characters in X/Y for UI*/
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

/* function primitives*/
void drawScreen();
int calculateTimeStep();
int generatePackage();
int queueCustomers();
int Initialize();
int dequeueCustomers();

/*Queue for transaction*/
struct listAdress transactionQueue; /* global variable - pointer to head node.*/
int package_index=0;

/*Queue in front of the poBox*/
struct listAdress customerQueue;
int customerQueueIndex;


char pseudoGrafix[screenCharX][screenCharY];

struct customer customer_list[250];

struct Time globalTime;

struct postOfficeBox poBox;

float timeMultiplier[24]={0,0,0,0,0,0.5,1.0,1.5,2.0,1.5,1.0,0.5,1.0,0.5,0.5,1.0,1.5,2.0,1.5,1.0,1.0,0.5,0.5,0.0};

int main(int argc, char *argv[]) {
	
	struct Time time;
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
							
				case 'A': return 0;
							
				case 'P': while(TRUE){if(kbhit()){
							InputChar= toupper(getch());
							Sleep(50);
							if(InputChar='P'){break;};
							}}; /*Todo*/
				
			}
				
		}
		
		globalTime = ConvertTime(iteration);
		time=globalTime;
		
		printf("%d : %d Tag %d",time.hour,time.minute, time.days);
		printf("\n");
		
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
	
	/*Initialize the customer id 0-250*/
	for(i=0;i<=(sizeof(customer_list)/sizeof(customer_list[0]));i++){
	
		customer_list[i].customer_id = i;
		
	}
	
	srand(time(0)); /*Initial seeding for random function*/
	
	transactionQueue.headAdress = NULL; /* empty list. set head as NULL. */
	transactionQueue.length = 0;
	
	customerQueue.headAdress=NULL;
	customerQueue.length=0;
	
	poBox.postOfficeBox_id=1;
	poBox.isInUse=FALSE;
	
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
		queueCustomers();
		
		if(poBox.isInUse==FALSE){
			dequeueCustomers();
		}
		
	}

	return 0;
	
}



int generatePackage(){
	
	int chance;
	int packageSize;
	struct package newPackage;
	
	chance=rand()%10000; /*Rand_max is too small (0x7fff~32.600) for any more precision*/
	
	if(chance<=416){ /*rounded chance x number of customers*/
		
		newPackage.package_id= package_index+1;
		package_index++;
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

int queueCustomers(){
	
	struct package temp;
	float chance;
	
	chance = rand()%100;
	chance = chance*timeMultiplier[globalTime.hour];
	
	if((chance>=95)&&(transactionQueue.headAdress!=NULL)){
		
		customerQueue.headAdress= InsertAtTail(transactionQueue.headAdress->data,customerQueue);
		customerQueue.length++;
		transactionQueue.headAdress = dequeue(transactionQueue);
			
	}

	
	return 0;
}

int dequeueCustomers(){
	
	struct package temp;
	if(customerQueue.headAdress!=NULL){	
	temp= customerQueue.headAdress->data;
	
	printf("Package %d von %d zu %d mit Gewicht %d",temp.package_id,temp.package_sender_id,temp.package_recipient_id,temp.package_size);
	printf("\n");
	customerQueue.length--;
	customerQueue.headAdress= dequeue(customerQueue);
	}

	
	return 0;
	
}

