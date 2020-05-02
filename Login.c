#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int readMessage(const char* _string) {
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

void writeMessage() {
	char* s_Nickname = "아리게리";
	char* ID_nickname = "Arigeri"; // 가상으로 만든 보내는 사람 이름
	//구조체를 통해 tt.nickname;



	system("cls");

	char ch, input[401] = { 0, };
	unsigned int i = 0;
	int x = 20, y = 5;
	bool checkk = false;
	int k = 0;
	// 변수 i는 입력받게 될 숫자의 갯수
	// 변수 k는 입력받은 -의 갯수


	gotoxy(0, y);
	printf("쪽지 -> ");
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
	printf("│           뒤로 가기           │\n");
	gotoxy(35, 27);
	printf("└-------------------------------┘\n");

	gotoxy(x, y);
	while (1) { //계속 반복해서 작동


		if (_kbhit()) {
			if (x > 80) { // x값이 80 초과하게 되면 자동으로 줄 바꿈(다음 줄로 넘어감)
				x = 20;
				y += 2; // 1줄만 뛰었을 경우 가독성이 불편해보여 수정함
			}
			if (checkk == true) {
				gotoxy(40, 24);
				printf("                             ");
				checkk = false;
			}


			ch = getch(); // 입력값을 ch에 저장
			if (i == 0 && ch == '~') { // 첫번째 칸일 경우 ~을 입력하면 뒤로 돌아감.
				return;
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
				if (input[i] & 0x80) { // 한글일 경우 배열 2칸을 지워야함.
					input[i--] = 0;
					input[i] = 0;
					gotoxy(--x, y);
					printf(" ");
					printf("\b");
					gotoxy(x, y);
				}
				else {
					input[i] = 0;
					gotoxy(x, y);
				}
			}
			else if (i >= 400 || k >= 200) { // -> 최대 입력 갯수 제한
				while (kbhit()) {
					getch();
				}
				gotoxy(40, 24);
				printf("더이상 입력하지 못합니다\n");
				checkk = true;
				gotoxy(x, y);
				continue;
			}
			else if (ch == -32) { // 방향키 및 f11, f12 제한
				if (kbhit()) {
					ch = getch();
					gotoxy(30, 30);
					printf("혀용되지 않는 문자가 포함되었습니다..\n");
					gotoxy(30, 31);
					system("pause");
					gotoxy(30, 30);
					printf("                                       ");
					gotoxy(30, 31);
					printf("                                       ");
					gotoxy(x, y);
					continue;
				}
			}
			else if (ch & 0x80) { // 한글 -> 일부분 문제가 존재하나 한계가 있어서 패스;
				input[i++] = ch;
				if (kbhit()) {
					ch = getch();
					input[i++] = ch;
					int g = i - 2;
					gotoxy(x, y);

					printf("%c%c", input[g], input[g + 1]);
					k++;
					x += 2;
					gotoxy(x, y);
				}
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
				while (kbhit()) { // f1 ~ f10사이의 키 입력이 출력되는 경우가 있어 제한하기 위해 추가.
					getch();
				}
				gotoxy(30, 30);
				printf("혀용되지 않는 문자가 포함되었습니다.\n");
				gotoxy(30, 31);
				system("pause");
				gotoxy(30, 30);
				printf("                                       ");
				gotoxy(30, 31);
				printf("                                       ");
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
	printf("쪽지를 성공적으로 보냈습니다.");

	gotoxy(30, 31);
	system("pause");
	return;
}

int main1(int argc, char* argv[])
{
	//system("title 회원가입 테스트");
	//system("mode con cols=80 lines=8");
	//writeMessage();
	//char a[200]; 
	//fgets(a, 200, stdin);
	//a[strcspn(a, "\n")] = 0;
	readMessage("testID");
	//system("color f0");

	/*if (matchMessage(a)) {
		printf("쪽지 매칭");
	}
	else printf("쪽지 매칭X");*/
	Account user = {0,};
	//char a[] = "abba";
	//if (isRepeat(a, strlen(a))) {
	//	printf("문자열%s는 반복", a);
	//}
	//else {
	//	printf("문자열%s는 반복X", a);
	//}
	//signUp(user);

	/*for (int i = 0;i < 10;i++) ret("testID");
	if (duplicateCheck("testID", IDCHECK)) {
		printf("중복");
		
	}
	else {
		printf("중복X");
	}*/
	//showUserInformation(user);
	//uiMainMenu();
	//duplicateCheck("abcdeabcde12", NICKNAMECHECK);
	//if (duplicateCheck("abcdeabcde12", IDCHECK)) {
	//	printf("중복");
	//}
	//else {
	//	printf("중복X");
	//}
	//signUp(user);
	//AccountToFile(user);
	/*char a[18];
	fgets(a, 18, stdin);
	a[strcspn(a, "\n")] = 0;
	if (matchPassword(a)) {
		printf("match");
	}
	else { printf("unmatch"); }*/
	//Eliminate(a, '-');
	//printf("a: %s\nstrlen(a): %d", a, strlen(a));
	
	/*
	// 완전한 한글인지 판별하는 테스트 코드
	static const char* const initial_array[] = {
"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ",
"ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"
	};
	regex_t regex;
	char a[14];
	int reti;
	char msgbuf[100];
	char b[3] = "";
	char* check = initial_array[0];

	fgets(a, 12, stdin);
	a[strcspn(a, "\n")] = 0;
	
	if (matchkorean(a, strlen(a))&&iscompletekorean(a, strlen(a))) {
		printf("완전한 한글입니다.");
	}
	else {
		printf("완전한 한글을 입력해주세요.");
	}*/
	
	
	/*while (true) {
		printf("글자 입력: ");
		fgets(a, 14, stdin);
		a[strcspn(a, "\n")] = 0;
		if (strlen(a) > 12) {
			clearInputBuffer();
		}
		printf("글자 수: %d\n", getLength(a, sizeof(a)));
	}
	*/

	//input();
	//fgets(u1.email, 50, stdin);

	//regex_t state;
	/*char* urls[] = {
	  "vng598@gmail.com",
	  "vngrjqnrdl@naver.com",
	  "vng598@knokuk.ac.kr"
	};
	const char* pattern = "^[a-zA-Z0-9_.-]*@[a-zA-Z0-9.-]+$";

	int index;
	//compile
	regcomp(&state, pattern, REG_EXTENDED);

	for (index = 0; index < 3; index++) {
		//check
		if (matchEmail(urls[index])) {
			printf("match: %s\n", urls[index]);
		}
		else
			printf("unmatch: %s\n", urls[index]);
	}
	*/
	/*printf("아이디를 입력해주세요\n");
	fgets(u1.id, 20, stdin);
	u1.id[strcspn(u1.id, "\n")] = 0;
	if (strlen(u1.id) < 4 || strlen(u1.id) > 13) {
		printf("글자수 조건을 만족해주세요.\n");
	}
	else {
		if (matchId(u1.id, userId))
			printf("아이디 생성이 완료되었습니다.");
		else {
			printf("올바른 문자를 입력해주세요.");
		}
	}
	printf("\n");
	fflush(stdin);

	printf("이메일을 입력해주세요\n");
	fgets(u1.email, 50, stdin);
	printf("\n%s\n", u1.email);
	u1.email[strcspn(u1.email, "\n")] = 0;
	if (matchEmail(u1.email)) {
		printf("이메일 입력이 완료되었습니다.\n");
	}
	else {
		printf("올바른 이메일 형식을 입력해주세요.\n");
	}
	printf("전화번호를 입력해주세요\n");
	fgets(u1.phone, 20, stdin);
	u1.phone[strcspn(u1.phone, "\n")] = 0;
	if (matchPhoneNumber(u1.phone)) {
		printf("전화번호 입력이 완료되었습니다.\n");
	}
	else {
		printf("올바른 전화번호 형식을 입력해주세요\n");
	}
	printf("비밀번호를 입력해주세요\n");
	fgets(u1.pw, 20, stdin);
	u1.pw[strcspn(u1.pw, "\n")] = 0;
	if (matchPassword(u1.pw)) {
		printf("비밀번호 입력이 완료되었습니다.\n");
	}
	else {
		printf("올바른 비밀번호 형식을 입력해주세요\n");
	}
	printf("\n[한글 입력 판단]\n");
	if (matchKorean(u1.id, strlen(u1.id))) printf("1. 아이디에 한글이 있습니다.\n");
	else printf("1. 아이디에 한글이 없습니다.\n");

	if (matchKorean(u1.email, strlen(u1.email))) printf("1. 이메일에 한글이 있습니다.\n");
	else printf("1. 이메일에 한글이 없습니다.\n");
	*/
	return 0;
}



int main() {

	FILE* memlist;
	
	memlist = fopen("./accountlist.txt", "r");
	if (memlist == NULL)
	{
		printf("파일 읽기 실패\n");
		exit(1);
	}

	char c = ' ';
	char account_id[num_account][13] = { 0, }; // 배열 세로는 char account_id[num_account][12];
	char account_password[100][17] = { 0, };

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
				break;
			}
			else
				printf("비밀번호가 틀립니다.");
			break;
		}

		if (i == 1)
			printf("존재하지 않는 아이디 입니다");
	}




	fclose(memlist);
}
