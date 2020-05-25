#pragma once
#include "header.h"


int uiAfterLogin(char * nick) {
	int triangle;
	char ch;

	system("cls");
	gotoxy(40, 5);
	printf("Welcome, %s!\n", nick);

	gotoxy(32, 10);
	printf("-------------------------------------------------\n");
	gotoxy(32, 11);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 12);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 13);
	printf("|\t│         View My Info         │ \t|\n");
	gotoxy(32, 14);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 15);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 16);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 17);
	printf("|\t│          User Search         │ \t|\n");
	gotoxy(32, 18);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 19);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 20);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 21);
	printf("|\t│          Message Box         │ \t|\n");
	gotoxy(32, 22);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 23);
	printf("|\t\t\t\t\t\t|\n");
	
	gotoxy(32, 24);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 25);
	printf("|\t│          Admin Menu          │ \t|\n");
	gotoxy(32, 26);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 27);
	printf("|\t\t\t\t\t\t|\n");
	
	
	gotoxy(32, 28);
	printf("|\t┌------------------------------┐  \t|\n");
	gotoxy(32, 29);
	printf("|\t│            Log Out           │ \t|\n");
	gotoxy(32, 30);
	printf("|\t└------------------------------┘  \t|\n");
	gotoxy(32, 31);
	printf("|\t\t\t\t\t\t|\n");
	gotoxy(32, 32);
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
						if (triangle < 29)
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
	if (triangle == 29)
		return 4;
	if (triangle == 25)
		return 5;
	return 4;
}
