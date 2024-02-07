#ifndef STRUCTS_H
#define STRUCTS_H

struct package {
	
	int package_id;
	int size;
	int sender_id;
	int recipient_id;
	int isInternal_pickUpReady;
	
};

struct locker {
	
	int locker_id;
	int size;
	int isEmpty;
	struct package content;
	int fuse_time;
	
};

struct customer {
	
	int customer_id;
	struct package packages_in_possession[15];
	
};

struct postOfficeBox{
	
	int postOfficeBox_id;
	
	int isInUse;
	
	int timeInUse;
	
	struct locker lockers[42];
};

struct Node  {
	
	struct package data;
	struct Node* next;
	struct Node* prev;
	
};

struct listAdress {
	
	struct Node* headAdress;
	int length;
	
};

struct Time{	
	int days;
	int hour;
	int minute;
};

struct position{
	int x,y;
	char size;
};
#endif
