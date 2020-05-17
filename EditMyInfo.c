#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#pragma warning(disable:4098)

int checkPW(char* pw) {

	while (1) {
		system("cls");

		gotoxy(5, 5);
		printf("본인 여부를 확인하기 위해 비밀번호를 다시 입력해주세요");
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
			printf("비밀번호가 틀립니다.");
			system("pause");
		}
	}

}

void selectEdit(Account* login) {

	while (1) {
		system("cls");

		gotoxy(5, 3);
		printf("===================================================================================");
		gotoxy(5, 4);
		printf("\t\t\t\t\t수정할 정보 선택"); // 텝 5개
		gotoxy(5, 5);
		printf("===================================================================================");

		gotoxy(40, 7);
		printf("비밀번호(0)");

		gotoxy(20, 9);
		printf("아이디");
		gotoxy(20, 10);
		printf("%s\t", (*login).id);

		gotoxy(40, 9);
		printf("이름(1)");
		gotoxy(40, 10);
		printf("%s\t", (*login).name);

		gotoxy(61, 9);
		printf("닉네임(2)");
		gotoxy(61, 10);
		printf("%s\t", (*login).nick);

		gotoxy(20, 12);
		printf("생년월일(4)");
		gotoxy(20, 13);
		for (int i = 0; i < 8; i++) {
			printf("%d", (*login).birth[i]);
		}

		gotoxy(40, 12);
		printf("휴대폰 번호(5)");
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
		printf("이메일 주소(3)");
		gotoxy(61, 13);
		printf("%s\t", (*login).email);

		gotoxy(10, 16);
		printf("수정을 원하는 항목의 번호를 입력하세요: ");

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
			printf("존재하지 않는 항목 번호입니다.\n");
			gotoxy(10, 18);
			system("pause");
		}
		else {
			switch (num) {
				case 0:	//비밀번호
					editPW(&((*login).pw));
					break;
				case 1:	//이름
					editName(&((*login).name));
					break;
				case 2:	//닉네임
					editNick(&((*login).nick));
					break;
				case 3:	//이메일 주소
					editEmail(&((*login).email));
					break;
				case 4:	//생년월일
					editBirth(&((*login).birth));
					break;
				case 5:	//휴대폰 번호
					editPhone(&((*login).phone));
					break;
			}
		}

	}
}

void editPW(char* pw) {

	char t_pw[PASSWORD_MAXSIZE + 2] = "";

	// 비밀번호 입력
	while (true) {
		system("cls");
		printf("새로운 비밀번호를 입력하세요: ");
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
			printf("기존 정보와 동일합니다.");
			system("pause");
			continue;
		}

		if (matchPassword(t_pw)) {
			if (strlen(t_pw) < 8 || strlen(t_pw) > 16) {
				printf("글자수 범위(최소 8자~최대 16자) 초과입니다.\n");
				system("pause");
				continue;
			}
			else {
				// 대문자 하나 이상
				// 소문자 하나 이상
				// 숫자 하나 이상
				if (!isContainUpperCase(t_pw)) { printf("알파벳 대문자를 하나 이상 포함해야 합니다.\n"); }
				if (!isContainLowerCase(t_pw)) { printf("알파벳 소문자를 하나 이상 포함해야 합니다.\n"); }
				if (!isContainNumber(t_pw)) { printf("인도-아라비아 숫자를 하나 이상 포함해야 합니다.\n"); }
				if (kreng(t_pw, strlen(t_pw))) { printf("비밀번호에는 한글을 허용하지 않습니다.\n"); }

				// 위의 세 조건을 모두 만족할 때
				if (isContainNumber(t_pw) && isContainUpperCase(t_pw) && isContainLowerCase(t_pw)) {
					// 반복된 문자 체크
					if (isRepeat(t_pw, strlen(t_pw))) {
						printf("비밀번호에 반복된 문자가 있습니다.\n");
						system("pause");
						continue;
					}
					// 연속된 문자 체크
					if (isConti(t_pw, strlen(t_pw))) {
						printf("비밀번호에 연속된 문자가 있습니다.\n");
						system("pause");
						continue;
					}

					printf("비밀번호 입력이 완료되었습니다.\n");
					system("pause");
					break;
				}
				system("pause");
				continue;
			}

		}
		else {
			printf("다음의 문자를 제외한 특수문자는 허용하지 않습니다.!@#$%^&*\n");
			system("pause");
			continue;
		}


	}

	//비밀번호 확인
	while (true) {
		system("cls");
		char checkPassword[PASSWORD_MAXSIZE + 2] = { 0, };
		printf("비밀번호 확인을 위해 다시 입력해주세요.");
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
			printf("비밀번호 확인&수정이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			printf("비밀번호와 일치하지 않습니다.\n");
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
		gotoxy(0, 1);
		printf("이름은 한글(최소 2자~최대 5자) 또는 영어 대소문자(최소 3자~최대 20자)로 구성됩니다.\n");
		printf("한글와 영어는 혼용하여 사용할 수 없습니다. 영어의 경우 띄어쓰기가 가능합니다.\n");
		gotoxy(0, 0);
		printf("새로운 이름을 입력하세요: ");
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
			printf("기존 정보와 동일합니다.");
			system("pause");
			continue;
		}

		if (kreng(t_name, strlen(t_name))) {
			if (isContainEng(t_name)) {
				printf("한글과 영어는 함께 사용할 수 없습니다.\n");
			}
			else {
				gotoxy(0, 4);
				printf("올바른 문자를 입력해주세요.\n");
			}
			system("pause");
			continue;
		}
		if (matchKorean(t_name, strlen(t_name))) {

			if (!isCompleteKorean(t_name, strlen(t_name))) {
				printf("올바른 문자를 입력해주세요.\n");
				system("pause");
				continue;
			}
			if (getLength(t_name) >= 2 && getLength(t_name) <= 5) {
				strcpy(name, t_name);
				printf("이름 수정이 완료되었습니다.\n");
				system("pause");
				break;
			}
			else {
				printf("한글은 공백을 포함하지 않고 2~5자를 입력해야 합니다.\n");
				system("pause");
				continue;
			}
		}
		else {
			if (matchEngName(t_name)) {
				if (getLength(t_name) >= 3 && getLength(t_name) <= 20) {
					strcpy(name, t_name);
					printf("이름 수정이 완료되었습니다.\n");
					system("pause");
					break;
				}
				else {
					printf("영어는 공백을 포함하여 3~20자를 입력해야 합니다.\n");
					system("pause");
					continue;
				}
			}
			else {
				printf("올바른 문자를 입력해주세요.\n");
				system("pause");
				continue;
			}
		}
	}

}

void editNick(char* nick) {

	char t_nick[NICKNAME_MAXSIZE + 2] = "";

	// 닉네임 입력
	while (true) {
		system("cls");
		gotoxy(0, 1);
		printf("닉네임에는 한글, 영어, 숫자, 띄어쓰기를 사용할 수 있습니다.(최소2자~최대12자)\n");
		gotoxy(0, 0);
		printf("새로운 닉네임을 입력하세요: ");

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
			printf("기존 정보와 동일합니다.");
			system("pause");
			continue;
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(t_nick, NICKNAMECHECK)) {
			printf("이미 존재하는 닉네임입니다.\n");
			system("pause");
			continue;
		}
		if (getLength(t_nick) < 2 || getLength(t_nick) > 12) {
			printf("닉네임은 한글, 영어, 숫자로 이루어진 2자~12자를 입력해야합니다.\n");
			system("pause");
			continue;
		}
		if (matchNickname(t_nick)) {
			strcpy(nick, t_nick);
			printf("닉네임 수정이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			printf("올바른 문자를 입력해주세요.\n");
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
		printf("새로운 이메일 주소를 입력하세요: ");

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
			printf("기존 정보와 동일합니다.");
			system("pause");
			continue;
		}

		// fileCheck: 중복된 아이디가 있는지 검사하는 함수
		if (duplicateCheck(t_email, EMAILCHECK)) {
			printf("이미 존재하는 이메일입니다.\n");
			system("pause");
			continue;
		}

		if (getLength(t_email) > 30) {
			printf("이메일은 30자를 초과할 수 없습니다.\n");
			system("pause");
			continue;
		}

		if (matchEmail(t_email)) {
			strcpy(email, t_email);
			printf("이메일 주소 수정이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			printf("올바른 형식의 이메일 주소를 입력해주세요.\n");
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
		printf("새로운 생년월일을 입력하세요: ");

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
				printf("기존 정보와 동일합니다.");
				system("pause");
				continue;
			}
		}

		if (isOnlyNumber(tempBirthNumber)) {
			if (strlen(tempBirthNumber) > 8) {
				printf("글자수 범위(숫자 8자) 초과입니다.\n");
				system("pause");
				continue;
			}
			else if (strlen(tempBirthNumber) == 8) {
				if (!isRightDate(tempBirthNumber)) {
					printf("존재하지 않는 날짜입니다.\n");
					system("pause");
					continue;
				}
			}
		}
		if (matchBirthday(tempBirthNumber)) {
			// 윤년 고려해서 없는 날짜 판단
			if (isInTheFuture(tempBirthNumber)) {
				printf("잘못된 생년월일입니다.\n");
				system("pause");
				continue;
			}
			// 프로그램 실행 이후 날짜 판단
			if (!isRightDate(tempBirthNumber)) {
				printf("존재하지 않는 날짜입니다.\n");
				system("pause");
				continue;
			}
			//strcpy_s(birth, BIRTHDAY_MAXSIZE + 2, tempBirthNumber);
			for (int i = 0; i < BIRTHDAY_MAXSIZE; i++) {
				birth[i] = tempBirthNumber[i] - 48;
			}
			printf("생년월일 수정이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			printf("숫자로만 이루어진 8자를 입력해주세요.\n");
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
		printf("새로운 휴대폰 번호를 입력하세요: ");
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
				printf("기존 정보와 동일합니다.");
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
				printf("기존 정보와 동일합니다.");
				system("pause");
				continue;
			}
		}

		// fileCheck: 중복된 번호가 있는지 검사하는 함수
		if (duplicateCheck(tempPhoneNumber, PHONENUMBERCHECK)) {
			printf("이미 존재하는 휴대폰 번호입니다.\n");
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
			if (tempPhoneNumber[11] == '\0') {
				for (int i = 0; i < PHONENUMBER_MAXSIZE; i++) {
					phone[i] = tempPhoneNumber[i] - 48;
				}
			}
			
			printf("전화번호 수정이 완료되었습니다.\n");
			system("pause");
			break;
		}
		else {
			if (isOnlyNumber(tempPhoneNumber) && strchr(tempPhoneNumber, '-') || isOnlyNumber(tempPhoneNumber)) {
				printf("전화번호는 10자리 또는 11자리로 입력해주세요.\n");
			}
			else {
				printf("올바르지 않은 문자가 포함되어 있습니다.\n");
			}
			system("pause");
			continue;
		}

	}

}