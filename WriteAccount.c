#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LENGTH 130
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
			//temp1[counter] = '\0';
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
	for (int j = i; j < MAX_LINE_LENGTH-3; j++) {
		infoString[j] = ' ';
	}
	infoString[MAX_LINE_LENGTH-2] = '\n';
	infoString[MAX_LINE_LENGTH-1] = '\0';
		
	if (i < counter) {		//변경된 이후의 총 데이터 길이가 원래보다 짧아진 경우
		infoString[i-1] = '\0';
		fseek(fp, position, SEEK_SET);
		fputs(infoString, fp);
	}
	else {		//변경된 이후의 총 데이터 길이가 원래보다 길어진 경우
		fseek(fp, position, SEEK_SET);
		fputs(infoString, fp);


	}



	
	fclose(fp);

}