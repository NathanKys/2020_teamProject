#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include "ReadAccount.h"
#define MAX_LINE_LENGTH 130

void checkSecondPw() {
	int adminSecondPw[6] = { 1, 3, 5, 7, 9, 0 };	//2차 비밀번호
	bool flag = 0;

	do {
		system("cls");
		flag = 0;
		printf("2차 비밀번호를 입력하세요.(숫자 6자리)");
		char input[7] = "";

		for (int i = 0; i < 6; i++) {
			scanf("%c", &input[i]);
		}

		char temp = ' ';
		scanf("%c", &temp);
		if (temp != '\n') {
			printf("비밀번호가 틀립니다.");
			system("pause");
			flag = 1;
		}
		else {
			for (int i = 0; i < 6; i++) {
				if ((input[i] - 48) != adminSecondPw[i]) {
					printf("비밀번호가 틀립니다.");
					system("pause");
					flag = 1;
					break;
				}
			}
		}

	} while (flag);

}

void readAccountInfo2(int startline, Account* a) {
	FILE* fp;
	fp = fopen("./accountlist.txt", "r");
	if (fp == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}
	char temp[MAX_LINE_LENGTH];
	int lineCounter = 1;

	while (lineCounter != startline) {

		fgets(temp, MAX_LINE_LENGTH, fp);
		lineCounter++;
	}
	if (feof(fp))
		return;
	//Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0, 0 };
	int i = 0;
	char t = ' ';

	while (true) {
		(*a).id[i] = fgetc(fp);
		if ((*a).id[i] == ',') { (*a).id[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		t = fgetc(fp);
		if (t == ',') { t = ' '; break; }
	}
	while (true) {
		(*a).name[i] = fgetc(fp);
		if ((*a).name[i] == ',') { (*a).name[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		(*a).nick[i] = fgetc(fp);
		if ((*a).nick[i] == ',') { (*a).nick[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		(*a).email[i] = fgetc(fp);
		if ((*a).email[i] == ',') { (*a).email[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		int temp = fgetc(fp) - 48;
		if (temp != -4)
		{
			(*a).birth[i] = temp; i++;
		}
		else { i = 0; break; }
	}
	while (true) {
		int temp = fgetc(fp) - 48;
		if (temp != -4) { (*a).phone[i] = temp; i++; }
		else { i = 0; break; }
	}

	fscanf(fp, "%d", &(*a).rec);
	fgetc(fp);
	(*a).lock = (fgetc(fp) - 48);
	fgetc(fp);
	(*a).admin = (fgetc(fp) - 48);

	fclose(fp);

}


void showAllAccountInfo(int num_account) {

	gotoxy(40, 1);
	printf("서비스 관리 계정 정보 열람");
	gotoxy(3, 3);
	printf("아이디");
	gotoxy(16, 3);
	printf("이름");
	gotoxy(37, 3);
	printf("닉네임");
	gotoxy(62, 3);
	printf("이메일 주소");
	gotoxy(93, 3);
	printf("생년월일");
	gotoxy(102, 3);
	printf("핸드폰 번호");


	int pageNum = 1;

	for (int i = 1; i <= 10; i++) {
		if ((pageNum - 1) * 10 + i <= num_account) {
			Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0, 0 };
			readAccountInfo2((pageNum - 1) * 10 + i, &a);
			gotoxy(3, 3 + (i * 2));	//아이디
			printf("%s", a.id);
			gotoxy(16, 3 + (i * 2));	//이름
			printf("%s", a.name);
			gotoxy(37, 3 + (i * 2));	//닉네임
			printf("%s", a.nick);
			gotoxy(62, 3 + (i * 2));	//이메일
			printf("%s", a.email);
			gotoxy(93, 3 + (i * 2));	//생년월일
			for (int j = 0; j < 6; j++) {
				printf("%d", a.birth[j]);
			}
			gotoxy(102, 3 + (i * 2));	//휴대폰 번호
			for (int j = 0; j < 11; j++) {
				printf("%d", a.phone[j]);
			}

		}
	}

	gotoxy(3, 25);
	printf("┌--------------------┐\n");
	gotoxy(3, 26);
	printf("│     이전 페이지    │\n");
	gotoxy(3, 27);
	printf("└--------------------┘\n");
	gotoxy(33, 25);
	printf("┌--------------------┐\n");
	gotoxy(33, 26);
	printf("│     다음 페이지    │\n");
	gotoxy(33, 27);
	printf("└--------------------┘\n");
	gotoxy(63, 25);
	printf("┌------------------┐\n");
	gotoxy(63, 26);
	printf("│     로그아웃     │\n");
	gotoxy(63, 27);
	printf("└------------------┘\n");
	gotoxy(93, 25);
	printf("┌------------------┐\n");
	gotoxy(93, 26);
	printf("│     번호 선택    │\n");
	gotoxy(93, 27);
	printf("└------------------┘\n");


	int triangle;
	char ch;

	triangle = 1;
	gotoxy(triangle, 26);
	printf("▶");
	while (1)
	{
		Sleep(1000);
		if (_kbhit())
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				switch (ch)
				{
					case LEFT:
						if (triangle > 1)
						{
							gotoxy(triangle, 26);
							printf("  ");
							triangle = triangle - 30;
							gotoxy(triangle, 26);
							printf("▶");
						}
						break;
					case RIGHT:
						if (triangle < 91)
						{
							gotoxy(triangle, 26);
							printf("  ");
							triangle = triangle + 30;
							gotoxy(triangle, 26);
							printf("▶");
						}
						break;
				}
			}
			if (ch == 13)
				break;
		}
	}

	if (triangle == 1)
		return 1;
	if (triangle == 31)
		return 2;
	if (triangle == 61)
		return 3;
	if (triangle == 91)
		return 4;

}
