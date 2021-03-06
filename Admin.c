﻿#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include "ReadAccount.h"

void checkSecondPw() {
	int adminSecondPw[6] = { 1, 3, 5, 7, 9, 0 };	//2차 비밀번호
	bool flag = 0;

	do {
		system("cls");
		flag = 0;
		printf("Please enter a secondary password.(6 digits)");
		char input[8] = "";

		for (int i = 0; i < 7; i++) {
			scanf("%c", &input[i]);
			if (i != 6 && input[i] == '\n') {	//6자를 다 입력하지 않고 enter친 경우
				printf("Password is incorrect.");
				system("pause");
				flag = 1;
				break;
			}
		}
		if (flag != 1 && input[6] != '\n') {
			char temp = ' ';
			while (true) {
				scanf("%c", &temp);
				if (temp == '\n')
					break;
			}
			printf("Password is incorrect.");
			system("pause");
			flag = 1;
		}

		if (flag != 1) {
			for (int i = 0; i < 6; i++) {
				if ((input[i] - 48) != adminSecondPw[i]) {
					printf("Password is incorrect.");
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
	int count = 0;
	while (true) {
		int temp = fgetc(fp) - 48;
		if (count == 10 && temp == -4) {
			(*a).phone[i] = -1;
			break;
		}
		else if (temp != -4) { (*a).phone[i] = temp; i++; }
		else { break; }
		count++;
	}

	fscanf(fp, "%d", &(*a).rec);
	fgetc(fp);
	(*a).lock = (fgetc(fp) - 48);
	fgetc(fp);
	(*a).subAdmin = (fgetc(fp) - 48);


	fclose(fp);
}


void showAllAccountInfo(int pageNum, int num_account) {

	gotoxy(45, 1);
	printf("Admin Menu - All account information");
	gotoxy(3, 3);
	printf("ID");
	gotoxy(16, 3);
	printf("Name");
	gotoxy(37, 3);
	printf("Nickname");
	gotoxy(50, 3);
	printf("Eamil Address");
	gotoxy(81, 3);
	printf("Date of Birth");
	gotoxy(95, 3);
	printf("Phone Number");
	gotoxy(108, 3);
	printf("Locked");
	gotoxy(115, 3);
	printf("SubAdmin");

	for (int i = 1; i <= 10; i++) {
		if ((pageNum - 1) * 10 + i <= num_account) {
			Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0 };
			readAccountInfo2((pageNum - 1) * 10 + i, &a);
			gotoxy(1, 3 + (i * 2));
			printf("%d", i - 1);
			gotoxy(3, 3 + (i * 2));	//아이디
			printf("%s", a.id);
			gotoxy(16, 3 + (i * 2));	//이름
			printf("%s", a.name);
			gotoxy(37, 3 + (i * 2));	//닉네임
			printf("%s", a.nick);
			gotoxy(50, 3 + (i * 2));	//이메일
			printf("%s", a.email);
			gotoxy(81, 3 + (i * 2));	//생년월일
			for (int j = 0; j < 8; j++) {
				printf("%d", a.birth[j]);
			}
			gotoxy(95, 3 + (i * 2));	//휴대폰 번호
			for (int j = 0; j < 11; j++) {
				if (a.phone[j] != -1) {
					printf("%d", a.phone[j]);
				}
			}
			gotoxy(108, 3 + (i * 2));	//잠금 여부
			if (a.lock == 0) {
				printf("  X");
			}
			else {
				printf("  O");
			}
			gotoxy(115, 3 + (i * 2));	//잠금 여부
			if (a.subAdmin == 0) {
				printf("   X");
			}
			else {
				printf("   O");
			}
		}
	}
}

int selectAccountToManage(int num_account, int pageNum, int endPage) {

	bool flag = 0;
	int in = 0;
	do {
		flag = 0;
		for (int i = 0; i < 3; i++) {
			gotoxy(0, 25 + i);
			printf("                                                                  ");
			printf("                                                                  ");
		}
		gotoxy(3, 25);
		printf("Please enter the number of account you want to manage.: ");

		char input;
		scanf("%c", &input);
		char c = ' ';
		char test = ' ';
		scanf("%c", &test);
		while (test != '\n') {
			scanf("%c", &c);
			if (c == '\n')
				break;
		}

		/*char input = ' ';
		char temp = ' ';
		scanf("%c", &input);
		scanf("%c", &temp);*/

		if (input == '~')
			return -1;

		in = input - 48;
		if (test != '\n' || !(0 <= in && in <= 9)) {
			//if (!(0 <= in && in <= 9)) {
			gotoxy(3, 26);
			printf("Invalid input. Please enter only one number.\n");
			gotoxy(3, 27);
			system("pause");
			gotoxy(3, 26);
			printf("                                              ");
			gotoxy(3, 27);
			printf("                                              ");
			flag = 1;
		}
		else if (pageNum == endPage && num_account % 10 <= in) {
			gotoxy(3, 26);
			printf("ID number entered doesn't exist.\n");
			gotoxy(3, 27);
			system("pause");
			flag = 1;
		}

	} while (flag);

	return in;
}

int selectManageFunction(bool subAdmin) {

	gotoxy(35, 5);
	printf("Please select the management menu that you want to perform for the selected account.");
	gotoxy(35, 7);
	if (subAdmin == 0) {
		printf("accountinfo: normal user");
	}
	else if (subAdmin == 1) {
		printf("accountinfo: subadministrator");
	}
	gotoxy(33, 10);
	printf("┌-------------------------┐\n");
	gotoxy(33, 11);
	printf("│     Change Nickname     │\n");
	gotoxy(33, 12);
	printf("└-------------------------┘\n");
	gotoxy(63, 10);
	printf("┌-------------------------┐\n");
	gotoxy(63, 11);
	printf("│  Lock / Unlock Account  │\n");
	gotoxy(63, 12);
	printf("└-------------------------┘\n");
	gotoxy(93, 10);
	printf("┌-------------------------┐\n");
	gotoxy(93, 11);
	printf("│   SubAdmin Management   │\n");
	gotoxy(93, 12);
	printf("└-------------------------┘\n");

	int triangle;
	char ch;

	triangle = 31;
	gotoxy(triangle, 11);
	printf("▶");
	while (1)
	{
		Sleep(300);
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
					if (triangle < 91)
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
	case 91:
		return 3;
		break;
	}
}

int selectManageFunctionSub(bool subAdmin) {
	gotoxy(35, 5);
	printf("Please select the management menu that you want to perform for the selected account.");
	gotoxy(35, 7);
	if (subAdmin == 0) {
		printf("accountinfo: normal user");
	}
	else if (subAdmin == 1) {
		printf("accountinfo: subadministrator");
	}
	gotoxy(33, 10);
	printf("┌-------------------------┐\n");
	gotoxy(33, 11);
	printf("│     Change Nickname     │\n");
	gotoxy(33, 12);
	printf("└-------------------------┘\n");
	gotoxy(63, 10);
	printf("┌-------------------------┐\n");
	gotoxy(63, 11);
	printf("│  Lock / Unlock Account  │\n");
	gotoxy(63, 12);
	printf("└-------------------------┘\n");

	int triangle;
	char ch;

	triangle = 31;
	gotoxy(triangle, 11);
	printf("▶");
	while (1)
	{
		Sleep(300);
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

void changeNick(char* nick) {


	char input[NICKNAME_MAXSIZE + 2];

	while (true) {
		system("cls");
		gotoxy(10, 5);
		printf("Current Nickname: %s", nick);

		gotoxy(10, 7);
		printf("Nickname can include English, numbers and blank spaces.(2-12)\n");
		gotoxy(10, 8);
		printf("Please enter a new Nickname.: ");

		fgets(input, NICKNAME_MAXSIZE + 2, stdin);
		input[strcspn(input, "\n")] = 0;

		gotoxy(10, 10);

		if (strlen(input) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(nick, input)) {
			printf("It same as current info.");
			system("pause");
			continue;
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(input, NICKNAMECHECK)) {
			printf("Overlapped nickname, Please check again.\n");
			system("pause");
			continue;
		}
		if (getLength(input) < 2 || getLength(input) > 12) {
			printf("Nickname must be 2 to 12 characters with English and numeric characters.\n");
			system("pause");
			continue;
		}
		if (matchNickname(input)) {
			printf("Nickname has been changed successfully.\n");
			gotoxy(10, 11);
			printf("Nickname after change: %s\n", input);
			gotoxy(10, 13);
			system("pause");
			break;
		}
		else {
			printf("Please enter a validated character.\n");
			system("pause");
			continue;
		}

	}
	strcpy(nick, input);
	system("cls");
}

void changeLock(char* id, bool* lock) {

	printf("Selected Account: %s\n", id);


	int triangle;
	char ch;

	triangle = 1;
	gotoxy(triangle, 6);
	printf("▶");

	gotoxy(0, 1);
	if (*lock) {
		printf("locked: ");
		printf("O");
		gotoxy(3, 5);
		printf("┌----------------------┐\n");
		gotoxy(3, 6);
		printf("│    Unlock Account    │\n");
		gotoxy(3, 7);
		printf("└----------------------┘\n");
		gotoxy(1, 6);
		while (1)
		{
			Sleep(300);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 13)
					break;
			}
		}
		gotoxy(0, 1);
		printf("locked: O -> X");
		gotoxy(3, 9);
		printf("Account has been unlocked successfully.");
	}
	else {
		printf("locked: ");
		printf("X");
		gotoxy(3, 5);
		printf("┌----------------------┐\n");
		gotoxy(3, 6);
		printf("│     Lock Account     │\n");
		gotoxy(3, 7);
		printf("└----------------------┘\n");
		gotoxy(1, 6);
		while (1)
		{
			Sleep(300);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 13)
					break;
			}
		}
		gotoxy(0, 1);
		printf("locked: X -> O");
		gotoxy(3, 9);
		printf("Account has been locked successfully.");
	}
	system("pause");
	system("cls");

	bool temp = (*lock);
	(*lock) = !temp;
}

void changeNickSub(char* nick, Account* targetAccount, int login_id_num) {

	if (checkSubAdmin(&targetAccount, login_id_num)) { // check
		return;
	}
	char input[NICKNAME_MAXSIZE + 2];

	while (true) {
		system("cls");
		gotoxy(10, 5);
		printf("Current Nickname: %s", nick);

		gotoxy(10, 7);
		printf("닉네임에는 한글, 영어, 숫자, 띄어쓰기를 사용할 수 있습니다.(최소2자~최대12자)\n");
		gotoxy(10, 8);
		printf("Please enter new nickname.: ");

		fgets(input, NICKNAME_MAXSIZE + 2, stdin);
		input[strcspn(input, "\n")] = 0;

		gotoxy(10, 10);
		if (checkSubAdmin(&targetAccount, login_id_num)) { // check
			break;
		}
		if (strlen(input) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(nick, input)) {
			printf("기존 정보와 동일합니다.");
			system("pause");
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
			printf("Nickname has been changed successfully.\n");
			gotoxy(10, 11);
			printf("Nickname after change: %s\n", input);
			gotoxy(10, 13);
			system("pause");
			break;
		}
		else {
			printf("올바른 문자를 입력해주세요.\n");
			system("pause");
			continue;
		}

	}
	strcpy(nick, input);
	system("cls");
}

void changeLockSub(char* id, bool* lock, Account* targetAccount, int login_id_num) {
	if (checkSubAdmin(&targetAccount, login_id_num)) { // check
		return;
	}

	printf("Selected Account: %s\n", id);


	int triangle;
	char ch;

	triangle = 1;
	gotoxy(triangle, 6);
	printf("▶");

	gotoxy(0, 1);
	if (*lock) {
		printf("locked: ");
		printf("O");
		gotoxy(3, 5);
		printf("┌----------------------┐\n");
		gotoxy(3, 6);
		printf("│    Unlock Account    │\n");
		gotoxy(3, 7);
		printf("└----------------------┘\n");
		gotoxy(1, 6);
		while (1)
		{
			Sleep(300);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 13)
					break;
			}
		}
		if (checkSubAdmin(&targetAccount, login_id_num)) { // check
			return;
		}
		gotoxy(0, 1);
		printf("locked: O -> X");
		gotoxy(3, 9);
		printf("Account has been unlocked successfully.");
	}
	else {
		printf("locked: ");
		printf("X");
		gotoxy(3, 5);
		printf("┌----------------------┐\n");
		gotoxy(3, 6);
		printf("│     Lock Account     │\n");
		gotoxy(3, 7);
		printf("└----------------------┘\n");
		gotoxy(1, 6);
		while (1)
		{
			Sleep(300);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 13)
					break;
			}
		}
		if (checkSubAdmin(&targetAccount, login_id_num)) { // check
			return;
		}
		gotoxy(0, 1);
		printf("locked: X -> O");
		gotoxy(3, 9);
		printf("Account has been locked successfully.");
	}
	system("pause");
	system("cls");

	bool temp = (*lock);
	(*lock) = !temp;
}

bool adminMenu(int num_account, Account* targetAccount) {
	int pageNum = 1;
	int endPage = ((num_account - 1) / 10) + 1;

	while (true) {

		showAllAccountInfo(pageNum, num_account);

		gotoxy(3, 25);
		printf("┌--------------------┐\n");
		gotoxy(3, 26);
		printf("│      Prev Page     │\n");
		gotoxy(3, 27);
		printf("└--------------------┘\n");
		gotoxy(33, 25);
		printf("┌--------------------┐\n");
		gotoxy(33, 26);
		printf("│      Next Page     │\n");
		gotoxy(33, 27);
		printf("└--------------------┘\n");
		gotoxy(63, 25);
		printf("┌------------------┐\n");
		gotoxy(63, 26);
		printf("│      Log Out     │\n");
		gotoxy(63, 27);
		printf("└------------------┘\n");
		gotoxy(93, 25);
		printf("┌------------------┐\n");
		gotoxy(93, 26);
		printf("│   Select Number  │\n");
		gotoxy(93, 27);
		printf("└------------------┘\n");


		int triangle;
		char ch;

		triangle = 1;
		gotoxy(triangle, 26);
		printf("▶");
		while (1)
		{
			Sleep(300);
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
				printf("There is no more account to display.");
				system("pause");
			}
			else {
				pageNum--;
			}
		}
		if (triangle == 31) {
			if (pageNum == endPage) {
				system("cls");
				printf("There is no more account to display.");
				system("pause");
			}
			else {
				pageNum++;
			}
		}
		if (triangle == 61)
			return false;

		if (triangle == 91) {
			int manageAccount = 0;

			int accountToManage = 0;
			accountToManage = selectAccountToManage(num_account, pageNum, endPage);

			if (accountToManage != -1) {

				manageAccount = ((pageNum - 1) * 10) + (accountToManage + 1);

				*targetAccount = readAccountInfo(manageAccount);
				system("cls");
				int menu = 0;
				menu = selectManageFunction((*targetAccount).subAdmin);
				switch (menu) {
				case 1:
					writeBreakdownChar(9, &((*targetAccount).id), &((*targetAccount).nick));
					changeNick((*targetAccount).nick);
					writeAccountInfo(manageAccount, targetAccount);
					break;

				case 2:
					changeLock((*targetAccount).id, &((*targetAccount).lock));
					writeAccountInfo(manageAccount, targetAccount);
					break;
				case 3:
					if ((*targetAccount).subAdmin == 0) {
						(*targetAccount).subAdmin = 1;
						printf("This account has been promoted to a sub administrator\n");
						writeAccountInfo(manageAccount, targetAccount);
						system("pause");
					}
					else if ((*targetAccount).subAdmin == 1) {
						(*targetAccount).subAdmin = 0;
						printf("This account has been demoted to a normal user\n");
						writeAccountInfo(manageAccount, targetAccount);
						system("pause");
					}
					break;
				}
			}

		}
		system("cls");
	}

}

//--

bool checkSubAdmin(Account* targetAccount, int login_id_num) {
	Account login;
	login = readAccountInfo(login_id_num);
	if (!login.subAdmin) {
		system("cls");
		gotoxy(35, 10);
		printf("You don’t have permissions to access this menu!");
		gotoxy(40, 12);
		system("pause");
		system("cls");
		return true;
	}
	else
		return false;
}

void subAdminMenu(int num_account, Account* targetAccount, int login_id_num, char* my_id) {
	int pageNum = 1;
	int endPage = ((num_account - 1) / 10) + 1;
	Account login;
	system("cls");
	while (true) {
		if (checkSubAdmin(&targetAccount, login_id_num)) { // check
			break;
		}

		showAllAccountInfo(pageNum, num_account);

		gotoxy(3, 25);
		printf("┌--------------------┐\n");
		gotoxy(3, 26);
		printf("│      Prev Page     │\n");
		gotoxy(3, 27);
		printf("└--------------------┘\n");
		gotoxy(33, 25);
		printf("┌--------------------┐\n");
		gotoxy(33, 26);
		printf("│      Next Page     │\n");
		gotoxy(33, 27);
		printf("└--------------------┘\n");
		gotoxy(63, 25);
		printf("┌------------------┐\n");
		gotoxy(63, 26);
		printf("│       Back       │");
		gotoxy(63, 27);
		printf("└------------------┘\n");
		gotoxy(93, 25);
		printf("┌------------------┐\n");
		gotoxy(93, 26);
		printf("│   Select Number  │\n");
		gotoxy(93, 27);
		printf("└------------------┘\n");


		int triangle;
		char ch;

		triangle = 1;
		gotoxy(triangle, 26);
		printf("▶");
		while (1)
		{
			Sleep(300);
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


		if (checkSubAdmin(&targetAccount, login_id_num)) { // check
			break;
		}

		if (triangle == 1) {
			if (pageNum == 1) {
				system("cls");
				printf("There is no more account to display.");
				system("pause");
			}
			else {
				pageNum--;
			}
		}
		if (triangle == 31) {
			if (pageNum == endPage) {
				system("cls");
				printf("There is no more account to display.");
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
			int accountToManage = 0;
			accountToManage = selectAccountToManage(num_account, pageNum, endPage);
			if (checkSubAdmin(&targetAccount, login_id_num)) { // check
				break;
			}
			if (accountToManage != -1) {

				manageAccount = ((pageNum - 1) * 10) + (accountToManage + 1);

				*targetAccount = readAccountInfo(manageAccount);
				system("cls");
				int menu = 0;
				menu = selectManageFunctionSub((*targetAccount).subAdmin);
				if (checkSubAdmin(&targetAccount, login_id_num)) { // check
					break;
				}
				switch (menu) {
				case 1:
					writeNickSub(8, (*targetAccount).id, (*targetAccount).nick, my_id);
					changeNickSub((*targetAccount).nick, &targetAccount, login_id_num);
					login = readAccountInfo(login_id_num);
					if (!login.subAdmin) { // check
						return;
					}
					writeAccountInfo(manageAccount, targetAccount);
					break;

				case 2:
					if (strcmp(my_id, (*targetAccount).id)) {
						changeLockSub((*targetAccount).id, &((*targetAccount).lock), &targetAccount, login_id_num);
						login = readAccountInfo(login_id_num);
						if (!login.subAdmin) { // check
							return;
						}
						writeAccountInfo(manageAccount, targetAccount);
					}
					else {
						printf("You can't lock yourself.\n");
						system("pause");
					}

					break;
				}
			}

		}
		system("cls");
	}

}

void writeNickSub(int num, char* target_id, char* oldNick, char* my_id) {
	FILE* fp;
	fp = fopen("./breakdown.txt", "a");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	char out[70];
	char cnum[2];
	strcpy(out, target_id);
	strcat(out, ",");
	sprintf(cnum, "%d", num);
	strcat(out, cnum);
	strcat(out, ",");
	strcat(out, oldNick);
	strcat(out, ",");
	strcat(out, my_id);
	strcat(out, "\n");
	fputs(out, fp);
	fclose(fp);
}
