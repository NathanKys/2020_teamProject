#pragma once

typedef enum { false, true } bool;

typedef struct Account {
	char id[13];
	char pw[19];
	char name[21];
	char nick[13];
	char email[31];
	int birth[7];
	int phone[12];
	unsigned int rec;
	bool lock;
	bool admin;
} Account;

Account readAccountInfo(int line);