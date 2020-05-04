#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void login() {

	FILE* memlist;
	
	memlist = fopen("./accountlist.txt", "r");
	if (memlist == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}

	char c = ' ';
	char account_id[num_account][13] = { 0, }; // 배열 세로는 char account_id[num_account][12];
	char account_password[num_account][17] = { 0, };

	int j;
	for (j = 0; j < num_account; j++) {   // for(j=0;j<num_account;j++)

		int i = 0;
		while (1) {
			c = fgetc(memlist);
			if (c == ',') {
				account_id[j][i] = NULL;
				break;
			}
			account_id[j][i++] = c;
		}
		i = 0;
		while (1) {
			c = fgetc(memlist);
			if (c == ',') {
				account_password[j][i] = NULL;
				break;
			}
			account_password[j][i++] = c;
		}
		while (fgetc(memlist) != '\n') {

		}
	}
	
	int row;
	char stdid[14];
	char stdpassword[18];

	printf("아이디를 입력하세요:");
	fgets(stdid, 14, stdin);

	// 배열 크기가 넘어가면 입력 버퍼를 비움.
	if (strlen(stdid) > 12) {
		while (getchar() != '\n');
	}
	stdid[strcspn(stdid, "\n")] = 0;
	for (int i = 0; i < num_account; i++) {       //i<num_account 로 수정
		if (strcmp(account_id[i], stdid) == 0) {
			printf("\n아이디 일치\n");

			printf("\n비밀번호를 입력하세요:");
			fgets(stdpassword, 18, stdin);
			if (strlen(stdid) > 12) {
				while (getchar() != '\n');
			}
			stdpassword[strcspn(stdpassword, "\n")] = 0;
			if (strcmp(account_password[i], stdpassword) == 0) {
				printf("\n비밀번호 일치\n");
				row=i;
				break;
			}
			else
				printf("비밀번호가 틀립니다.");
			break;
		}

		if (i == (num_account-1))
			printf("존재하지 않는 아이디 입니다");
	}




	fclose(memlist);
	return row;
}
