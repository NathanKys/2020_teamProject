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

	system("cls");
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


void showAllAccountInfo(int pageNum, int num_account) {

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

	for (int i = 1; i <= 10; i++) {
		if ((pageNum - 1) * 10 + i <= num_account) {
			Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0, 0 };
			readAccountInfo2((pageNum - 1) * 10 + i, &a);
			gotoxy(1, 3 + (i * 2));
			printf("%d", i - 1);
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
}

int selectAccountToManage() {

	bool flag = 0;
	int in = 0;
	do {
		flag = 0;
		for (int i = 0; i < 3; i++) {
			gotoxy(3, 25 + i);
			printf("                                                           ");
			printf("                                                           ");
		}
		gotoxy(3, 25);
		printf("관리할 계정 번호를 선택하세요.");
		char input = ' ';
		char temp = ' ';
		scanf("%c", &input);
		scanf("%c", &temp);

		in = input - 48;
		if (temp != '\n' || !(0 <= in && in <= 9)) {
			printf("잘못된 입력입니다. 숫자 하나만을 입력하세요.\n");
			system("pause");
			flag = 1;
		}

	} while (flag);

	return in;
}

int selectManageFunction() {

	gotoxy(35, 5);
	printf("선택한 계정에 대해 수행할 관리 기능을 선택하세요.");
	gotoxy(33, 10);
	printf("┌----------------------┐\n");
	gotoxy(33, 11);
	printf("│      닉네임 수정     │\n");
	gotoxy(33, 12);
	printf("└----------------------┘\n");
	gotoxy(63, 10);
	printf("┌------------------------┐\n");
	gotoxy(63, 11);
	printf("│    계정 잠금 및 해제   │\n");
	gotoxy(63, 12);
	printf("└------------------------┘\n");

	int triangle;
	char ch;

	triangle = 31;
	gotoxy(triangle, 11);
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
						if (triangle > 31)
						{
							gotoxy(triangle, 11);
							printf("  ");
							triangle = triangle - 30;
							gotoxy(triangle, 11);
							printf("▶");
						}
						break;
					case RIGHT:
						if (triangle < 61)
						{
							gotoxy(triangle, 11);
							printf("  ");
							triangle = triangle + 30;
							gotoxy(triangle, 11);
							printf("▶");
						}
						break;
				}
			}
			if (ch == 13)
				break;
		}
	}

	system("cls");
	switch (triangle) {
		case 31:
			return 1;
			break;
		case 61:
			return 2;
			break;
	}
}

void changeNick(char * nick) {


	char input[NICKNAME_MAXSIZE + 2];

	while (true) {
		system("cls");
		gotoxy(10, 5);
		printf("기존 닉네임: %s", nick);

		gotoxy(10, 7);
		printf("닉네임에는 한글, 영어, 숫자, 띄어쓰기를 사용할 수 있습니다.(최소2자~최대12자)\n");
		gotoxy(10, 8);
		printf("새로운 닉네임을 입력하세요: ");

		fgets(input, NICKNAME_MAXSIZE + 2, stdin);
		input[strcspn(input, "\n")] = 0;

		gotoxy(10, 9);

		if (strlen(input) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(input, NICKNAMECHECK)) {
			printf("이미 사용 중인 닉네임입니다.\n");
			system("pause");
			continue;
		}
		if (getLength(input) < 2 || getLength(input) > 12) {
			printf("닉네임은 한글, 영어, 숫자로 이루어진 2자~12자를 입력해야합니다.\n");
			system("pause");
			continue;
		}
		if (matchNickname(input)) {
			printf("닉네임 입력이 완료되었습니다.\n");
			gotoxy(10, 10);
			printf("변경 이후 닉네임: %s", input);
			system("pause");
			break;
		}
		else {
			printf("올바른 문자를 입력해주세요.\n");
			system("pause");
			continue;
		}

	}
}

void changeLock(char* id, bool* lock) {

	printf("선택한 계정: %s\n", id);
	printf("계정 잠금 여부: ");

	int triangle;
	char ch;

	triangle = 1;
	gotoxy(triangle, 6);
	printf("▶");

	if (lock) {
		printf("O");
		gotoxy(3, 5);
		printf("┌----------------------┐\n");
		gotoxy(3, 6);
		printf("│      잠금 해제      │\n");
		gotoxy(3, 7);
		printf("└----------------------┘\n");
		while (1)
		{
			Sleep(1000);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 13)
					break;
			}
		}
		printf("잠금 해제 처리되었습니다.");
	}
	else {
		printf("X");
		printf("O");
		gotoxy(3, 5);
		printf("┌----------------------┐\n");
		gotoxy(3, 6);
		printf("│      계정 잠금      │\n");
		gotoxy(3, 7);
		printf("└----------------------┘\n");
		while (1)
		{
			Sleep(1000);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 13)
					break;
			}
		}
		printf("계정 잠금 처리되었습니다.");
	}
	(*lock) = !lock;
}

void adminMenu(int num_account) {

	int pageNum = 1;
	int endPage = (num_account / 10) + 1;

	while (true) {

		showAllAccountInfo(pageNum, num_account);

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



		if (triangle == 1) {
			if (pageNum == 1) {
				system("cls");
				printf("더 이상 표시할 계정이 없습니다.");
				system("pause");
			}
			else {
				pageNum--;
			}
		}
		if (triangle == 31) {
			if (pageNum = endPage) {
				system("cls");
				printf("더 이상 표시할 계정이 없습니다.");
				system("pause");
			}
			else {
				pageNum++;
			}
		}
		if (triangle == 61)
			return;
		if (triangle == 91) {
			int manageAccount = 0;
			Account a;
			manageAccount = ((pageNum - 1) * 10) + (selectAccountToManage() + 1);
			a = readAccountInfo(manageAccount);
			system("cls");
			int menu = 0;
			menu = selectManageFunction();
			switch (menu) {
				case 1:
					changeNick(&(a.nick));
					break;

				case 2:
					changeLock(&(a.id), &(a.lock));
					break;
			}

		}

	}

}