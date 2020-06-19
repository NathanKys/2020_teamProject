#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#pragma warning(disable:4098)

int checkPW(char* pw) {

	while (1) {
		system("cls");

		gotoxy(5, 5);
		printf("For your security, you must re-enter your password to continue.");
		gotoxy(7, 8);
		printf("-----------------------------------------------");
		gotoxy(6, 9);
		printf("-> ");
		gotoxy(7, 10);
		printf("-----------------------------------------------");
		gotoxy(9, 9);

		char t_pw[16] = "";
		char temp = ' ';
		for (int i = 0; i < 16; i++) {
			scanf("%c", &temp);
			if (temp == '\n') {
				break;
			}
			t_pw[i] = temp;
		}
		if (t_pw[0] == '~') {
			return 0;
		}
		if (!strcmp(pw, t_pw)) {
			return 1;
		}
		else {
			gotoxy(7, 11);
			printf("Password is incorrect.");
			system("pause");
		}
	}

}

void selectEdit(Account* login, int login_id_num) {

	while (1) {
		system("cls");

		gotoxy(5, 3);
		printf("===================================================================================");
		gotoxy(5, 4);
		printf("\t\t\t\t\tChange My Info"); // 텝 5개
		gotoxy(5, 5);
		printf("===================================================================================");

		gotoxy(40, 7);
		printf("Password(0)");

		gotoxy(20, 9);
		printf("ID");
		gotoxy(20, 10);
		printf("%s\t", (*login).id);

		gotoxy(40, 9);
		printf("Name(1)");
		gotoxy(40, 10);
		printf("%s\t", (*login).name);

		gotoxy(61, 9);
		printf("Nickname(2)");
		gotoxy(61, 10);
		printf("%s\t", (*login).nick);

		gotoxy(20, 12);
		printf("Date of Birth(4)");
		gotoxy(20, 13);
		for (int i = 0; i < 8; i++) {
			printf("%d", (*login).birth[i]);
		}

		gotoxy(40, 12);
		printf("Phone Number(5)");
		gotoxy(40, 13);
		if ((*login).phone[10] == -1) {
			for (int i = 0; i < 10; i++) {
				printf("%d", (*login).phone[i]);
			}
		}
		else {
			for (int i = 0; i < 11; i++) {
				printf("%d", (*login).phone[i]);
			}
		}

		gotoxy(61, 12);
		printf("Email Address(3)");
		gotoxy(61, 13);
		printf("%s\t", (*login).email);

		gotoxy(10, 16);
		printf("Enter the item number you want to change.: ");

		char num;
		scanf("%c", &num);
		char c = ' ';
		char test = ' ';
		scanf("%c", &test);
		while (test != '\n') {
			scanf("%c", &c);
			if (c == '\n')
				break;
		}
		if (num == '~')
			return;
		num = num - 48;
		if (!(0 <= num && num <= 5) || test != '\n') {
			gotoxy(10, 17);
			printf("Item number entered doesn't exist.\n");
			gotoxy(10, 18);
			system("pause");
		}
		else {
			switch (num) {
				case 0:	//비밀번호
					writeBreakdownChar(num, &((*login).id), &((*login).pw));
					editPW(&((*login).pw));
					break;
				case 1:	//이름
					writeBreakdownChar(num, &((*login).id), &((*login).name));
					editName(&((*login).name));
					break;
				case 2:	//닉네임
					writeBreakdownChar(num, &((*login).id), &((*login).nick));
					editNick(&((*login).nick));
					break;
				case 3:	//이메일 주소
					writeBreakdownChar(num, &((*login).id), &((*login).email));
					editEmail(&((*login).email));
					break;
				case 4:	//생년월일
					writeBreakdownInt(num, &((*login).id), &((*login).birth));
					editBirth(&((*login).birth));
					break;
				case 5:	//휴대폰 번호
					writeBreakdownInt(num, &((*login).id), &((*login).phone));
					editPhone(&((*login).phone));
					break;
			}
			writeAccountInfo(login_id_num, login);
		}

	}
}

void writeBreakdownChar(int num, char* id, char* info) {
	FILE* fp;
	fp = fopen("./breakdown.txt", "a");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	char out[50];
	char cnum[2];
	strcpy(out, id);
	strcat(out, ",");
	sprintf(cnum, "%d", num);
	strcat(out, cnum);
	strcat(out, ",");
	strcat(out, info);
	strcat(out, "\n");
	fputs(out, fp);
	fclose(fp);
}
void writeBreakdownInt(int num, char* id, int* info) {
	FILE* fp;
	fp = fopen("./breakdown.txt", "a");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
	char out[50];
	char cnum[2];
	char temp[12];
	strcpy(out, id);
	strcat(out, ",");
	sprintf(cnum, "%d", num);
	strcat(out, cnum);
	strcat(out, ",");

	if (num == 4) {
		for (int i = 0; i < 8; i++) {
			temp[i] = info[i] + 48;
		}
		temp[8] = 0;
	}
	else {
		int i = 0;
		for (i = 0; i < 11; i++) {
			if (info[i] == -1)
				break;
			temp[i] = info[i] + 48;
		}
		temp[i] = 0;
	}

	strcat(out, temp);
	strcat(out, "\n");
	fputs(out, fp);
	fclose(fp);
}

void editPW(char* pw) {

	char t_pw[PASSWORD_MAXSIZE + 2] = "";

	// 비밀번호 입력
	while (true) {
		system("cls");
		printf("Password must contain at least one uppercase letter, one lowercase letter and one number.(8-16)\n");
		printf("Do not allow special characters except for the following characters : !@#$%^&*\n");
		printf("Please enter a new Password.: ");
		fgets(t_pw, PASSWORD_MAXSIZE + 2, stdin);

		t_pw[strcspn(t_pw, "\n")] = 0;

		// 메뉴로 이동
		if (t_pw[0] == '~' && strlen(t_pw) == 1) {
			return;
		}
		if (strlen(t_pw) > PASSWORD_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(pw, t_pw)) {
			printf("It same as current info.");
			system("pause");
			continue;
		}

		if (matchPassword(t_pw)) {
			if (strlen(t_pw) < 8 || strlen(t_pw) > 16) {
				printf("String has been out of range.(8-16)\n");
				system("pause");
				continue;
			}
			else {
				// 대문자 하나 이상
				// 소문자 하나 이상
				// 숫자 하나 이상
				if (!isContainUpperCase(t_pw)) { printf("You must include at least one alphabetic uppercase letter.\n"); }
				if (!isContainLowerCase(t_pw)) { printf("You must include at least one alphabetic lowercase letter.\n"); }
				if (!isContainNumber(t_pw)) { printf("You must include at least one Hindu - Arabic number.\n"); }

				// 위의 세 조건을 모두 만족할 때
				if (isContainNumber(t_pw) && isContainUpperCase(t_pw) && isContainLowerCase(t_pw)) {
					// 반복된 문자 체크
					if (isRepeat(t_pw, strlen(t_pw))) {
						printf("String contains repeated characters.\n");
						system("pause");
						continue;
					}
					// 연속된 문자 체크
					if (isConti(t_pw, strlen(t_pw))) {
						printf("String contains consecutive characters.\n");
						system("pause");
						continue;
					}

					printf("Success.\n");
					system("pause");
					break;
				}
				system("pause");
				continue;
			}

		}
		else {
			printf("Do not allow special characters except for the following characters : !@#$%^&*\n");
			system("pause");
			continue;
		}


	}

	//비밀번호 확인
	while (true) {
		system("cls");
		char checkPassword[PASSWORD_MAXSIZE + 2] = { 0, };
		printf("Reenter your Password for Password confirmation.");
		fgets(checkPassword, PASSWORD_MAXSIZE + 2, stdin);
		checkPassword[strcspn(checkPassword, "\n")] = 0;
		if (strlen(checkPassword) > PASSWORD_MAXSIZE) {
			clearInputBuffer();
		}

		// 메뉴로 이동
		if (checkPassword[0] == '~' && strlen(checkPassword) == 1) {
			return;
		}

		if (!strcmp(checkPassword, t_pw)) {
			strcpy(pw, t_pw);
			printf("Password has been changed successfully.\n");
			system("pause");
			break;
		}
		else {
			printf("Password confirmation doesn't match Password. Please try again.\n");
			system("pause");
			continue;
		}
	}
	
}

void editName(char* name) {

	char t_name[NAME_MAXSIZE + 2] = "";
	// 이름 입력
	while (true) {
		system("cls");
		gotoxy(0, 0);
		printf("Name contains blank space and alphabetic upper and lower case characters.(3-20)\n");

		printf("Please enter a new Name.: ");
		fgets(t_name, NAME_MAXSIZE + 2, stdin);
		t_name[strcspn(t_name, "\n")] = 0;

		gotoxy(0, 4);
		// 메뉴로 이동
		if (t_name[0] == '~' && strlen(t_name) == 1) {
			return;
		}
		if (strlen(t_name) > NAME_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(name, t_name)) {
			printf("It same as current info.");
			system("pause");
			continue;
		}

		if (matchEngName(t_name)) {
			if (getLength(t_name) >= 3 && getLength(t_name) <= 20) {
				strcpy(name, t_name);
				printf("Name has been changed successfully.\n");
				system("pause");
				break;
			}
			else {
				printf("You must enter 3 to 20 characters, include blank spaces.\n");
				system("pause");
				continue;
			}
		}
		else {
			printf("Please enter a validated character.\n");
			system("pause");
			continue;
		}
	}

}

void editNick(char* nick) {

	char t_nick[NICKNAME_MAXSIZE + 2] = "";

	// 닉네임 입력
	while (true) {
		system("cls");
		gotoxy(0, 0);
		printf("Nickname can include English, numbers and blank spaces.(2-12)\n");
		printf("Please enter a new Nickname.: ");

		fgets(t_nick, NICKNAME_MAXSIZE + 2, stdin);
		t_nick[strcspn(t_nick, "\n")] = 0;

		gotoxy(0, 3);
		if (t_nick[0] == '~' && strlen(t_nick) == 1) {
			// 메뉴로 이동
			return;
		}
		if (strlen(t_nick) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(nick, t_nick)) {
			printf("It same as current info.");
			system("pause");
			continue;
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(t_nick, NICKNAMECHECK)) {
			printf("Overlapped nickname, Please check again.\n");
			system("pause");
			continue;
		}
		if (getLength(t_nick) < 2 || getLength(t_nick) > 12) {
			printf("Nickname must be 2 to 12 characters with English and numeric characters.\n");
			system("pause");
			continue;
		}
		if (matchNickname(t_nick)) {
			strcpy(nick, t_nick);
			printf("Nickname has been changed successfully.\n");
			system("pause");
			break;
		}
		else {
			printf("Please enter a validated character.\n");
			system("pause");
			continue;
		}

	}

}

void editEmail(char* email) {

	char t_email[EMAILADDRESS_MAXSIZE + 2] = "";
	// 이메일 주소 입력
	while (true) {
		system("cls");
		printf("Please enter a new Eamil Address.: ");

		fgets(t_email, EMAILADDRESS_MAXSIZE + 2, stdin);
		t_email[strcspn(t_email, "\n")] = 0;

		// 메뉴로 이동
		if (t_email[0] == '~' && strlen(t_email) == 1) {
			return;
		}
		if (strlen(t_email) > EMAILADDRESS_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(email, t_email)) {
			printf("It same as current info.");
			system("pause");
			continue;
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(t_email, EMAILCHECK)) {
			printf("Overlapped Email, please check again.\n");
			system("pause");
			continue;
		}

		if (getLength(t_email) > 30) {
			printf("The maximum total length of a email address is 30 characters.\n");
			system("pause");
			continue;
		}

		if (matchEmail(t_email)) {
			strcpy(email, t_email);
			printf("Email Address has been changed successfully.\n");
			system("pause");
			break;
		}
		else {
			printf("Please enter a validated email address.\n");
			system("pause");
			continue;
		}
	}

}

void editBirth(int* birth) {

	char tempBirthNumber[BIRTHDAY_MAXSIZE + 2];
	//생년월일 입력
	while (true) {
		system("cls");
		printf("Please enter a new Date of Birth.: ");

		fgets(tempBirthNumber, BIRTHDAY_MAXSIZE + 2, stdin);
		tempBirthNumber[strcspn(tempBirthNumber, "\n")] = 0;

		// 메뉴로 이동
		if (tempBirthNumber[0] == '~' && strlen(tempBirthNumber) == 1) {
			return;
		}
		if (strlen(tempBirthNumber) > BIRTHDAY_MAXSIZE) {
			clearInputBuffer();
		}
		if (tempBirthNumber[8] == '\0') {
			bool flag = 1;
			for (int i = 0; i < 8; i++) {
				if (birth[i] != (tempBirthNumber[i] - 48)) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				printf("It same as current info.");
				system("pause");
				continue;
			}
		}

		if (isOnlyNumber(tempBirthNumber)) {
			if (strlen(tempBirthNumber) > 8) {
				printf("String has out of range(8).\n");
				system("pause");
				continue;
			}
			else if (strlen(tempBirthNumber) == 8) {
				if (!isRightDate(tempBirthNumber)) {
					printf("Inexistent form of date, please check again.\n");
					system("pause");
					continue;
				}
			}
		}
		if (matchBirthday(tempBirthNumber)) {
			// 윤년 고려해서 없는 날짜 판단
			if (isInTheFuture(tempBirthNumber)) {
				printf("Invalidated date of birth, please check again.\n");
				system("pause");
				continue;
			}
			// 프로그램 실행 이후 날짜 판단
			if (!isRightDate(tempBirthNumber)) {
				printf("Inexistent form of date, please check again.\n");
				system("pause");
				continue;
			}
			//strcpy_s(birth, BIRTHDAY_MAXSIZE + 2, tempBirthNumber);
			for (int i = 0; i < BIRTHDAY_MAXSIZE; i++) {
				birth[i] = tempBirthNumber[i] - 48;
			}
			printf("Date of Birth has been changed successfully.\n");
			system("pause");
			break;
		}
		else {
			printf("The only validated character is number, maximum string size of 8.\n");
			system("pause");
			continue;
		}

	}

}

void editPhone(int* phone) {

	char tempPhoneNumber[PHONENUMBER_MAXSIZE + 4] = "";

	// 휴대폰 번호 입력
	while (true) {
		system("cls");
		printf("Please enter a new Phone Number.: ");
		tempPhoneNumber[10] = '\0';
		fgets(tempPhoneNumber, PHONENUMBER_MAXSIZE + 4, stdin);
		tempPhoneNumber[strcspn(tempPhoneNumber, "\n")] = 0;

		// 메뉴로 이동
		if (tempPhoneNumber[0] == '~' && strlen(tempPhoneNumber) == 1) {
			return;
		}
		if (strlen(tempPhoneNumber) > PHONENUMBER_MAXSIZE + 2) {
			clearInputBuffer();
		}
		Eliminate(tempPhoneNumber, '-');

		if (tempPhoneNumber[10] == '\0') {
			bool flag = 1;
			for (int i = 0; i < 10; i++) {
				if (phone[i] != (tempPhoneNumber[i] - 48)) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				printf("It same as current info.");
				system("pause");
				continue;
			}
		}
		else if (tempPhoneNumber[11] == '\0') {
			bool flag = 1;
			for (int i = 0; i < 11; i++) {
				if (phone[i] != (tempPhoneNumber[i] - 48)) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				printf("It same as current info.");
				system("pause");
				continue;
			}
		}

		// fileCheck: 중복된 번호가 있는지 검사하는 함수
		if (duplicateCheck(tempPhoneNumber, PHONENUMBERCHECK)) {
			printf("Overlapped phone number, please try another one.\n");
			system("pause");
			continue;
		}

		if (matchPhoneNumber(tempPhoneNumber)) {
			//strcpy_s(phone, PHONENUMBER_MAXSIZE + 2, tempPhoneNumber);
			if (tempPhoneNumber[10] == '\0') {
				for (int i = 0; i < PHONENUMBER_MAXSIZE-1; i++) {
					phone[i] = tempPhoneNumber[i] - 48;
				}
				phone[10] = -1;
			}
			else if (tempPhoneNumber[11] == '\0') {
				for (int i = 0; i < PHONENUMBER_MAXSIZE; i++) {
					phone[i] = tempPhoneNumber[i] - 48;
				}
			}
			
			printf("Phone Number has been modified successfully.\n");
			system("pause");
			break;
		}
		else {
			if (isOnlyNumber(tempPhoneNumber) && strchr(tempPhoneNumber, '-') || isOnlyNumber(tempPhoneNumber)) {
				printf("Please enter the phone number in 10 or 11 digits.\n");
			}
			else {
				printf("Invalidated form of character has contained, please check again.\n");
			}
			system("pause");
			continue;
		}

	}

}