#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#include ".\headers\DVL.h"		   /*functions for the queue structs*/
#include ".\headers\structs.h"	   /*header file for all structs and custom datatypes*/
#include ".\headers\helperFunc.h"  /*time conversion + distribution functions*/
#include ".\headers\package_ops.h" /*Package in-/output*/

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

int Initialize();
int readIn();
int calculateTimeStep();
int generatePackage();
int queueCustomers();
int dequeueCustomers();
int poWorker();

void getCharPositions();
void drawScreen();
void refreshScreen();
void writeToTextBuffer(int lockerIndex, int positionIndex, char);

/*Queues for incoming and outbound transactions*/
struct listAdress transactionQueueIn; /* global variable - pointer to head node.*/
struct listAdress transactionQueueOut;
int package_index = 0;

/*Queue in front of the poBox*/
struct listAdress customerQueue;
int customerQueueIndex;

/*LUT for the UI text elements*/
struct position textPosition[43];
int positionIndex;

/*UI char buffer*/
char pseudoGrafix[screenCharX][screenCharY];

/*Time variable*/
int globalIteration = 0;
struct Time globalTime;

struct postOfficeBox poBox;

/*Multiplier table for day/night cycle*/
float timeMultiplier[24] = {0, 0, 0, 0, 0, 0.5, 1.0, 1.5, 2.0, 1.5, 1.0, 0.5, 1.0, 0.5, 0.5, 1.0, 1.5, 2.0, 1.5, 1.0, 1.0, 0.5, 0.5, 0.0};

int failedToDeliver = 0;
int triedToDeliver = 0;
int occupiedLockers[5] = {0, 0, 0, 0, 0};

int main(int argc, char *argv[])
{

	char inputChar;
	int iterationsPerStep = 10;

	Initialize();

	/*20160min = 14 Tage*/
	while (globalIteration <= 20160)
	{

		calculateTimeStep(iterationsPerStep);

		drawScreen();

		Sleep(1000);

		/*Look for an unbuffered keystroke*/
		if (kbhit())
		{

			inputChar = toupper(getch());

			/*T= Turbo, set the iterations of the for-loop in the simulation function up or down; A= Quit; P= basically the key detection loop, without doing anything else*/
			switch (inputChar)
			{

			case 'T':
				if (iterationsPerStep == 10)
				{
					iterationsPerStep = 100;
				}
				else
				{
					iterationsPerStep = 10;
				}
				break;

			case 'A':
				return 0;

			case 'P':
				while (TRUE)
				{
					if (kbhit())
					{
						inputChar = toupper(getch());
						Sleep(50);
						if (inputChar == 'P')
						{
							break;
						};
					}
				};
			}
		}
	}

	/*Print number of generated packages*/
	Print(transactionQueueIn);
	Print(transactionQueueOut);
	printf("Generierte Pakete: %d", transactionQueueIn.length + transactionQueueOut.length);

	return 0;
}

/*Initialize main variables*/
int Initialize()
{

	int i = 0;

	/*read the UI to the buffer and prepare the LUT for Ui manipulation*/
	readIn();

	getCharPositions();

	srand(time(0)); /*Initial seeding for random function*/

	/*Set up queue adresses and poBox*/
	transactionQueueIn.headAdress = NULL;
	transactionQueueIn.length = 0;

	transactionQueueOut.headAdress = NULL;
	transactionQueueOut.length = 0;

	customerQueue.headAdress = NULL;
	customerQueue.length = 0;

	poBox.postOfficeBox_id = 1;
	poBox.isInUse = FALSE;
	poBox.lastPackageDeposited = TRUE;

	/*Give each locker in the poBox struct its size*/
	for (i = 0; i < 43; i++)
	{

		poBox.lockers[i].isEmpty = TRUE;

		if (i < 4)
		{
			poBox.lockers[i].size = XS_size;
		}
		if ((4 <= i) && (i < 10))
		{
			poBox.lockers[i].size = S_size;
		}
		if ((10 <= i) && (i < 32))
		{
			poBox.lockers[i].size = M_size;
		}
		if ((32 <= i) && (i < 42))
		{
			poBox.lockers[i].size = L_size;
		}
		if (42 <= i)
		{
			poBox.lockers[i].size = XL_size;
		}
	}

	return 0;
}

/*Get text file, read it line by line into a temp buffer and write that to the UI buffer*/
int readIn()
{

	FILE *file;
	int x, y;

	char localBuffer[screenCharX];

	file = fopen("UI.txt", "r");

	for (x = 0; x < screenCharX; x++)
	{
		/*Gets an entire line, so transfered line by line*/
		fgets(localBuffer, screenCharX, file);

		for (y = 0; y < screenCharY; y++)
		{

			pseudoGrafix[x][y] = localBuffer[y];
		}
	}

	return 0;
}

/*Look for '#' in the UI buffer and write it's position to the buffer*/
void getCharPositions()
{

	int x, y;

	positionIndex = 0;

	for (x = 0; x < screenCharX - 11; x++) /*Nobody knows... Still*/
	{

		for (y = 0; y < screenCharY; y++)
		{

			if (pseudoGrafix[x][y] == '#')
			{

				textPosition[positionIndex].x = x;
				textPosition[positionIndex].y = y;
				textPosition[positionIndex].size = pseudoGrafix[x - 1][y + 1]; /*Size of the locker can be determined by looking at the character 1 line and one char to the right from its position; S,M,L;XL = X; XS = +;*/

				/*replace + with K*/
				if (textPosition[positionIndex].size == '+')
				{
					textPosition[positionIndex].size = 'K';
				}

				positionIndex++;
			}
		}
	}

	return;
}

/*Write values to the UI buffer*/
void refreshScreen()
{

	int mainIndex = 0, XSIndex = 0, SIndex = 0, MIndex = 0, LIndex = 0, XLIndex = 0, i;

	for (i = 0; i < 5; i++)
	{
		occupiedLockers[i] = 0;
	}

	for (mainIndex = 0; mainIndex < 43; mainIndex++)
	{

		switch (textPosition[mainIndex].size)
		{

		/*Determine the size of the locker in the UI and look at the status of a locker of the corrosponding size in the poBox struct*/
		case 'K':
			if (poBox.lockers[XSIndex].isEmpty == TRUE)
			{
				/*Call the subroutine with modifyer e = empty*/
				writeToTextBuffer(XSIndex, mainIndex, 'e');
				XSIndex++;
			}
			else
			{
				/*Call the subroutine with modifyer f = full*/
				writeToTextBuffer(XSIndex, mainIndex, 'f');
				occupiedLockers[0]++;
				XSIndex++;
			};

			break;

		case 'S':
			if (poBox.lockers[4 + SIndex].isEmpty == TRUE)
			{

				writeToTextBuffer(SIndex + 4, mainIndex, 'e');
				SIndex++;
			}
			else
			{

				writeToTextBuffer(SIndex + 4, mainIndex, 'f');
				occupiedLockers[1]++;
				SIndex++;
			};

			break;

		case 'M':
			if (poBox.lockers[9 + MIndex].isEmpty == TRUE)
			{

				writeToTextBuffer(MIndex + 9, mainIndex, 'e');
				MIndex++;
			}
			else
			{

				writeToTextBuffer(MIndex + 9, mainIndex, 'f');
				occupiedLockers[2]++;
				MIndex++;
			};

			break;

		case 'L':
			if (poBox.lockers[31 + LIndex].isEmpty == TRUE)
			{

				writeToTextBuffer(LIndex + 31, mainIndex, 'e');
				LIndex++;
			}
			else
			{

				writeToTextBuffer(LIndex + 31, mainIndex, 'f');
				occupiedLockers[3]++;
				LIndex++;
			};

			break;

		case 'X':
			if (poBox.lockers[41 + XLIndex].isEmpty == TRUE)
			{

				writeToTextBuffer(XLIndex + 41, mainIndex, 'e');
				XLIndex++;
			}
			else
			{

				writeToTextBuffer(XLIndex + 41, mainIndex, 'f');
				occupiedLockers[4]++;
				XLIndex++;
			};

			break;
		}
	}

	return;
}

/*Does what it says, can be expanded*/
void writeToTextBuffer(int lockerIndex, int positionIndex, char stringToPut)
{

	char localBuffer[4];
	int i;

	/*Handle case XS, since it only has one char space*/
	if (textPosition[positionIndex].size == 'K')
	{

		switch (stringToPut)
		{

		case 'e':
			pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y] = 'e';
			break;

		case 'f':
			pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y] = poBox.lockers[lockerIndex].fuse_time + '0';
			break;
		}

		return;
	}

	switch (stringToPut)
	{
	/*= leer*/
	case 'e':
		localBuffer[0] = 'l';
		localBuffer[1] = 'e';
		localBuffer[2] = 'e';
		localBuffer[3] = 'r';
		break;
	/*= ?d*/
	case 'f':
		localBuffer[0] = ' ';
		localBuffer[1] = poBox.lockers[lockerIndex].fuse_time + '0';
		localBuffer[2] = 'd';
		localBuffer[3] = ' ';
		break;
	}

	/*Write to the UI buffer*/
	for (i = 0; i < 4; i++)
	{

		pseudoGrafix[textPosition[positionIndex].x][textPosition[positionIndex].y + i] = localBuffer[i];
	}

	return;
}

/*Clear the screen, loop over every element of the UI buffer and print it out char by char*/
void drawScreen()
{

	int x, y = 0;

	float deliveryRate = 0.0, deliveryQuota = 0.0;

	system("cls");

	refreshScreen();

	for (x = 0; x < screenCharX - 11; x++)
	{

		for (y = 0; y < screenCharY; y++)
		{

			printf("%c", pseudoGrafix[x][y]);
		}

		printf("\n");
	}

	printf("\n");
	printf("Belegung:");
	printf("\n");
	printf("	XL: %d von 2", occupiedLockers[4]);
	printf("\n");
	printf("	 L: %d von 10", occupiedLockers[3]);
	printf("\n");
	printf("	 M: %d von 21", occupiedLockers[2]);
	printf("\n");
	printf("	 S: %d von 5", occupiedLockers[1]);
	printf("\n");
	printf("	XS: %d von 4", occupiedLockers[0]);

	printf("\n");
	printf("\n");

	printf("Kunden in der Warteschlange: %d", customerQueue.length);

	printf("\n");

	deliveryRate = (float)(package_index + 1) / (float)250;

	printf("Zustellrate: %.2f", deliveryRate);

	printf("\n");

	if (failedToDeliver != 0)
	{
		deliveryQuota = 1 - (float)failedToDeliver / (float)triedToDeliver;
	}

	printf("ZustellQuote: %.2f %d %d", deliveryQuota * 100, triedToDeliver, failedToDeliver);

	printf("\n");
	printf("\n");
	printf("(P)ause");
	printf("\n");
	printf("(T)urbo");
	printf("\n");
	printf("(A)bbruch");

	printf("\n");
	printf("\n");

	printf("%d : %d Tag %d", globalTime.hour, globalTime.minute, globalTime.days);

	return;
}

/*Main simulation loop, calls mostly subroutines*/
int calculateTimeStep(int iterationsPerStep)
{

	int iteration;
	struct Node *temp;

	/*Run this the number of times it is called by the main() function for (T)urbo*/
	for (iteration = 0; iteration < iterationsPerStep; iteration++)
	{

		/*Update time*/
		globalIteration++;
		globalTime = ConvertTime(globalIteration);

		/*Time skip 1-4*/
		if ((globalTime.hour == 1) && (globalTime.minute == 0))
		{

			iteration = 0;
			iterationsPerStep = 181;
		}

		/*Detect weekends: day mod 6 =saturday; day mod 7 =sunday; */
		if ((((globalTime.days % 6) == 0) || (globalTime.days % 7 == 0)) && (globalTime.days != 0))
		{

			if ((globalTime.hour == 14) && (globalTime.minute == 0) && (globalTime.days % 6 == 0))
			{

				poWorker();
			}
		}
		else
		{
			/*At midnight, tick down the counter for each package by one*/
			if ((globalTime.hour == 0) && (globalTime.minute == 0))
			{

				poBox = age_packages(poBox);
			}

			/*Post worker input/output packages at 10:30 and 18:30 ToDo: Wochenende*/
			if (((globalTime.hour == 10) && (globalTime.minute == 30)) || ((globalTime.hour == 18) && (globalTime.minute == 30)))
			{

				poWorker();
			}
		}

		/*Queue subroutines*/
		generatePackage();

		queueCustomers();

		/*Modify the inUse Flag*/
		if (poBox.timeInUse == 0)
		{

			poBox.isInUse = FALSE;
		}

		if (poBox.isInUse == FALSE)
		{

			dequeueCustomers();
		}
		else
		{

			poBox.timeInUse -= 1;
		}
	}

	return 0;
}

/*Generate a package, and fill the struct*/
int generatePackage()
{

	int magicNumber, fiftyFifty, tenPercent, temp;
	double packageSize;
	struct package newPackage;

	magicNumber = rand() % 10000; /*Rand_max is too small (0x7fff~32.600) for any more precision*/

	if (magicNumber <= 416)
	{ /*rounded chance x number of customers*/

		fiftyFifty = rand() % 2; /*Coinflip if in-/or outbound*/
		tenPercent = rand() % 10;

		newPackage.package_id = package_index + 1;
		package_index++;

		if (fiftyFifty == FALSE)
		{

			newPackage.sender_id = rand() % 249 + 1;
			newPackage.recipient_id = 300;

			if (tenPercent == FALSE)
			{

				do
				{

					temp = rand() % 249 + 1;

				} while (temp == newPackage.sender_id);

				newPackage.recipient_id = temp;
			}
		}
		else
		{

			newPackage.sender_id = 300;
			newPackage.recipient_id = rand() % 249 + 1;
		}

		/*Todo: in/in packages*/
		packageSize = (double)rand() / (double)RAND_MAX;

		packageSize = round(distribFunc2(packageSize)); /*Random size*/

		switch ((int)packageSize)
		{

		case 1:
			packageSize = XS_size;
			break;
		case 2:
			packageSize = S_size;
			break;
		case 3:
			packageSize = M_size;
			break;
		case 4:
			packageSize = L_size;
			break;
		case 5:
			packageSize = XL_size;
			break;
		}

		newPackage.size = packageSize;
		newPackage.isInternal_pickUpReady = FALSE;

		/*Insert in to the queue, depending on in- or outbound*/
		if (fiftyFifty == FALSE)
		{

			transactionQueueOut.headAdress = InsertAtTail(newPackage, transactionQueueOut);
			transactionQueueOut.length++;
		}
		else
		{
			transactionQueueIn.headAdress = InsertAtTail(newPackage, transactionQueueIn);
			transactionQueueIn.length++;
		}

		return 1;
	}

	return 0;
}

/*Take packages from the transaction queues and put them into the queue infront of the poBox*/
int queueCustomers()
{

	double queueChance;
	int coinFlip;
	struct Node *temp;

	queueChance = ((double)rand()/(double)RAND_MAX)*100;
	queueChance = queueChance * timeMultiplier[globalTime.hour];

	/*Random chance for someone to queue, modified by the table at the top, with coin flip for in-/outbound*/
	if (queueChance >= 95)
	{

		coinFlip = rand() % 2;

		if (coinFlip == TRUE)
		{

			if (transactionQueueOut.headAdress != NULL)
			{

				customerQueue.headAdress = InsertAtTail(transactionQueueOut.headAdress->data, customerQueue);
				customerQueue.length++;
				transactionQueueOut.headAdress = dequeue(transactionQueueOut);
			}
		}
		else
		{

			if (transactionQueueIn.headAdress != NULL)
			{

				temp = transactionQueueIn.headAdress;

				/*Go over every element in the inbound queue, until u find the first with the pickUp Flag TRUE*/
				while (temp->next != NULL)
				{

					if (temp->data.isInternal_pickUpReady == TRUE)
					{

						customerQueue.headAdress = InsertAtTail(transactionQueueIn.headAdress->data, customerQueue);
						customerQueue.length++;

						transactionQueueIn.headAdress = dequeue(transactionQueueIn);

						return 0;
					}

					temp = temp->next;
				}
			}
		}
	}

	return 0;
}

/*Take customers from the queue infront of the poBox and take/deposit the package*/
int dequeueCustomers()
{

	struct package temp;
	double randNumber, waitTime;

	if (customerQueue.headAdress != NULL)
	{

		temp = customerQueue.headAdress->data;

		randNumber = (double)rand() / (double)RAND_MAX;
		waitTime = round(distribFunc(randNumber));

		poBox.isInUse = TRUE;
		poBox.timeInUse = (int)(waitTime);

		/*Package inbound; take it*/
		if (customerQueue.headAdress->data.sender_id == 300)
		{

			poBox = output_package(poBox, customerQueue.headAdress->data.recipient_id);
		}

		/*Package outbound; deposit it*/
		if (customerQueue.headAdress->data.recipient_id == 300)
		{

			triedToDeliver++;
			poBox = input_package(temp, poBox);
			/*If the package could not be deposited, send to end of transaction queue*/
			if (poBox.lastPackageDeposited == FALSE)
			{

				transactionQueueOut.headAdress = InsertAtTail(customerQueue.headAdress->data, transactionQueueOut);
				failedToDeliver++;
			}
		}

		/*If its internal, from one resident to another*/
		if ((customerQueue.headAdress->data.recipient_id != 300) && (customerQueue.headAdress->data.sender_id != 300))
		{

			/*If the package was inspected by the poWorker; take it*/
			if (customerQueue.headAdress->data.isInternal_pickUpReady == TRUE)
			{

				poBox = output_package(poBox, customerQueue.headAdress->data.recipient_id);
			}
			else
			{
				/*If the package is not PickupReady it has to come from the outbound queue, since incoming packages cant be queued until their flag is set TRUE*/
				poBox = input_package(temp, poBox);
				triedToDeliver++;

				if (poBox.lastPackageDeposited == FALSE)
				{

					transactionQueueOut.headAdress = InsertAtTail(customerQueue.headAdress->data, transactionQueueOut);
					failedToDeliver++;
				}
				else
				{
					/*Put the package in to the inbound queue for sheduling pickup*/
					transactionQueueIn.headAdress = InsertAtTail(customerQueue.headAdress->data, transactionQueueIn);
				}
			}
		}

		/*Remove the Package/Customer from the Queue*/
		customerQueue.length--;
		customerQueue.headAdress = dequeue(customerQueue);

		Print(customerQueue);
		printf("\n");
	}

	return 0;
}

/*Subroutine to get the poWorker to take and input packages*/
int poWorker()
{

	struct Node *temp;
	/*Take all outbound packages out and use the station for 20 minutes*/
	poBox = output_package(poBox, 300);
	poBox.isInUse = TRUE;
	poBox.timeInUse = 10;

	temp = transactionQueueIn.headAdress;

	/*Go over every element in the inbound queue, put it into the poBox, set the flag for that package in the queue to pickup ready*/
	while (temp->next != NULL)
	{

		/*If the package is not internal and the pickUpReady flag is not set, it is not deposited*/
		if ((temp->data.sender_id == 300) && (temp->data.isInternal_pickUpReady == FALSE))
		{

			poBox = input_package(temp->data, poBox);
			triedToDeliver++;

			if (poBox.lastPackageDeposited == TRUE)
			{

				temp->data.isInternal_pickUpReady = TRUE;
			}
			else
			{
				failedToDeliver++;
			}
		}

		/*Validate internally send packages*/
		if (temp->data.sender_id != 300)
		{

			temp->data.isInternal_pickUpReady = TRUE;
		}

		temp = temp->next;
	}
}
