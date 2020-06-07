#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include "ReadAccount.h"
#include "message.h"

void showAllAccountInfo2(int pageNum, int num_account) {
	for (int i = 1; i <= 10; i++) {
		if ((pageNum - 1) * 10 + i <= num_account) {
			Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0, 0 };
			readAccountInfo2((pageNum - 1) * 10 + i, &a);
			gotoxy(37, 3 + (i * 2));
			printf("%d", i - 1);
			gotoxy(43, 3 + (i * 2));
			printf("%s", a.id);
			gotoxy(70, 3 + (i * 2));
			printf("%d", a.rec);
		}
	}
}
int selectAccountToShow(int num_account, int pageNum, int endPage) {
	bool flag = 0;
	int in = 0;
	do {
		flag = 0;
		for (int i = 0; i < 3; i++) {
			gotoxy(3, 25 + i);
			printf("                                                           ");
			printf("                                                           ");
		}
		gotoxy(3, 28);
		printf("                                                                                                       ");
		gotoxy(3, 25);
		printf("Enter the ID number of the account you want to view.(0-9)");
		char input = ' ';
		char temp = ' ';
		scanf("%c", &input);
		scanf("%c", &temp);

		if (input == '~') {
			system("pause");
			return -1;
		}

		in = input - 48;
		if (temp != '\n' || !(0 <= in && in <= 9)) {
			gotoxy(3, 26);
			printf("Invalid input. Please enter only one number.\n");
			system("pause");
			gotoxy(3, 26);
			printf("                                              ");
			gotoxy(3, 27);
			printf("                                              ");
			flag = 1;
		}
		if (pageNum == endPage && num_account % 10 <= in) {
			gotoxy(3, 26);
			printf("This ID number doesn’t exist.\n");
			system("pause");
			flag = 1;
		}

	} while (flag);
	return in;
}
int accountInfo_Menu(Account* a) {
	gotoxy(50, 4);
	printf("View User Information");
	gotoxy(19, 6);
	printf("==============================================================================");
	gotoxy(25, 8);
	printf("ID");
	gotoxy(37, 8);
	printf("Nickname");
	gotoxy(52, 8);
	printf("Date of Birth");
	gotoxy(65, 8);
	printf("Email Address");
	gotoxy(19, 10);
	printf("==============================================================================");
	gotoxy(23, 12);
	printf("%s", a->id);
	gotoxy(37, 12);
	printf("%s", a->nick);
	gotoxy(52, 12);
	for (int j = 0; j < 6; j++) {
		printf("%d", a->birth[j]);
	}
	gotoxy(65, 12);
	printf("%s", a->email);
	gotoxy(33, 25);
	printf("┌----------------------┐");
	gotoxy(33, 26);
	printf("│     Send Message     │");
	gotoxy(33, 27);
	printf("└----------------------┘");
	gotoxy(63, 25);
	printf("┌-----------┐");
	gotoxy(63, 26);
	printf("│    Back   │");
	gotoxy(63, 27);
	printf("└-----------┘");

	int triangle;
	char ch;
	triangle = 31;
	gotoxy(triangle, 26);
	printf("▶");
	while (1)
	{
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
						gotoxy(triangle, 26);
						printf("  ");
						triangle = triangle - 30;
						gotoxy(triangle, 26);
						printf("▶");
					}
					break;
				case RIGHT:
					if (triangle < 61)
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
void userSearch(Account* login, int num_account) {
	int pageNum = 1;
	int endPage = ((num_account - 1) / 10) + 1;

	while (true) {
		system("cls");
		gotoxy(55, 1);
		printf("User Search");
		gotoxy(35, 3);
		printf("Number");
		gotoxy(44, 3);
		printf("ID");
		gotoxy(68, 3);
		printf("recommendation");
		showAllAccountInfo2(pageNum, num_account);
		gotoxy(3, 25);
		printf("┌--------------------┐");
		gotoxy(3, 26);
		printf("│      Prev Page     │");
		gotoxy(3, 27);
		printf("└--------------------┘");
		gotoxy(33, 25);
		printf("┌--------------------┐");
		gotoxy(33, 26);
		printf("│      Next Page     │");
		gotoxy(33, 27);
		printf("└--------------------┘");
		gotoxy(63, 25);
		printf("┌------------------┐");
		gotoxy(63, 26);
		printf("│       Back       │");
		gotoxy(63, 27);
		printf("└------------------┘");
		gotoxy(93, 25);
		printf("┌------------------┐");
		gotoxy(93, 26);
		printf("│   Select Number  │");
		gotoxy(93, 27);
		printf("└------------------┘");
		gotoxy(36, 28);
		printf("Please Select 'Select Number' if you want to view account information.");

		int triangle;
		char ch;
		triangle = 1;
		gotoxy(triangle, 26);
		printf("▶");
		while (1)
		{
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
				printf("There is no more ID to display.");
				system("pause");
			}
			else {
				pageNum--;
			}
		}
		if (triangle == 31) {
			if (pageNum == endPage) {
				system("cls");
				printf("There is no more ID to display.");
				system("pause");
			}
			else {
				pageNum++;
			}
		}
		if (triangle == 61)
			return;
		if (triangle == 91) {
			int showAccount = 0;
			int accountToManage = 0;
			Account a;
			int temp = 0;
			do {  // ############################################################## 수정
				system("cls");
				showAllAccountInfo2(pageNum, num_account);
				accountToManage = selectAccountToShow(num_account, pageNum, endPage);
				if (accountToManage != -1) {
					showAccount = ((pageNum - 1) * 10) + (accountToManage + 1);
					a = readAccountInfo(showAccount);
					system("cls");
					int menu = 0;
					menu = accountInfo_Menu(&a);
					switch (menu) {
					case 1:
						temp = sendMessage(login->id, a.id);
						break; 
					case 2:
						temp = 0;
						break;
					}
				}
				else{
					break;
				}
			} while (temp == 1); // ############################################################## 수정

			/*
			accountToManage = selectAccountToShow(num_account, pageNum, endPage);
			if (accountToManage != -1) {
				showAccount = ((pageNum - 1) * 10) + (accountToManage + 1);
				a = readAccountInfo(showAccount);
				system("cls");
				int menu = 0;
				menu = accountInfo_Menu(&a);
				switch (menu) {
				case 1:
					sendMessage(login->id, a.id);
				case 2:
					continue;
				}
			}*/
		}
	}
}
