#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"

int readAccountNum() {
	FILE* fp;
	fp = fopen("./accountlist.txt", "r");
	if (fp == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}
	int lineCounter = 0;
	char tempc = ' ';
	while (true) {
		tempc = fgetc(fp);
		if (tempc == '\n')
			lineCounter++;
		if (feof(fp))
			break;
	}

	fclose(fp);

	return lineCounter;
}

Account readAccountInfo(int line) {
	FILE* fp;
	fp = fopen("./accountlist.txt", "r");
	if (fp == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}
	char temp[MAX_LINE_LENGTH];
	int lineCounter = 1;
	while (lineCounter != line) {
		fgets(temp, MAX_LINE_LENGTH, fp);
		lineCounter++;

	}

	Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0 };
	int i = 0;
	while (true) {
		a.id[i] = fgetc(fp);
		if (a.id[i] == ',') { a.id[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.pw[i] = fgetc(fp);
		if (a.pw[i] == ',') { a.pw[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.name[i] = fgetc(fp);
		if (a.name[i] == ',') { a.name[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.nick[i] = fgetc(fp);
		if (a.nick[i] == ',') { a.nick[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		a.email[i] = fgetc(fp);
		if (a.email[i] == ',') { a.email[i] = '\0'; i = 0; break; }
		i++;
	}
	while (true) {
		int temp = fgetc(fp) - 48;
		if (temp != -4)
		{ a.birth[i] = temp; i++; }
		else { i = 0; break; }
	}
	while (true) {
		int temp = fgetc(fp) - 48;
		if (temp != -4) { a.phone[i] = temp; i++; }
		else { a.phone[i] = -1; i = 0; break; }
	}

	fscanf(fp, "%d", &a.rec);
	fgetc(fp);
	a.lock = (fgetc(fp) - 48);
	fgetc(fp);
	a.changed = (fgetc(fp) - 48);

	fclose(fp);

	return a;
}