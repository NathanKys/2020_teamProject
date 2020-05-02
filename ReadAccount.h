#pragma once

typedef enum { false, true } bool;

#define ID_MAXSIZE 12
#define PASSWORD_MAXSIZE 16
#define NAME_MAXSIZE 20
#define NICKNAME_MAXSIZE 24
#define EMAILADDRESS_MAXSIZE 30
#define BIRTHDAY_MAXSIZE 8
#define PHONENUMBER_MAXSIZE 11

typedef struct Account {
	char id[ID_MAXSIZE + 2];		//12+\0+1(길이 초과 확인용)
	char pw[PASSWORD_MAXSIZE+2];		//16+\0+1(길이 초과 확인용)
	char name[NAME_MAXSIZE+2];		//한글10+\n+1(길이 초과 확인용)
	char nick[NICKNAME_MAXSIZE + 2];	//한글12+\0+1(길이 초과 확인용)
	char email[EMAILADDRESS_MAXSIZE+2];	//20+\0+1(길이 초과 확인용)
	int birth[BIRTHDAY_MAXSIZE+2];		//6+\0+1(길이 초과 확인용)
	int phone[PHONENUMBER_MAXSIZE+2];	//11+\0+1(길이 초과 확인용)
	unsigned int rec;
	bool lock;
	bool changed;	//관리자에 의한 계정 변경 여부
} Account;

Account readAccountInfo(int line);
