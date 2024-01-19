#ifndef STRUCTS_H
#define STRUCTS_H


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
	struct package packages_in_possession[15];
	
};

struct postOfficeBox{
	
	int postOfficeBox_id;
	
	int isInUse;
	
	struct locker XS_locker[4];
	struct locker S_locker[5];
	struct locker M_locker[21];
	struct locker L_locker[10];
	struct locker XL_locker[2];
	
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

#endif
