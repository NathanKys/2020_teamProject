#pragma once
#include "header.h"


int uiAfterLogin(char * nick) {
	int triangle;
	char ch;

	system("cls");
	gotoxy(40, 5);
	printf("%s님 안녕하세요!\n", nick);

	gotoxy(32, 10);
	printf("-------------------------------------------------\n");
	gotoxy(32, 11);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 12);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 13);
	printf("|\t│          내정보  보기        │ \t|\n");
	gotoxy(32, 14);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 15);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 16);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 17);
	printf("|\t│          사용자  검색        │ \t|\n");
	gotoxy(32, 18);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 19);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 20);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 21);
	printf("|\t│            쪽지함            │ \t|\n");
	gotoxy(32, 22);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 23);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 24);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 25);
	printf("|\t│           로그 아웃          │ \t|\n");
	gotoxy(32, 26);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 27);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 28);
	printf("--------------------------------------------------\n");


	triangle = 13;
	gotoxy(37, triangle);
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
					case UP:
						if (triangle > 13)
						{
							gotoxy(37, triangle);
							printf(" ");
							triangle = triangle - 4;
							gotoxy(37, triangle);
							printf("▶");
						}
						break;
					case DOWN:
						if (triangle < 25)
						{
							gotoxy(37, triangle);
							printf(" ");
							triangle = triangle + 4;
							gotoxy(37, triangle);
							printf("▶");
						}
						break;
				}
			}
			if (ch == 13)
				break;
		}
	}

	if (triangle == 13)
		return 1;
	if (triangle == 17)
		return 2;
	if (triangle == 21)
		return 3;
	if (triangle == 25)
		return 4;
	return 4;
}