#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ReadAccountList.h"
#include <stdio.h>
#define MAX_LINE_LENGTH 130

void readAccountList(int line) {
	FILE* fp;
	fp = fopen("./accountlist.txt", "r");
	if (fp == NULL)
	{
		printf("파일 읽기 실패\n");
		return;
	}
	char temp[MAX_LINE_LENGTH];
	int lineCounter = 0;
	while (lineCounter != line) {
		fgets(temp, MAX_LINE_LENGTH, fp) != NULL;
		lineCounter++;

	}

	Account a = { "", "", "", "", "", {0, }, {0, }, 0, 0, 0 };
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
		else { i = 0; break; }
	}

	fscanf(fp, "%d", &a.rec);
	fgetc(fp);
	a.lock = (fgetc(fp) - 48);
	fgetc(fp);
	a.admin = (fgetc(fp) - 48);

	printf("%s\n", a.id);
	printf("%s\n", a.pw);
	printf("%s\n", a.name);
	printf("%s\n", a.nick);
	printf("%s\n", a.email);
	for (int i = 0; i < sizeof(a.birth) / sizeof(int); i++) {
		printf("%d",a.birth[i]);
	}
	printf("\n");
	for (int i = 0; i < sizeof(a.phone) / sizeof(int); i++) {
		printf("%d", a.phone[i]);
	}
	printf("\n");
	printf("%d\n", a.rec);
	printf("%d\n", a.lock);
	printf("%d\n", a.admin);

	fclose(fp);
}