#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#define MAX_LINE_LENGTH 130
Account inputAccount(int line)
{
	FILE* fp;
	fp = fopen("./accountlist.txt", "r");
	if (fp == NULL)
	{
		printf("파일 입출력 실패.\n");
		exit(1);
	}
	char temp[MAX_LINE_LENGTH];
	int lineCounter = 1;
	while (lineCounter != line) {
		fgets(temp, MAX_LINE_LENGTH, fp);
		lineCounter++;

	}

	Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0, 0 };
	int i = 0;
	while (true) {
		a.id[i] = fgetc(fp);
		if (a.id[i] == ',') { a.id[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.pw[i] = fgetc(fp);
		if (a.pw[i] == ',') { a.pw[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.name[i] = fgetc(fp);
		if (a.name[i] == ',') { a.name[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.nick[i] = fgetc(fp);
		if (a.nick[i] == ',') { a.nick[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.email[i] = fgetc(fp);
		if (a.email[i] == ',') { a.email[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		int temp = fgetc(fp) - 48;
		if (temp != -4)
		{
			a.birth[i] = temp; i++;
		}
		else { i = 0; break; }
	}
	while (true) {
		int temp = fgetc(fp) - 48;
		if (temp != -4) { a.phone[i] = temp; i++; }
		else { i = 0; break; }
	}

	fscanf(fp, "%d", &a.rec);
	fgetc(fp);
	a.lock = (fgetc(fp) - 48);
	fgetc(fp);
	a.admin = (fgetc(fp) - 48);

	fclose(fp);

	return a;
}
int selectMenu() {
	int number;
	printf("1.이전 페이지 ");
	printf("2.다음 페이지 ");
	printf("3.뒤로가기 ");
	printf("4.번호입력\n");

	scanf("%d", &number);
	
	return number;
}
void returnAccount(Account temp) {
	int number;
	system("cls");
	printf("			사용자 정보 조회\n");
	printf("=================================================================================\n");
	printf("	아이디		닉네임			이메일			생년월일\n");
	printf("=================================================================================\n");
	printf("%12s	%12s	%30s		", temp.id, temp.nick, temp.email);
	for (int i = 0; i < sizeof(temp.birth) / sizeof(int); i++) {
		printf("%d", temp.birth[i]);
	}
	printf("\n");
	printf("1.쪽지 보내기");
	printf("2.뒤로가기\n");

	scanf("%d", &number);
	switch (number)
	{
	case 1:
		break;
	case 2:
		system("cls");
		showUserList(0);
	default:
		break;
	}
}
void showUserList(int page) {
	int number = 0;
	int num = 0;
	Account temp[10];
	for (int i = 0; i < 10; i++) {
		temp[i] = inputAccount(i + 1 + page);
	}
	for (int i = 0; i < 10; i++) {
		printf("%d. %12s (%d)\n", i, temp[i].id, temp[i].rec);
	}
	number = selectMenu();

	switch (number)
	{
	case 1:
		if(page>0)
			system("cls");
			showUserList(page - 10);
		break; 
	case 2:
		system("cls");
		showUserList(page + 10);
		break;
	case 3:
		break;
	case 4:
		
		printf("열람할 계정의 아이디 번호를 입력하세요.(0~9)\n");
		printf(">");
		scanf("%d", &num);
		if (num>=0 &&  num<=9)
			returnAccount(temp[num]);
		break;
	default:
		break;
	}

}
