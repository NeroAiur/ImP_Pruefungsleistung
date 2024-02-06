#ifndef STRUCTS_H
#define STRUCTS_H

struct package {
	
	int package_id;
	int package_size;
	int package_sender_id;
	int package_recipient_id;
	int package_isInternal_pickUpReady;
	
};

struct locker {
	
	int locker_id;
	int locker_size;
	int isEmpty;
	struct package locker_content;
	int locker_age;
	
};

struct customer {
	
	int customer_id;
	struct package packages_in_possession[15];
	
};

struct postOfficeBox{
	
	int postOfficeBox_id;
	
	int isInUse;
	
	struct locker [42];
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
