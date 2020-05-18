#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

void writeAccountInfo(int line, Account* login) {

	FILE* fp;
	fp = fopen("./accountlist.txt", "r+");
	if (fp == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}
	char temp[MAX_LINE_LENGTH];
	int lineCounter = 1;
	fpos_t position = 0;

	while (lineCounter != line) {
		fgets(temp, MAX_LINE_LENGTH, fp);
		lineCounter++;
	}
	fgetpos(fp, &position);

	char temp1[MAX_LINE_LENGTH] = "";
	int counter = 0;
	while (true) {	//입력하기 전에 입력대상 라인의 기존 글자수만큼의 문자열 준비
		temp1[counter] = fgetc(fp);
		if (temp1[counter] == EOF || temp1[counter] == '\n') {
			break;
		}
		temp1[counter] = ' ';
		counter++;
	}

	fseek(fp, position, SEEK_SET);
	fwrite(temp1, counter, 1, fp);	//앞서 준비한 문자열로 입력 대상 라인 밀기(덮어쓰기)


	char infoString[MAX_LINE_LENGTH] = "";
	int i = 0;
	int j = 0;
	while (true) {
		if ((*login).id[j] == '\0') {
			infoString[i++] = ',';
			j = 0;
			break;
		}
		infoString[i++] = (*login).id[j++];
	}
	while (true) {
		if ((*login).pw[j] == '\0') {
			infoString[i++] = ',';
			j = 0;
			break;
		}
		infoString[i++] = (*login).pw[j++];
	}
	while (true) {
		if ((*login).name[j] == '\0') {
			infoString[i++] = ',';
			j = 0;
			break;
		}
		infoString[i++] = (*login).name[j++];
	}
	while (true) {
		if ((*login).nick[j] == '\0') {
			infoString[i++] = ',';
			j = 0;
			break;
		}
		infoString[i++] = (*login).nick[j++];
	}
	while (true) {
		if ((*login).email[j] == '\0') {
			infoString[i++] = ',';
			j = 0;
			break;
		}
		infoString[i++] = (*login).email[j++];
	}
	for (int j = 0; j < 6; j++) {
		infoString[i++] = (*login).birth[j] + 48;
	}
	infoString[i++] = ',';
	j = 0;

	for (int j = 0; j < 11; j++) {
		if ((*login).phone[j] == -1)
			break;
		infoString[i++] = (*login).phone[j] + 48;
	}
	infoString[i++] = ',';
	j = 0;

	char c[3] = "";
	sprintf(c, "%d", (*login).rec);
	while (true) {
		if (c[j] == '\0') {
			infoString[i++] = ',';
			j = 0; break;
		}
		infoString[i++] = c[j++];
	}
	infoString[i++] = (*login).lock + 48;
	infoString[i++] = ',';
	infoString[i++] = (*login).changed + 48;
	

	infoString[i] = '\0';

	fseek(fp, position, SEEK_SET);
	fputs(infoString, fp);
	
	fclose(fp);

}

void recordHistory(char* id, char* _string, int option) {
	/*
	recordHistory는 사용자가 변경한 정보를 텍스트 파일에 반영하는 함수입니다.

	Parameters
	----------
	id: 정보 변경을 실행한 사용자의 아이디
	 _string: 바뀐 새로운 정보(비밀번호, 이메일 등)
	 option: 어떤 정보가 바뀌는지 알려주는 변수


	Notes
	-----
	accountlist.txt는 ANSI형식으로 저장되어 있어야 합니다.
	이 함수를 오로지 기록하는 함수이므로 새로운 정보의 적합성 체크는 함수 호출 이전에 이루어져야 합니다.

	Examples
	--------
	recordHistory("abc289", "새로운이름", NAMECHECK);
	=> abc289 아이디가 저장하고 있던 기존의 이름 뒤에 "/새로운 이름"을 끼워넣음.
	*/
	FILE* fp;
	FILE* tempfp;
	fpos_t position;
	fp = fopen("accountlist.txt", "r+t");
	tempfp = fopen("accountlist.txt", "r");
	char string[1000] = { 0, };
	int i = 0;
	int j = 0;
	char ch;
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		exit(1);
	}
	while (true) {
		while (true) {
			string[i] = fgetc(fp);
			fgetc(tempfp);
			if (string[i] == ',') { string[i] = '\0'; i = 0; break; }
			else if (string[i] == EOF) { fclose(fp); fclose(tempfp); return; }
			i++;
		}
		if (!strcmp(string, id)) {
			// 위에서 아이디를 먼저 읽었기 때문에 -1해줘야 함.
			for (; j < option - 1; j++) {
				while (true) {
					ch = fgetc(fp);
					fgetc(tempfp);
					if (ch == ',') {
						break;
					}
					else if (ch == EOF) {
						fclose(fp);
						fclose(tempfp);
						return;
					}
				}
			}
			while (true) {
				string[i] = fgetc(fp);
				fgetc(tempfp);
				if (string[i] == ',') { string[i] = '\0'; i = 0; break; }
				else if (string[i] == EOF) { fclose(fp); fclose(tempfp); return; }
				i++;
			}
			printf("%s", string);
			fseek(fp, -1, SEEK_CUR);
			fwrite("/", 1, 1, fp);
			fseek(fp, 1, SEEK_CUR);

			//fwrite(_string, strlen(_string), 1, fp);
			fseek(fp, -1, SEEK_CUR);
			fwrite(_string, strlen(_string), 1, fp);
			fseek(fp, 1, SEEK_CUR);

			fseek(fp, -1, SEEK_CUR);
			fwrite(",", 1, 1, fp);
			fseek(fp, 1, SEEK_CUR);

			fseek(fp, -1, SEEK_CUR);
			while (true) {
				ch = fgetc(tempfp);
				if (feof(tempfp) != 0)
					break;
				fputc(ch, fp);
			}
			fseek(fp, 1, SEEK_CUR);
		}
		else {
			// 아이디가 일치하지 않으면 다음 줄로 넘어감.
			while (fgetc(fp) != '\n');
			while (fgetc(tempfp) != '\n');
		}
		j = 0;
	}
	fclose(fp);
	fclose(tempfp);
}