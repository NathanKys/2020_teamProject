#define _CRT_SECURE_NO_WARNINGS
#include "header.h"



int uiShowMyInfo(Account* login, int login_id_num) {
	int triangle;
	char ch;
	system("cls");

	gotoxy(5, 3);
	printf("=====================================================================================\n");
	gotoxy(5, 4);
	printf("\t\t\t\t\t  내 정보"); // 텝 5개 스페이스바 2개
	gotoxy(5, 5);
	printf("=====================================================================================\n");

	gotoxy(20, 7);
	printf("아이디");
	gotoxy(20, 8);
	printf("%s\t", (*login).id);

	gotoxy(40, 7);
	printf("이름");
	gotoxy(40, 8);
	printf("%s\t", (*login).name);

	gotoxy(61, 7);
	printf("닉네임");
	gotoxy(61, 8);
	printf("%s\t", (*login).nick);

	gotoxy(20, 10);
	printf("생년월일");
	gotoxy(20, 11);
	for (int i = 0; i < 8; i++) {
		printf("%d", (*login).birth[i]);
	}

	gotoxy(40, 10);
	printf("휴대폰 번호");
	gotoxy(40, 11);
	if ((*login).phone[10] == -1) {
		for (int i = 0; i < 10; i++) {
			printf("%d", (*login).phone[i]);
		}
	}
	else if ((*login).phone[11] == -1) {
		for (int i = 0; i < 11; i++) {
			printf("%d", (*login).phone[i]);
		}
	}
	

	gotoxy(61, 10);
	printf("이메일 주소");
	gotoxy(61, 11);
	printf("%s\t", (*login).email);

	gotoxy(10, 16);
	printf("┌------------------┐\n");
	gotoxy(10, 17);
	printf("│   내 정보 수정   │\n");
	gotoxy(10, 18);
	printf("└------------------┘\n");

	gotoxy(35, 16);
	printf("┌------------------┐\n");
	gotoxy(35, 17);
	printf("│     과거 이력    │\n");
	gotoxy(35, 18);
	printf("└------------------┘\n");

	gotoxy(60, 16);
	printf("┌------------------┐\n");
	gotoxy(60, 17);
	printf("│     뒤로 가기    │\n");
	gotoxy(60, 18);
	printf("└------------------┘\n");


	triangle = 8;
	gotoxy(triangle, 17);
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
						if (triangle > 8)
						{
							gotoxy(triangle, 17);
							printf("  ");
							triangle = triangle - 25;
							gotoxy(triangle, 17);
							printf("▶");
						}
						break;
					case RIGHT:
						if (triangle < 58)
						{
							gotoxy(triangle, 17);
							printf("  ");
							triangle = triangle + 25;
							gotoxy(triangle, 17);
							printf("▶");
						}
						break;
				}
			}
			if (ch == 13)
				break;
		}
	}


	switch (triangle)
	{
		case 8:
			if (checkPW((*login).pw) == 1) {
				selectEdit(login, login_id_num);
			}
			else {
				break;
			}

			break;

		case 33:
			uiOldInfo(login);
			break;
			
		case 58:
			return 2;
			break;	
	}

}


void uiOldInfo(Account* login) {
	int xxxx = 5;
	int yyyy = 5;
	char ch;
	system("cls");
	

	gotoxy(5, 3);
	printf("=====================================================================================\n");
	gotoxy(5, 4);
	printf("\t\t\t\t\t  변경된 정보"); // 텝 5개 스페이스바 2개
	gotoxy(5, 5);
	printf("=====================================================================================\n");

	FILE* list;

	list = fopen("./breakdown.txt", "r");
	if (list == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}
	//char tempID[20] = {0, };
	//int i = 0;
	while (!feof(list)) {
		int i = 0;
		char tempID[20] = { 0, };
		char temp[50] = { 0 , };
		while (true) {
			tempID[i] = fgetc(list);
			if (tempID[i] == ',') {
				tempID[i] = '\0';

				if (strcmp(login->id, tempID) == 0) {

					char num = fgetc(list);
					fgetc(list);
					int number = num - 48;
					yyyy += 2;
					gotoxy(xxxx, yyyy);
					if (number == 0) {
						printf("과거 비밀번호\t");
					}
					else if (number == 1) {
						printf("과거 이름\t");
					}
					else if (number == 2 || number == 8 || number == 9) {
						printf("과거 닉네임\t");
					}
					else if (number == 3) {
						printf("과거 이메일\t");
					}
					else if (number == 4) {
						printf("과거 생년월일\t");
					}
					else if (number == 5) {
						printf("과거 전화번호\t");
					}
					else {
						printf("과거  ??????\t");
					}

					int j = 0;
					while (true) {
						temp[j] = fgetc(list);
						if (temp[j] == EOF || temp[j] == '\n' || temp[j] == ',') {
							if (temp[j] == ',') {
								temp[j] = '\0';
							}
							break;
						}
						j++;
					}
					printf(": %s", temp);

					if (number == 8) { // 보조 관리자
						int k = 0;
						char change_ID[20] = { 0, };
						while (true) {
							change_ID[k] = fgetc(list);
							if (change_ID[k] == '\n' || change_ID[k] == EOF) {
								break;
							}
							k++;
						}
						printf("\t\t변경자\t: %s  ", change_ID);
						
					}
					if (number == 9) { // 최종 관리자
						printf("\t\t변경자\t: admin");
					}
					printf("\n");
				}
				else {
					char buffer[70];
					fgets(buffer, 70, list);
				}

				break;
			}
			//else if (tempID[i] == EOF) {
			//	fclose(list);
			//	return 0;
			//}
			i++;
		}

	}
	fclose(list);

	yyyy += 2;
	gotoxy(xxxx, yyyy);

	system("pause");

	return;
}
