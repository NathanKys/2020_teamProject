#pragma once

typedef enum { false, true } bool;

typedef struct Account {
	char id[12];
	char pw[16];
	char name[20];
	char nick[12];
	char email[30];
	int birth[6];
	int phone[11];
	unsigned int rec;
	bool lock;
	bool admin;
} Account;

void readAccountList(int line);