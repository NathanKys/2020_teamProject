#pragma once
#include "header.h"

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

void showAllAcoountInfo() {

	gotoxy(10, 3);
	printf("아이디");
	gotoxy(10, 5);

}