#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include "ReadAccount.h"
#include "message.h"
#define MAX_LINE_LENGTH 130

void showAllAccountInfo2(int pageNum, int num_account) {
	for (int i = 1; i <= 10; i++) {
		if ((pageNum - 1) * 10 + i <= num_account) {
			Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0, 0 };
			readAccountInfo2((pageNum - 1) * 10 + i, &a);
			gotoxy(35, 3 + (i * 2));
			printf("%d", i - 1);
			gotoxy(37, 3 + (i * 2));
			printf("%s", a.id);
			gotoxy(62, 3 + (i * 2));
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
		printf("열람할 계정의 아이디 번호를 선택하세요.");
		char input = ' ';
		char temp = ' ';
		scanf("%c", &input);
		scanf("%c", &temp);

		if (input == '~'){
			system("pause");
		return -1;
		}

		in = input - 48;
		if (temp != '\n' || !(0 <= in && in <= 9)) {
			gotoxy(3, 26);
			printf("잘못된 입력입니다. 숫자 하나만을 입력하세요.\n");
			system("pause");
			gotoxy(3, 26);
			printf("                                              ");
			gotoxy(3, 27);
			printf("                                              ");
			flag = 1;
		}
		if (pageNum == endPage && num_account % 10 <= in) {
			gotoxy(3, 26);
			printf("존재하지 않는 아이디 번호입니다.\n");
			system("pause");
			flag = 1;
		}

	} while (flag);
	return in;
}
int accountInfo_Menu(Account* a) {
	gotoxy(50, 4);
	printf("사용자 정보 조회");
	gotoxy(19, 6);
	printf("==============================================================================");
	gotoxy(23, 8);
	printf("아이디");
	gotoxy(37, 8);
	printf("닉네임");
	gotoxy(52, 8);
	printf("생년월일");
	gotoxy(65, 8);
	printf("이메일");
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
	printf("│      쪽지 보내기     │");
	gotoxy(33, 27);
	printf("└----------------------┘");
	gotoxy(63, 25);
	printf("┌------------------------┐");
	gotoxy(63, 26);
	printf("│    뒤로가기   │");
	gotoxy(63, 27);
	printf("└------------------------┘");

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
		printf("사용자 검색");
		gotoxy(37, 3);
		printf("아이디");
		gotoxy(62, 3);
		printf("추천 횟수");
		showAllAccountInfo2(pageNum, num_account);
		gotoxy(3, 25);
		printf("┌--------------------┐");
		gotoxy(3, 26);
		printf("│     이전 페이지    │");
		gotoxy(3, 27);
		printf("└--------------------┘");
		gotoxy(33, 25);
		printf("┌--------------------┐");
		gotoxy(33, 26);
		printf("│     다음 페이지    │");
		gotoxy(33, 27);
		printf("└--------------------┘");
		gotoxy(63, 25);
		printf("┌------------------┐");
		gotoxy(63, 26);
		printf("│     뒤로가기     │");
		gotoxy(63, 27);
		printf("└------------------┘");
		gotoxy(93, 25);
		printf("┌------------------┐");
		gotoxy(93, 26);
		printf("│     번호 선택    │");
		gotoxy(93, 27);
		printf("└------------------┘");
		gotoxy(36, 28);
		printf("계정 정보를 열람하려면 번호 입력을 선택하세요.");

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
				printf("더 이상 표시할 계정이 없습니다.");
				system("pause");
			}
			else {
				pageNum--;
			}
		}
		if (triangle == 31) {
			if (pageNum == endPage) {
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
			int showAccount = 0;
			int accountToManage = 0;
			Account a;
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
			}
		}
	}
}
