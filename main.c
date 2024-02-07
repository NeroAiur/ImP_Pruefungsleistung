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
#include ".\headers\output.h"
#include ".\headers\package_ops.h"

/*number of characters in X/Y for UI*/
#define screenCharX 38
#define screenCharY 36

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
int readIn();
void getCharPositions();
void refreshScreen();
void writeToTextBuffer(int lockerIndex, int positionIndex,char);

/*Queue for transaction*/
struct listAdress transactionQueue; /* global variable - pointer to head node.*/
int package_index=0;

/*Queue in front of the poBox*/
struct listAdress customerQueue;
int customerQueueIndex;

struct position textPosition[42];
int positionIndex=0;

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
		
		drawScreen();
		
		Sleep(1000);
		
		if(kbhit()){
			
			InputChar= toupper(getch());
			
			switch (InputChar){
				
				case 'T':	if(	iterationsPerStep==10) {iterationsPerStep=100;
							}else{iterationsPerStep=10;}	
							break;
							
				case 'A': return 0;
							
				case 'P': while(TRUE){if(kbhit()){
											InputChar= toupper(getch());
											Sleep(50);
											if(InputChar=='P'){break;};
						  }};
				
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
	
	int i=0;
	
	readIn();
	
	drawScreen();
	
	getCharPositions();
	
	
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
	
	for(i=0;i<(sizeof(poBox.lockers)/sizeof(poBox.lockers[0])); i++){

		poBox.lockers[i].isEmpty=TRUE;
		
		if(i<4){
			poBox.lockers[i].size=XS_size;
		}
		if((4<=i)&&(i<9)){
			poBox.lockers[i].size=S_size;
		}
		if((9<=i)&&(i<31)){
			poBox.lockers[i].size=M_size;
		}
		if((31<=i)&&(i<40)){
			poBox.lockers[i].size=L_size;
		}
		if(40<=i){
			poBox.lockers[i].size=XL_size;
		}
		/*
		printf("Locker Size: %d Index: %d",poBox.lockers[i].size,i);
		printf("\n");*/
		
	}
	

	
	return 0;
	
}



void getCharPositions(){
	
	int x,y;
	
	for(x=0; x<screenCharX-11; x++){

		for(y=0; y<screenCharY; y++){
			
			if(pseudoGrafix[x][y]=='#'){
				
				textPosition[positionIndex].x=x;
				textPosition[positionIndex].y=y;
				textPosition[positionIndex].size=pseudoGrafix[x-1][y+1];
				
				if(textPosition[positionIndex].size=='+'){
					textPosition[positionIndex].size='K';
				}
				
				positionIndex++;
				
			}
			
		}
		
	}
	
	return;
}



void refreshScreen(){
	
	int mainIndex,XSIndex=0,SIndex=0,MIndex=0,LIndex=0,XLIndex=0;
	
	for(mainIndex=0; mainIndex<=42; mainIndex++){

		switch(textPosition[mainIndex].size){
			
			case 'K': 	if(poBox.lockers[XSIndex].isEmpty==TRUE){
							writeToTextBuffer(XSIndex,mainIndex,'e');
							XSIndex++;
						}else{
							writeToTextBuffer(XSIndex,mainIndex,'f');
						};
						
						break;
						
			case 'S': 	if(poBox.lockers[4+SIndex].isEmpty==TRUE){
							writeToTextBuffer(SIndex,mainIndex,'e');
							SIndex++;
						}else{
							writeToTextBuffer(SIndex,mainIndex,'f');
						};		
						
						break;
						
			case 'M': 	if(poBox.lockers[9+MIndex].isEmpty==TRUE){
							writeToTextBuffer(MIndex,mainIndex,'e');
							MIndex++;
						}else{
							writeToTextBuffer(MIndex,mainIndex,'f');
						};
						
						break;
						
			case 'L': 	if(poBox.lockers[31+LIndex].isEmpty==TRUE){
							writeToTextBuffer(LIndex,mainIndex,'e');
							LIndex++;
						}else{
							writeToTextBuffer(LIndex,mainIndex,'f');
						};	
							
						break;	
						
			case 'X': 	if(poBox.lockers[40+XLIndex].isEmpty==TRUE){
							writeToTextBuffer(XLIndex,mainIndex,'e');
							XLIndex++;
						}else{
							writeToTextBuffer(XLIndex,mainIndex,'f');
						};		
						break;						
		
		}
		
	}
	return;
}



void writeToTextBuffer(int lockerIndex, int positionIndex, char stringToPut){
	
	char buffer[4];
	int i;
	
	if(textPosition[positionIndex].size=='K'){
		switch(stringToPut){
		case 'e': pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y]='e'; break;
		case 'f': pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y]='f'; break;
		}
		
		return;
	}
	
	switch(stringToPut){
		case 'e': buffer[0]='l'; buffer[1]='e'; buffer[2]='e'; buffer[3]='r'; break;
		case 'f': buffer[0]=' '; buffer[1]='F'; buffer[2]='d'; buffer[3]=' '; break;
		
	}
	
	for(i=0;i<4;i++){
		
		pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y+i]=buffer[i];
		
	}
	
	return;
}



void drawScreen(){
	
	int x,y=0;
	
	system("cls");
	
	refreshScreen();
	
	for(x=0; x<screenCharX-11; x++){

		for(y=0; y<screenCharY; y++){
			
			printf("%c", pseudoGrafix[x][y]);
			
		}
		
		printf("\n");
		
	}
	
	return;
	
}



int readIn(){
	
	FILE *file;
	int x,y;
	
	char buffer[screenCharX];
	
	file = fopen("UI.txt","r");
	
	
	for(x=0; x<screenCharX; x++){
		
		fgets(buffer,screenCharX,file);
		
		for(y=0; y<screenCharY; y++){
			
			pseudoGrafix[x][y]=buffer[y];
			
		}
		
	}
	
	return 0;
	
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
		newPackage.sender_id= rand()%249+1;
		newPackage.recipient_id= rand()%249+1; /*Todo: sender/reciever cant be the same id*/
		
		packageSize=rand()%5+1;
		
		switch(packageSize){
			
			case 1: packageSize = XS_size; break;
			case 2: packageSize = S_size; break;
			case 3: packageSize = M_size; break;
			case 4: packageSize = L_size; break;
			case 5: packageSize = XL_size; break;
			
		}
		
		newPackage.size=packageSize;
		
		transactionQueue.headAdress = InsertAtTail(newPackage,transactionQueue);
		transactionQueue.length++;
		
		return 1;
		
	}
	
	return 0;
	
}



int queueCustomers(){
	

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
		poBox= inputPackage(temp,poBox);
		printf("Package %d von %d zu %d mit Gewicht %d",temp.package_id,temp.sender_id,temp.recipient_id,temp.size);
		printf("\n");
		customerQueue.length--;
		customerQueue.headAdress= dequeue(customerQueue);
	
	}

	
	return 0;
	
}

