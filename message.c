#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
//message.txt로 부터 첫줄부터 파일입출력을 통해 temp구조체에 담고,
//그 구조체의 receiver가 사용자 id와 같으면 크기가 10인 구조체 배열 message에 저장
//구조체가 꽉차면 첫번째 구조체부터 밀어내는식으로 해서 배열 마지막이 가장 최신(텍스트파일에 가장 아래있는) message로 유지
//message.txt파일의 마지막 줄을 읽으면 런타임에러가 발생
void showMessageList(char* id) {
	FILE* fp;
	fp = fopen("./message.txt", "r");
	if (fp == NULL)
	{
		printf("파일 입출력 실패.\n");
		return;
	}
	int j = 0;
	int k = 0;
	Message message[10] = { "", "", "", 0 };
	int count = 0;
	while (count!=35) {
		Message temp = { "", "", "", 0 };
		if (k < 10) {
			while (true) {
				temp.sender[j] = fgetc(fp);
				if (temp.sender[j] == ',') { temp.sender[j] = '\0'; j = 0; break; }
				j++;
			}
			while (true) {
				temp.receiver[j] = fgetc(fp);
				if (temp.receiver[j] == ',') { temp.receiver[j] = '\0'; j = 0; break; }
				j++;
			}
			temp.read = (fgetc(fp) - 48);
			fgetc(fp);
			while (true) {
				temp.content[j] = fgetc(fp);
				if (temp.content[j] == '\n') { temp.content[j] = '\0'; j = 0; break; }
				j++;
			}
			if (!strcmp(temp.receiver,id)) {
				message[k] = temp;
				k++;
			}		
		}
		else {
			while (true) {
				temp.sender[j] = fgetc(fp);
				if (temp.sender[j] == ',') { temp.sender[j] = '\0'; j = 0; break; }
				j++;
			}
			while (true) {
				temp.receiver[j] = fgetc(fp);
				if (temp.receiver[j] == ',') { temp.receiver[j] = '\0'; j = 0; break; }
				j++;
			}
			temp.read = (fgetc(fp) - 48);
			fgetc(fp);
			while (true) {
				temp.content[j] = fgetc(fp);
				if (temp.content[j] == '\n') { temp.content[j] = '\0'; j = 0; break; }
				j++;
			}
			if (!strcmp(temp.receiver, id)){
				for (int i = 0; i < 9; i++) {
					message[i] = message[i+1];
				}
				message[9] = temp;
			}
		}
		count++;
	}
	for (int i = 0; i < 10; i++) {
		printf("%s\n", message[i].content);
	}
	fclose(fp);
}

/*
void writeMessage() {
	FILE* fp;
	fp = fopen("./message.txt", "w");
	if (fp == NULL)
	{
		printf("파일 입출력 실패.\n");
		return;
	}






}*/
