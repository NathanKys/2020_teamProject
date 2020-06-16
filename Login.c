#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char admin_id[] = "1234";
char admin_password[] = "1234";

int loginFunction(int* num_account) {

	FILE* memlist;

	memlist = fopen("./accountlist.txt", "r");
	if (memlist == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	char c = ' ';
	char** account_id = (char**)malloc(sizeof(char*) * (*num_account));
	char** account_password = (char**)malloc(sizeof(char*) * (*num_account));

	for (int i = 0; i < *num_account; i++) {
		account_id[i] = (char*)malloc(sizeof(char) * 13);
		account_password[i] = (char*)malloc(sizeof(char) * 13);
	}

	int j;
	for (j = 0; j < *num_account; j++) {   // for(j=0;j<num_account;j++)

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

	int row = 0;
	char stdid[14];
	char stdpassword[18];

	while (row == 0) {
		system("cls");
		printf("ID:");
		fgets(stdid, 14, stdin);
		
		if(strcmp(stdid,"~")==0){
			
			break;
		}

		// 배열 크기가 넘어가면 입력 버퍼를 비움.
		stdid[strcspn(stdid, "\n")] = 0;
		if (strlen(stdid) > 12) {
			while (getchar() != '\n');
		}
		for (int i = 0; i < *num_account; i++) {       //i<num_account 로 수정
			if (strcmp(account_id[i], stdid) == 0) {
			pass:system("cls");
				char stdpassword[18] = "";
				printf("PASSWORD:");
				fgets(stdpassword, 18, stdin);

				char c = ' ';
				while (stdpassword[16]!= 0) {
					scanf("%c", &c);
					if (c == '\n')
						break;
				}
				stdpassword[strcspn(stdpassword, "\n")] = 0;
				
				if (strcmp(account_password[i], stdpassword) == 0) {
					
					printf("Loged in sucessfully\n");
					system("pause");
					row = i + 1;
					break;
				}
				else {
					printf("Wrong password.\n");
					system("pause");
					goto pass;
				}

			}
			else if (strcmp(admin_id, stdid) == 0) {
			pass_admin: system("cls"); 
				printf("Please enter a secondary password.(6 digits)");
				char stdpassword[18] = "";
				fgets(stdpassword, 18, stdin);

				char c = ' ';
				while (stdpassword[16] != 0) {
					scanf("%c", &c);
					if (c == '\n')
						break;
				}
				stdpassword[strcspn(stdpassword, "\n")] = 0;
				if (strcmp(admin_password, stdpassword) == 0) {
					row = -1;
					break;
				}
				else {
					printf("Password is incorrect.");
					system("pause");
					goto pass_admin;
				}
			}

			if (i == (*num_account - 1))
			{
				printf("Invalidated form of ID\n");
				system("pause");
			}
		}
	}

	free(account_id);
	free(account_password);

	fclose(memlist);
	return row;
}
