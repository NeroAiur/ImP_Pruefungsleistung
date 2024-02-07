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
struct listAdress transactionQueueIn; /* global variable - pointer to head node.*/
struct listAdress transactionQueueOut; 
int package_index=0;

/*Queue in front of the poBox*/
struct listAdress customerQueue;
int customerQueueIndex;

struct position textPosition[43];
int positionIndex;

char pseudoGrafix[screenCharX][screenCharY];

struct customer customer_list[250];

int globalIteration=0;
struct Time globalTime;

struct postOfficeBox poBox;

float timeMultiplier[24]={0,0,0,0,0,0.5,1.0,1.5,2.0,1.5,1.0,0.5,1.0,0.5,0.5,1.0,1.5,2.0,1.5,1.0,1.0,0.5,0.5,0.0};


int main(int argc, char *argv[]) {
	
	char InputChar;
	int iterationsPerStep=10;
	
	Initialize();
	
	while(globalIteration<=20160){

		calculateTimeStep(iterationsPerStep);
		
		drawScreen();
		
		printf("%d : %d Tag %d",globalTime.hour,globalTime.minute, globalTime.days);
		printf("\n");
		
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

		
	}
	
	Print(transactionQueueIn);
	Print(transactionQueueOut);	
	printf("Generierte Pakete: %d",transactionQueueIn.length);
	
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
	
	transactionQueueIn.headAdress = NULL; /* empty list. set head as NULL. */
	transactionQueueIn.length = 0;
	
	transactionQueueOut.headAdress = NULL; /* empty list. set head as NULL. */
	transactionQueueOut.length = 0;
	
	customerQueue.headAdress=NULL;
	customerQueue.length=0;
	
	poBox.postOfficeBox_id=1;
	poBox.isInUse=FALSE;
	
	for(i=0;i<43; i++){

		poBox.lockers[i].isEmpty=TRUE;
		
		if(i<4){
			poBox.lockers[i].size=XS_size;
		}
		if((4<=i)&&(i<10)){
			poBox.lockers[i].size=S_size;
		}
		if((10<=i)&&(i<32)){
			poBox.lockers[i].size=M_size;
		}
		if((32<=i)&&(i<42)){
			poBox.lockers[i].size=L_size;
		}
		if(42<=i){
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
	
	positionIndex=0;
	
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
	
	int mainIndex=0,XSIndex=0,SIndex=0,MIndex=0,LIndex=0,XLIndex=0;
	
	for(mainIndex=0; mainIndex<43; mainIndex++){

		switch(textPosition[mainIndex].size){
			
			case 'K': 	if(poBox.lockers[XSIndex].isEmpty==TRUE){
							writeToTextBuffer(XSIndex,mainIndex,'e');
							XSIndex++;
						}else{
							writeToTextBuffer(XSIndex,mainIndex,'f');
							XSIndex++;
						};
						
						break;
						
			case 'S': 	if(poBox.lockers[4+SIndex].isEmpty==TRUE){
							writeToTextBuffer(SIndex+4,mainIndex,'e');
							SIndex++;
						}else{
							writeToTextBuffer(SIndex+4,mainIndex,'f');
							SIndex++;
						};		
						
						break;
						
			case 'M': 	if(poBox.lockers[9+MIndex].isEmpty==TRUE){
							writeToTextBuffer(MIndex+9,mainIndex,'e');
							MIndex++;
						}else{
							writeToTextBuffer(MIndex+9,mainIndex,'f');
							MIndex++;
						};
						
						break;
						
			case 'L': 	if(poBox.lockers[31+LIndex].isEmpty==TRUE){
							writeToTextBuffer(LIndex+31,mainIndex,'e');
							LIndex++;
						}else{
							writeToTextBuffer(LIndex+31,mainIndex,'f');
							LIndex++;
						};	
							
						break;	
						
			case 'X': 	if(poBox.lockers[41+XLIndex].isEmpty==TRUE){
							writeToTextBuffer(XLIndex+41,mainIndex,'e');
							XLIndex++;
						}else{
							writeToTextBuffer(XLIndex+41,mainIndex,'f');
							XLIndex++;
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
		case 'f': pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y]=poBox.lockers[lockerIndex].fuse_time+'0'; break;
		}
		
		return;
	}
	
	switch(stringToPut){
		case 'e': buffer[0]='l'; buffer[1]='e'; buffer[2]='e'; buffer[3]='r'; break;
		case 'f': buffer[0]=' '; buffer[1]=poBox.lockers[lockerIndex].fuse_time+'0'; buffer[2]='d'; buffer[3]=' '; break;
		
	}
	
	for(i=0;i<4;i++){
		
		pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y+i]=buffer[i];
		
	}
	
	return;
}



void drawScreen(){
	
	int x,y=0;
	
	/*system("cls");*/
	
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
	struct Node* temp;
	
	for(iteration=0; iteration < iterationsPerStep; iteration++){
		
		globalIteration++;
		globalTime = ConvertTime(globalIteration);
		
		if((globalTime.hour==0)&&(globalTime.minute==0)){
			poBox=age_packages(poBox);
		}
		
		if((globalTime.hour==1)&&(globalTime.minute==0)){
			iteration=0;
			iterationsPerStep=181;
		}
		
		if(((globalTime.hour==10)&&(globalTime.minute==30))||((globalTime.hour==18)&&(globalTime.minute==30))){
			
			poBox = output_package(poBox,300);
			poBox.isInUse=TRUE;
			poBox.timeInUse=20;
			
			temp=transactionQueueIn.headAdress;
			
			while(temp->next!=NULL){
				
				poBox=input_package(temp->data,poBox);

				printf("Package deposited by post worker: %d Gewicht %d , von: %d zu: %d",  temp->data.package_id, temp->data.size, temp->data.sender_id, temp->data.recipient_id);
                printf("\n");
                
				temp->data.isInternal_pickUpReady=TRUE;
				temp=temp->next;
				
			}
			
		}
		
		generatePackage();
		queueCustomers();
		
		
		if(poBox.timeInUse==0){
			poBox.isInUse=FALSE;
		}
		if(poBox.isInUse==FALSE){
			dequeueCustomers();
		}else{poBox.timeInUse-=1;
		                printf("Time in use %d", poBox.timeInUse);
		                printf("\n");
		}
		
	}

	return 0;
	
}



int generatePackage(){
	
	int chance,inOrOut;
	int packageSize;
	struct package newPackage;
	
	chance=rand()%10000; /*Rand_max is too small (0x7fff~32.600) for any more precision*/
	
	if(chance<=416){ /*rounded chance x number of customers*/
		
		inOrOut=rand()%2;
		
		newPackage.package_id= package_index+1;
		package_index++;
		if(inOrOut==FALSE){
			newPackage.sender_id= rand()%249+1;
			newPackage.recipient_id=300;
		}else{
			newPackage.sender_id= 300;
			newPackage.recipient_id= rand()%249+1;
		}
		
 /*Todo: sender/reciever cant be the same id*/
		
		packageSize=rand()%5+1;
		
		switch(packageSize){
			
			case 1: packageSize = XS_size; break;
			case 2: packageSize = S_size; break;
			case 3: packageSize = M_size; break;
			case 4: packageSize = L_size; break;
			case 5: packageSize = XL_size; break;
			
		}
		
		newPackage.size=packageSize;
		newPackage.isInternal_pickUpReady=FALSE;
		
		if(inOrOut==FALSE){
				transactionQueueOut.headAdress = InsertAtTail(newPackage,transactionQueueOut);
				transactionQueueOut.length++;
		}else{	transactionQueueIn.headAdress = InsertAtTail(newPackage,transactionQueueIn);
				transactionQueueIn.length++;
		}

		
		return 1;
		
	}
	
	return 0;
	
}



int queueCustomers(){
	

	float chance;
	int coinFlip;
	struct Node* temp;
	
	chance = rand()%100;
	chance = chance*timeMultiplier[globalTime.hour];
	
	if(chance>=95){
		
		coinFlip = rand()%2;
		
		if(coinFlip==TRUE){
			
			if(transactionQueueOut.headAdress!=NULL){
				
					customerQueue.headAdress= InsertAtTail(transactionQueueOut.headAdress->data,customerQueue);
					customerQueue.length++;
					transactionQueueOut.headAdress = dequeue(transactionQueueOut);
		
			}

		}else{
			
			if(transactionQueueIn.headAdress!=NULL){
				
				temp=transactionQueueIn.headAdress;
				
				while(temp->next!=NULL){
					
					if(temp->data.isInternal_pickUpReady==TRUE){
						
						customerQueue.headAdress = InsertAtTail(transactionQueueIn.headAdress->data,customerQueue);
						customerQueue.length++;
						
						transactionQueueIn.headAdress = dequeue(transactionQueueIn);
						
						return 0;
						
					}
					
					temp=temp->next;
					
				}
				
			}
			
		}
		
	}
	

	return 0;
	
}



int dequeueCustomers(){
	
	struct package temp;
	
	if(customerQueue.headAdress!=NULL){	
		
		temp= customerQueue.headAdress->data;

		
		poBox.isInUse=TRUE;
		poBox.timeInUse=5;
		
		printf("Package %d von %d zu %d mit Gewicht %d",temp.package_id,temp.sender_id,temp.recipient_id,temp.size);
		printf("\n");
		
		if(customerQueue.headAdress->data.sender_id==300){
			poBox= output_package(poBox,customerQueue.headAdress->data.recipient_id);
			
		}else{	
			poBox= input_package(temp,poBox);
		}
		
		customerQueue.length--;
		customerQueue.headAdress= dequeue(customerQueue);
		Print(customerQueue);
		printf("\n");
	
	}

	
	return 0;
	
}

