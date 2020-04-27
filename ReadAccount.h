#pragma once

typedef enum { false, true } bool;

typedef struct Account {
	char id[13];	//12+\0
	char pw[19];	//16+\0
	char name[21];	//한글10+\n
	char nick[25];	//한글12+\0
	char email[21];	//20+\0
	int birth[7];	//6+\0
	int phone[12];	//11+\0
	unsigned int rec;
	bool lock;
	bool admin;
} Account;

Account readAccountInfo(int line);