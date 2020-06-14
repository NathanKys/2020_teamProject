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
			temp.receiverId[i] = fgetc(fp);
			if (temp.receiverId[i] == ',') { temp.receiverId[i] = '\0'; i = 0; break; }
			else if (temp.receiverId[i] == EOF) {
				fclose(fp);
				return messageCounter;
			}
			i++;

		}
		while (true) {
			temp.senderId[i] = fgetc(fp);
			if (temp.senderId[i] == ',') { temp.senderId[i] = '\0'; i = 0; break; }
			else if (temp.senderId[i] == EOF) {
				fclose(fp);
				return messageCounter;
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
Message* readMessageFile(char* id, int count) {
	FILE* fp;
	fp = fopen("./message.txt", "r");
	if (fp == NULL) {
		printf("파일 읽기 실패\n");
		exit(1);
	}
	Message* m_arr;
	m_arr = (Message*)malloc(sizeof(Message) * count);
	int i = 0;
	int j = 0;

	while (!feof(fp)) {
		Message temp = { "", "", 0, "" };
		temp.receiverId[i] = fgetc(fp);
		if (temp.receiverId[i] == '\0') {
			continue;
		}
		while (true) {
			if (temp.receiverId[i] == ',') { temp.receiverId[i] = '\0'; i = 0; break; }
			else if (temp.receiverId[i] == EOF) {
				fclose(fp);
				return m_arr;
			}
			i++;
			temp.receiverId[i] = fgetc(fp);
		}
		while (true) {
			temp.senderId[i] = fgetc(fp);
			if (temp.senderId[i] == ',') { temp.senderId[i] = '\0'; i = 0; break; }
			else if (temp.senderId[i] == EOF) {
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
	const char* pattern = "^([A-Za-z0-9가-힣.?,()!]||[[:blank:]]){1,200}$";

	regcomp(&state, pattern, REG_EXTENDED);
	return regexec(&state, string, 0, NULL, 0) ? false : true;
}
int sendMessage(char* sender, char* receiver) {
	
	FILE* fp;
	fp = fopen("./message.txt", "at"); // 같은 프로젝트 파일 내에 존재하면 쓸 필요X
	if (fp == NULL)
	{
		printf("파일 입출력 실패.\n");
		return;
	}


	system("cls");

	char ch, input[401] = { 0, };
	unsigned int i = 0;
	int x = 20, y = 5;
	int cy = 10;

	bool checkk = false; // true일 경우 '더이상 입력하지 못합니다' 란 문구가 출력되어 있는 상태였으므로 이 문구 지우기.
	int k = 0;

	// 변수 i는 입력받게 될 배열의 위치
	// 변수 k는 입력받은 글자수

	gotoxy(2, cy);
	printf("▶");

	gotoxy(0, y);
	printf("Message -> ");
	gotoxy(10, 3);
	for (int j = 0; j <= 85; j++) {
		printf("-");
	}
	for (int j = 4; j <= 18; j++) {
		gotoxy(10, j);
		printf("|");
		gotoxy(95, j);
		printf("|");
	}
	gotoxy(10, 19);
	for (int j = 0; j <= 85; j++) {
		printf("-");
	}

	gotoxy(70, 20);
	printf("%d/200", k);

	gotoxy(35, 25);
	printf("┌-------------------------------┐\n");
	gotoxy(35, 26);
	printf("│             Back              │\n");
	gotoxy(35, 27);
	printf("└-------------------------------┘\n");

	gotoxy(x, y);
	while (1) { //계속 반복해서 작동


		if (_kbhit()) {
			if (x > 80) { // x값이 80 초과하게 되면 자동으로 줄 바꿈(다음 줄로 넘어감)
				x = 20;
				y += 2; // 1줄만 뛰었을 경우 가독성이 불편해보여 2줄을 뛰움
			}

			if (checkk == true) {
				gotoxy(40, 24);
				printf("                             ");
				checkk = false;
			}


			ch = _getch(); // 입력값을 ch에 저장
			if (i == 0 && ch == '~') { // 첫번째 칸일 경우 ~을 입력하면 뒤로 돌아감.
				gotoxy(x, y);
				printf("~");
				gotoxy(30, 30);
				printf("Back to User Search.");
				gotoxy(30, 31);
				system("pause");
				return 0;  // 합칠때 리턴값을 통하여 돌아갈 위치 정하기 #######################################################################
			}
			else if (ch == 13) { // 아스키코드로 enter
				break;
			}
			else if (ch == 8 && i >= 0) {      // backspace
				if (i == 0) {
					gotoxy(x, y);
					continue;
				}
				if (x == 20) { // 줄바꿈을 고려하여 x,y값을 변경
					x = 81;
					y -= 2;
				}
				gotoxy(--x, y);
				printf(" ");
				printf("\b");
				i--;
				k--;
				/*if (input[i] & 0x80) { // 한글일 경우 배열 2칸을 지워야함.
					input[i--] = 0;
					input[i] = 0;
					gotoxy(--x, y);
					printf(" ");
					printf("\b");
					gotoxy(x, y);
				}*/
				input[i] = 0;
				gotoxy(x, y);
			}
			else if (i >= 400 || k >= 200) { // -> 최대 입력 갯수 제한
				while (_kbhit()) {
					_getch();
				}
				gotoxy(40, 24);
				printf("Maximum is 200.");
				checkk = true;
				gotoxy(x, y);
				continue;
			}
			else if (ch == -32) { // 방향키 및 f11, f12 제한
				if (_kbhit()) {
					ch = _getch();
					if (ch == DOWN || ch == UP) {
						if (cy == 10 && ch == DOWN) {
							gotoxy(2, cy);
							printf(" ");
							cy = 26;
							gotoxy(32, cy);
							printf("▶");
							while (1) {
								if (_kbhit()) {
									ch = _getch();
									if (ch == 13) {
										return 1; //합칠때 리턴값을 통하여 돌아갈 위치 정하기 #######################################################################
									}
									else if (ch == -32) {
										ch = _getch();
										if (ch == UP) {
											gotoxy(32, cy);
											printf(" ");
											cy = 10;
											gotoxy(2, cy);
											printf("▶");
											break;
										}
									}
									else {

									}
								}
							}
						}
						continue;
					}
					gotoxy(30, 29);
					printf("Character that is not allowed is included.");
					gotoxy(10, 30);
					printf("Allowed Characters: English, Number, ‘?’, ‘!’, ‘.’, ‘,’, ‘(‘, ‘)’, Spaceing Word");
					gotoxy(30, 31);
					system("pause");
					gotoxy(30, 29);
					printf("                                                  ");
					gotoxy(30, 30);
					printf("                                                                                        ");
					gotoxy(30, 31);
					printf("                                        ");
					gotoxy(x, y);
					continue;
				}
			}
			else if (ch & 0x80) { // 한글 ;
				while(_kbhit()) {
					_getch();
				}
				gotoxy(30, 29);
				printf("Character that is not allowed is included.");
				gotoxy(10, 30);
				printf("Allowed Characters: English, Number, ‘?’, ‘!’, ‘.’, ‘,’, ‘(‘, ‘)’, Spaceing Word");
				gotoxy(30, 31);
				system("pause");
				gotoxy(30, 29);
				printf("                                                  ");
				gotoxy(30, 30);
				printf("                                                                                        ");
				gotoxy(30, 31);
				printf("                                        ");
				gotoxy(x, y);
				continue;
			}
			else if (isalnum(ch) || (ch == '.') || (ch == ',') || (ch == '?') || (ch == '(') || (ch == ')') || (ch == '!') || (ch == 32)) { // 한글 이외이 것

				input[i] = ch;
				i++;
				k++;
				gotoxy(x++, y);
				printf("%c", ch);
				gotoxy(x, y);
			}
			else {
				while (_kbhit()) { // f1 ~ f10사이의 키 입력이 출력되는 경우가 있어 제한하기 위해 추가.
					_getch();
				}
				gotoxy(30, 29);
				printf("Character that is not allowed is included.");
				gotoxy(10, 30);
				printf("Allowed Characters: English, Number, ‘?’, ‘!’, ‘.’, ‘,’, ‘(‘, ‘)’, Spaceing Word");
				gotoxy(30, 31);
				system("pause");
				gotoxy(30, 29);
				printf("                                                  ");
				gotoxy(30, 30);
				printf("                                                                                        ");
				gotoxy(30, 31);
				printf("                                        ");
				gotoxy(x, y);
			}

			gotoxy(70, 20);
			printf("              ");
			gotoxy(70, 20);
			printf("%d/200", k);

			gotoxy(x, y);
		}

	}


	gotoxy(30, 30);
	printf("The message was sent successfully.");
	gotoxy(30, 31);
	system("pause");


	fputs(receiver, fp); // 쪽지 보내는 사람 즉 지금 로그인 한 사람 닉네임
	fputs(",", fp);
	fputs(sender, fp); // 쪽지 받는 사람 닉네임
	fputs(",1,", fp); // 0 읽음   #  1 안 읽음
	fputs(input, fp);
	fputs("\n", fp);
	fclose(fp);
	return 0;  // ############################################################## 수정
}
void showMessage(Message* m, char* id, int count, int index) {
	int flag = count - index - 1;
	while (true) {
		system("cls");
		gotoxy(40, 1);
		printf("Check Message");
		gotoxy(10, 3);
		printf("Sender : %s", m[flag].senderId);
		gotoxy(10, 5);
		printf("Content : ");
		if (strlen(m[flag].text) > 160) {
			for (int i = 0; i < 80; i++) {
				printf("%c", m[flag].text[i]);
			}
			gotoxy(22, 6);
			for (int i = 80; i < 160; i++) {
				printf("%c", m[flag].text[i]);
			}
			gotoxy(22, 7);
			for (int i = 160; i < strlen(m[flag].text); i++) {
				printf("%c", m[flag].text[i]);
			}
		}
		else if (strlen(m[flag].text) > 80) {
			for (int i = 0; i < 80; i++) {
				printf("%c", m[flag].text[i]);
			}
			gotoxy(22, 6);
			for (int i = 80; i < strlen(m[flag].text); i++) {
				printf("%c", m[flag].text[i]);
			}
		}
		else {
			printf("%s", m[flag].text);
		}
		gotoxy(3, 25);
		printf("┌------------------┐");
		gotoxy(3, 26);
		printf("│       Reply      │");
		gotoxy(3, 27);
		printf("└------------------┘");
		gotoxy(33, 25);
		printf("┌------------------┐");
		gotoxy(33, 26);
		printf("│  Delete Message  │");
		gotoxy(33, 27);
		printf("└------------------┘");
		gotoxy(63, 25);
		printf("┌------------------┐");
		gotoxy(63, 26);
		printf("│       Back       │");
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
			sendMessage(id, m[flag].senderId);
			return;
		}
		if (triangle == 31) {
			system("cls");
			deleteMessage(id, count, flag);
			return;
		}
		if (triangle == 61) {
			return;
		}
	}
}
Message* showMessageList(char* id) {
	int count = countMessage(id);
	Message* m = readMessageFile(id, count);
	if (count > 0 && count < 10) {
		int line = 0;
		for (int i = count - 1; i >= 0; i--) {
			if (m[i].read) {
				gotoxy(34, 5 + (line * 2));
				printf("Unread");
			}
			else {
				gotoxy(35, 5 + (line * 2));
				printf("Read");
			}
			gotoxy(50, 5 + (line * 2));
			printf("%s", m[i].senderId);
			gotoxy(70, 5 + (line * 2));
			if (strlen(m[i].text) > 11) {
				for (int j = 0; j < 10; j++) {
					printf("%c", m[i].text[j]);
				}
				printf("...");
			}
			else {
				printf("%s", m[i].text);
			}
			line++;
		}
	}
	else if (count >= 10) {
		int line;
		for (int i = count - 1; i > count - 11; i--) {
			line = count - i - 1;
			if (m[i].read) {
				gotoxy(34, 5 + (line * 2));
				printf("Unread");
			}
			else {
				gotoxy(35, 5 + (line * 2));
				printf("Read");
			}
			gotoxy(50, 5 + (line * 2));
			printf("%s", m[i].senderId);
			gotoxy(70, 5 + (line * 2));
			if (strlen(m[i].text) > 10) {
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
		printf("Message Box is empty!");
	}
	return m;
}
int findLine(char* id, int count, int flag) {
	FILE* fp;
	char temp[TEXT_MAXSIZE];
	int i = 0;
	int counter = 0;
	int line = 1;
	int ch = 0;

	fp = fopen("./message.txt", "r+");
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		exit(1);
	}
	while (true) {
		char temp_id[ID_MAXSIZE + 2] = "";
		temp_id[i] = fgetc(fp);
		if (temp_id[i] == '\0') {
			continue;
		}
		while (true) {
			if (temp_id[i] == ',') {
				temp_id[i] = '\0';
				i = 0;
				break;
			}
			i++;
			temp_id[i] = fgetc(fp);
		}
		if (!strcmp(temp_id, id)) {
			counter++;
			if (counter == flag + 1) {
				fclose(fp);
				return line;
			}
			else {
				fgets(temp, TEXT_MAXSIZE, fp);
			}
		}
		else {
			fgets(temp, TEXT_MAXSIZE, fp);
		}
		line++;
	}
	fclose(fp);
}
void deleteMessage(char* id, int count, int flag) {
	FILE* fp;

	fp = fopen("./message.txt", "r+");
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		exit(1);
	}
	int lineCounter = 1;
	int line = findLine(id, count, flag);
	char temp[MAX_LINE_LENGTH_MSG];
	fpos_t position = 0;

	while (lineCounter != line) {
		fgets(temp, MAX_LINE_LENGTH_MSG, fp);
		lineCounter++;
	}
	fgetpos(fp, &position);

	char temp1[MAX_LINE_LENGTH] = "";
	int counter = 0;
	while (true) {
		temp1[counter] = fgetc(fp);
		if (temp1[counter] == EOF || temp1[counter] == '\n') {
			break;
		}
		temp1[counter] = ' ';
		counter++;
	}
	fseek(fp, position, SEEK_SET);
	fwrite(temp1, counter, 1, fp);

	fclose(fp);
}
void readMessage(char* id, int count, int index) {
	FILE* fp;
	char temp[TEXT_MAXSIZE];
	int i = 0;
	int flag = count - index - 1;
	int counter = 0;
	int ch;

	fp = fopen("./message.txt", "r+");
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		exit(1);
	}
	while (true) {
		char temp_id[ID_MAXSIZE + 2] = "";
		temp_id[i] = fgetc(fp);
		if (temp_id[i] == '\0') {
			continue;
		}
		while (true) {
			if (temp_id[i] == ',') {
				temp_id[i] = '\0';
				i = 0;
				break;
			}
			else if (temp_id[i] == EOF) {
				fclose(fp);
				return;
			}
			i++;
			temp_id[i] = fgetc(fp);
		}
		if (!strcmp(temp_id, id)) {
			if (counter == flag) {
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
				fseek(fp, 0, SEEK_CUR);//없으면 오류 발생
				fputs("0", fp);
				fseek(fp, 0, SEEK_CUR);//없으면 오류 발생
				fclose(fp);
				return;
			}
			else{
				fgets(temp, TEXT_MAXSIZE, fp);
			}
			counter++;
		}
		else {
			fgets(temp, TEXT_MAXSIZE, fp);
		}
	}
	fclose(fp);
}
void messageBox(char* id) {
	while (true) {
		system("cls");
		Message* m = showMessageList(id);
		gotoxy(1, 1);
		gotoxy(57, 1);
		printf("Message Box");
		gotoxy(35, 3);
		printf("Status");
		gotoxy(50, 3);
		printf("Sender");
		gotoxy(70, 3);
		printf("Content");
		gotoxy(48, 25);
		printf("┌------------┐");
		gotoxy(48, 26);
		printf("│    Back    │");
		gotoxy(48, 27);
		printf("└------------┘");

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
			readMessage(id, count, index);
			showMessage(m, id, count, index);
		}
		else if (triangleY == 26) {
			break;
		}
	}
}
