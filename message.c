#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include "Message.h"
#include "ReadAccount.h"

int countMessage(char* id) {
	FILE* fp;
	fp = fopen("./message.txt", "r");
	if (fp == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}
	int messageCounter = 0;

	int i = 0;
	while (!feof(fp)) {
		Message temp = { "", "", 0, "" };
		while (true) {
			temp.senderId[i] = fgetc(fp);
			if (temp.senderId[i] == ',') { temp.senderId[i] = '\0'; i = 0; break; }
			else if (temp.senderId[i] == EOF) {
				fclose(fp);
				return messageCounter;
			}
			i++;

		}
		while (true) {
			temp.receiverId[i] = fgetc(fp);
			if (temp.receiverId[i] == ',') { temp.receiverId[i] = '\0'; i = 0; break; }
			else if (temp.receiverId[i] == EOF) {
				fclose(fp);
				return messageCounter;
			}
			i++;
		}
		temp.read = (fgetc(fp) - 48);
		fgetc(fp);
		while (true) {
			temp.text[i] = fgetc(fp);
			if (temp.text[i] == '\n') {	temp.text[i] = '\0'; i = 0; break; }
			else if (temp.text[i] == EOF) {
				fclose(fp);
				return messageCounter;
			}
			i++;
		}
		if (!strcmp(temp.receiverId, id)) {
			messageCounter++;
		}
	}
	fclose(fp);
	return messageCounter;
}
Message* readMessage(char* id, int count) {
	FILE* fp;
	fp = fopen("./message.txt", "r");
	if (fp == NULL){
		printf("파일 읽기 실패\n");
		exit(1);
	}
	Message* m_arr;
	m_arr = (Message*)malloc(sizeof(Message) * count);
	int i = 0;
	int j = 0;

	while (!feof(fp)) {
		Message temp = { "", "", 0, "" };
		while (true) {
			temp.senderId[i] = fgetc(fp);
			if (temp.senderId[i] == ',') { temp.senderId[i] = '\0'; i = 0; break; }
			else if (temp.senderId[i] == EOF) {
				fclose(fp);
				return m_arr;
			}
			i++;
		}
		while (true) {
			temp.receiverId[i] = fgetc(fp);
			if (temp.receiverId[i] == ',') { temp.receiverId[i] = '\0'; i = 0; break; }
			else if (temp.receiverId[i] == EOF) {
				fclose(fp);
				return m_arr;
			}
			i++;
		}
		temp.read = (fgetc(fp) - 48);
		fgetc(fp);
		while (true) {
			temp.text[i] = fgetc(fp);
			if (temp.text[i] == '\n') { temp.text[i] = '\0'; i = 0; break; }
			else if (temp.text[i] == EOF) {
				fclose(fp);
				return m_arr;
			}
			i++;
		}
		if (!strcmp(temp.receiverId, id)) {
			m_arr[j] = temp;
			j++;
		}
	}
	fclose(fp);
	return m_arr;
}
bool matchMessage(const char* string) {
	regex_t state;
	const char* pattern = "^([A-Za-z0-9가-힣.?,\\!]||[[:blank:]]){1,200}$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}
char* writeMessage() {
	char* input = malloc(sizeof(char) * 201);
	while (true) {
		system("cls");
		gotoxy(10, 10);
		printf("쪽지는 최대 200자까지 작성할 수 있습니다.");
		gotoxy(10, 11);
		printf(">");
		fgets(input, TEXT_MAXSIZE + 2, stdin);
		input[strcspn(input, "\n")] = 0;

		if (input[0]=='~' && strlen(input) == 1) {
			system("cls");
			gotoxy(45, 10);
			printf("메뉴로 돌아갑니다.");
			gotoxy(41, 11);
			system("pause");
			return;
		}
		if (strlen(input) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}
		if (getLength(input) > 200) {
			gotoxy(10, 15);
			printf("쪽지는 최대 200자까지 작성할 수 있습니다!");
			gotoxy(10, 16);
			system("pause");
			continue;
		}
		if (matchMessage(input)) {
			system("cls");
			gotoxy(45, 10);
			printf("쪽지를 성공적으로 보냈습니다.");
			gotoxy(41, 12);
			system("pause");
			break;
		}
		else {
			gotoxy(10, 15);
			printf("허용되지 않은 문자가 포함되었습니다.");
			gotoxy(10, 16);
			printf("허용하는 문자 : 한글, 영어, 숫자, '?', '!', '.', '(', ')', 띄어쓰기 ");
			gotoxy(10, 17);
			system("pause");
			continue;
		}
	}
	return input;
}
void sendMessage(char* sender, char* receiver) {
	FILE* fp;
	fp = fopen("./message.txt", "a+");
	if (fp == NULL)
	{
		printf("파일 입출력 실패.\n");
		exit(1);
	}
	char* input;
	input = writeMessage();
	fprintf(fp, "%s,%s,%d,%s\n", sender, receiver, 1, input);
	fclose(fp);
}
void deleteMessage(Message* m) { //미구현
	FILE* fp;
	fp = fopen("./message.txt", "a+");
	if (fp == NULL)
	{
		printf("파일 입출력 실패.\n");
		exit(1);
	}


	fclose(fp);
}
void showMessage(Message* m, char* id, int num) {
	while (true) {
		system("cls");
		gotoxy(40, 1);
		printf("쪽지 확인");
		gotoxy(10, 3);
		printf("발신자 : %s", m[num].senderId);
		gotoxy(10, 5);
		printf("쪽지 내용 : ");
		if (strlen(m[num].text) > 160) {
			for (int i = 0; i < 80; i++) {
				printf("%c", m[num].text[i]);
			}
			gotoxy(22, 6);
			for (int i = 80; i < 160; i++) {
				printf("%c", m[num].text[i]);
			}
			gotoxy(22, 7);
			for (int i = 160; i < strlen(m[num].text); i++) {
				printf("%c", m[num].text[i]);
			}
		}
		else if(strlen(m[num].text) > 80){
			for(int i=0; i<80; i++){
				printf("%c", m[num].text[i]);
			}
			gotoxy(22, 6);
			for (int i = 80; i < strlen(m[num].text); i++) {
				printf("%c", m[num].text[i]);
			}
		}
		else {
			printf("%s", m[num].text);
		}
		gotoxy(3, 25);
		printf("┌----------------┐");
		gotoxy(3, 26);
		printf("│     답장    │");
		gotoxy(3, 27);
		printf("└----------------┘");
		gotoxy(33, 25);
		printf("┌----------------┐");
		gotoxy(33, 26);
		printf("│     삭제    │");
		gotoxy(33, 27);
		printf("└----------------┘");
		gotoxy(63, 25);
		printf("┌------------------┐");
		gotoxy(63, 26);
		printf("│     뒤로가기     │");
		gotoxy(63, 27);
		printf("└------------------┘");

		int triangle;
		char ch;
		triangle = 1;
		gotoxy(triangle, 26);
		printf("▶");
		while (1)
		{
			if (_kbhit())
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					switch (ch)
					{
					case LEFT:
						if (triangle > 1)
						{
							gotoxy(triangle, 26);
							printf("  ");
							triangle = triangle - 30;
							gotoxy(triangle, 26);
							printf("▶");
						}
						break;
					case RIGHT:
						if (triangle < 61)
						{
							gotoxy(triangle, 26);
							printf("  ");
							triangle = triangle + 30;
							gotoxy(triangle, 26);
							printf("▶");
						}
						break;
					}
				}
				if (ch == 13)
					break;
			}
		}
		if (triangle == 1) {
			system("cls");
			sendMessage(id, m[num].senderId);
			return;
		}
		if (triangle == 31) {
			system("cls");
			deleteMessage(&m);
			return;
		}
		if (triangle == 61) {
			return;
		}
	}
}
Message* showMessageList(char* id) {
	int count = countMessage(id);
	Message* m = readMessage(id, count);

	if (count > 0 && count < 10) {
		for (int i = 0; i < count; i++) {
			if (m[i].read) {
				gotoxy(34, 5 + (i * 2));
				printf("안읽음");
			}
			else {
				gotoxy(35, 5 + (i * 2));
				printf("읽음");
			}
			gotoxy(50, 5 + (i * 2));
			printf("%s", m[i].senderId);
			gotoxy(70, 5 + (i * 2));
			if (strlen(m[i].text) > 11){
				for (int j = 0; j < 10; j++) {
					printf("%c", m[i].text[j]);
				}
				printf("...");
			}
			else {
				printf("%s", m[i].text);
			}
		}
	}
	else if (count >= 10) {
		int line;
		for (int i = count - 10; i < count; i++) {
			line = i - count + 10;
			if (m[i].read) {
				gotoxy(34, 5 + (line * 2));
				printf("안읽음");
			}
			else {
				gotoxy(35, 5 + (line * 2));
				printf("읽음");
			}
			gotoxy(50, 5 + (line * 2));
			printf("%s", m[i].senderId);
			gotoxy(70, 5 + (line * 2));
			if (strlen(m[i].text) > 10){
				for (int j = 0; j < 10; j++) {
					printf("%c", m[i].text[j]);
				}
				printf("...");
			}
			else {
				printf("%s", m[i].text);
			}
		}
	}
	else {
		gotoxy(48, 13);
		printf("쪽지함이 비어있습니다!");
	}
	return m;
}
void messageBox(char* id) {
	while (true) {
		system("cls");
		Message* m = showMessageList(id);
		gotoxy(1, 1);
		gotoxy(57, 1);
		printf("쪽지함");
		gotoxy(35, 3);
		printf("상태");
		gotoxy(50, 3);
		printf("발신자");
		gotoxy(70, 3);
		printf("쪽지 내용");
		gotoxy(48, 25);
		printf("┌------------------┐");
		gotoxy(48, 26);
		printf("│     뒤로가기     │");
		gotoxy(48, 27);
		printf("└------------------┘");

		int triangleX = 30;
		int triangleY = 5;
		char ch;
		gotoxy(triangleX, triangleY);
		printf("▶");
		while (1)
		{
			if (_kbhit())
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					switch (ch)
					{
					case UP:
						if (triangleY > 5 && triangleY < 26)
						{
							gotoxy(triangleX, triangleY);
							printf("  ");
							triangleY = triangleY - 2;
							gotoxy(triangleX, triangleY);
							printf("▶");
						}
						else if (triangleY == 26) {
							gotoxy(triangleX, triangleY);
							printf("  ");
							triangleX = 30;
							triangleY = 23;
							gotoxy(triangleX, triangleY);
							printf("▶");
						}
						break;
					case DOWN:
						if (triangleY < 23)
						{
							gotoxy(triangleX, triangleY);
							printf("  ");
							triangleY = triangleY + 2;
							gotoxy(triangleX, triangleY);
							printf("▶");
						}
						else if (triangleY == 23) {
							gotoxy(triangleX, triangleY);
							printf("  ");
							triangleX = 45;
							triangleY = 26;
							gotoxy(triangleX, triangleY);
							printf("▶");
						}
						break;
					}
				}
				if (ch == 13)
					break;
			}
		}
		int index = (triangleY - 5) / 2;
		int count = countMessage(id);
		if (triangleY < 26 && count>index) {
			showMessage(m, id, index);
		}
		else if (triangleY==26){
			break;
		}
	}
}

void readMessage(const char* _string) {
	// 최대 추천 횟수: 99번
	FILE* fp;
	char temp[MAX_LINE_LENGTH];
	char ch;
	int i = 0;
	int j = 0;
	char string[ID_MAXSIZE + 2] = "";

	// 읽기 우선 쓰기 모드
	fp = fopen("./message.txt", "r+");
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		exit(1);
	}
	while (true) {
		while (true) {
			// 해당 아이디 확인
			string[i] = fgetc(fp);
			if (string[i] == ',') { 
				string[i] = '\0'; 
				i = 0; 
				break; }
			else if (string[i] == EOF) { 
				fclose(fp); 
				return; 
			}
			i++;
		}
		if (!strcmp(string, _string)) {
			// 읽었는지 확인하는 변수까지 이동
			for (;j < 1;j++) {
				while (true) {
					ch = fgetc(fp);
					if (ch == ',') {
						break;
					}
					else if (ch == EOF) {
						fclose(fp);
						return;
					}
				}
			}
			fseek(fp, 0, SEEK_CUR);//없으면 오류 발생
			fputs("0",fp);
			fseek(fp, 0, SEEK_CUR);//없으면 오류 발생
		}
		else {
			// 아이디가 일치하지 않으면 다음 줄로 넘어감.
			fgets(temp, MAX_LINE_LENGTH, fp);
		}
		j = 0;
	}
	fclose(fp);
}
