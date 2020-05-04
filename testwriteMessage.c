int writeMessage(char *ID_Nickname,char *s_Nickname) { // 현재 로그인 한 사람의 정보 / 쪽지 받을 사람의 닉네임.
	
	//tt.nick;
	
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
				y+=2; // 1줄만 뛰었을 경우 가독성이 불편해보여 2줄을 뛰움
			}

			if (checkk == true) {
				gotoxy(40, 24);
				printf("                             ");
				checkk = false;
			}
			ch = getch(); // 입력값을 ch에 저장
			if (i == 0 && ch == '~') { // 첫번째 칸일 경우 ~을 입력하면 뒤로 돌아감.
				gotoxy(x, y);
				printf("~");
				gotoxy(30, 30);
				printf("사용자 검색 메뉴로 이동합니다.");
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
					y-= 2;
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
					if (ch == DOWN || ch == UP) {					
						if (cy == 10 && ch == DOWN) {
							gotoxy(2, cy);
							printf(" ");
							cy = 26;
							gotoxy(32, cy);
							printf("▶");
							while (1){
								if (kbhit()) {
									ch = getch();
									if (ch == 13) {
										return 0; //합칠때 리턴값을 통하여 돌아갈 위치 정하기 #######################################################################
									}
									else if (ch == -32) {
										ch = getch();
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
			else if (ch & 0x80) { // 한글 ;
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
			else if (isalnum(ch) ||  (ch == '.') || (ch == ',') || (ch == '?') || (ch == '(') || (ch == ')') || (ch == '!') || (ch == 32)) { // 한글 이외이 것					
					input[i] = ch;
					i++;
					k++;
					gotoxy(x++, y);
					printf("%c", ch);
					gotoxy(x, y);
			}
			else {
				while (kbhit()){ // f1 ~ f10사이의 키 입력이 출력되는 경우가 있어 제한하기 위해 추가.
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

	
	//fputs(tt.nick, fp);
	fputs(ID_Nickname, fp); // 쪽지 보내는 사람 즉 지금 로그인 한 사람 닉네임
	fputs(",",fp);
	fputs(s_Nickname, fp); // 쪽지 받는 사람 닉네임
	fputs(",1,", fp); // 0 읽음   #  1 안 읽음
	fputs(input, fp);
	fputs("\n",fp);
	fclose(fp);
	
	return 0;
}


// 앞서 만들어진 내용에 따라 return 값에 변화를 주는 방식을 이용하기.

