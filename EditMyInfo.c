#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#pragma warning(disable:4098)

int checkPW(char* pw) {

	while (1) {
		system("cls");
		printf("본인 여부를 확인하기 위해 비밀번호를 다시 입력해주세요.");
		char t_pw[16] = "";
		char temp = ' ';
		for (int i = 0; i < 16; i++) {
			scanf("%c", &temp);
			if (temp == '\n')
				break;
			t_pw[i] = temp;
		}
		if (t_pw[0] == '~')
			return 0;
		if (!strcmp(pw, t_pw)) {
			return 1;
		}
		else {
			printf("비밀번호가 틀립니다.");
			system("pause");
		}
	}

}

void selectEdit(Account* login) {

	while (1) {
		system("cls");

		gotoxy(40, 1);
		printf("비밀번호(0)");

		gotoxy(20, 3);
		printf("아이디");
		gotoxy(20, 4);
		printf("%s\t", (*login).id);

		gotoxy(40, 3);
		printf("이름(1)");
		gotoxy(40, 4);
		printf("%s\t", (*login).name);

		gotoxy(60, 3);
		printf("닉네임(2)");
		gotoxy(60, 4);
		printf("%s\t", (*login).nick);

		gotoxy(20, 6);
		printf("생년월일(4)");
		gotoxy(20, 7);
		for (int i = 0; i < sizeof((*login).birth) / sizeof(int); i++) {
			printf("%d", (*login).birth[i]);
		}

		gotoxy(40, 6);
		printf("휴대폰 번호(5)");
		gotoxy(40, 7);
		for (int i = 0; i < sizeof((*login).phone) / sizeof(int); i++) {
			printf("%d", (*login).phone[i]);
		}

		gotoxy(60, 6);
		printf("이메일 주소(3)");
		gotoxy(60, 7);
		printf("%s\t", (*login).email);

		gotoxy(10, 16);
		printf("수정을 원하는 항목의 번호를 입력하세요: ");
		char num;
		scanf("%c", &num);
		if (num == '~')
			return;
		num = num - 48;
		if (!(0 <= num && num <= 5)) {
			printf("존재하지 않는 항목 번호입니다.");
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
	getchar();
	while (1) {
		system("cls");
		printf("새로운 비밀번호를 입력하세요: ");
		char t_pw[17] = "";
		for (int i = 0; i < 16; i++) {
			scanf("%c", &t_pw[i]);
			if (t_pw[i] == '\n') { t_pw[i] = '\0'; break; }
		}
		if (t_pw[0] == '~')
			return 0;
		if (!strcmp(pw, t_pw)) {
			printf("기존 정보와 동일합니다.");
			system("pause");
		}
		else {
			strcpy(pw, t_pw);
			printf("비밀번호 수정이 완료되었습니다.");
			system("pause");
			return 0;
		}
	}
}

void editName(char* name) {
	getchar();
	while (1) {
		system("cls");
		printf("새로운 이름을 입력하세요: ");
		char t_name[21] = "";
		for (int i = 0; i < 20; i++) {
			scanf("%c", &t_name[i]);
			if (t_name[i] == '\n') { t_name[i] = '\0'; break; }
		}
		if (t_name[0] == '~')
			return 0;
		if (!strcmp(name, t_name)) {
			printf("기존 정보와 동일합니다.");
			system("pause");
		}
		else {
			strcpy(name, t_name);
			printf("이름 수정이 완료되었습니다.");
			system("pause");
			return 0;
		}
	}
}

void editNick(char* nick) {
	getchar();
	while (1) {
		system("cls");
		printf("새로운 닉네임을 입력하세요: ");
		char t_nick[25] = "";
		for (int i = 0; i < 24; i++) {
			scanf("%c", &t_nick[i]);
			if (t_nick[i] == '\n') { t_nick[i] = '\0'; break; }
		}
		if (t_nick[0] == '~')
			return 0;
		if (!strcmp(nick, t_nick)) {
			printf("기존 정보와 동일합니다.");
			system("pause");
		}
		else if (1) {
			//닉네임 중복 체크 함수
			system("pause");
		}
		else {
			strcpy(nick, t_nick);
			printf("닉네임 수정이 완료되었습니다.");
			system("pause");
			return 0;
		}
	}
}

void editEmail(char* email) {
	getchar();
	while (1) {
		system("cls");
		printf("새로운 이메일 주소를 입력하세요: ");
		char t_email[31] = "";
		for (int i = 0; i < 30; i++) {
			scanf("%c", &t_email[i]);
			if (t_email[i] == '\n') { t_email[i] = '\0'; break; }
		}
		if (t_email[0] == '~')
			return 0;
		if (!strcmp(email, t_email)) {
			printf("기존 정보와 동일합니다.");
			system("pause");
		}
		else if (1) {
			//닉네임 중복 체크 함수
			system("pause");
		}
		else {
			strcpy(email, t_email);
			printf("이메일 주소 수정이 완료되었습니다.");
			system("pause");
			return 0;
		}
	}
}

void editBirth(int* birth) {
	getchar();
	while (1) {
		int flag = 0;
		system("cls");
		printf("새로운 생년월일을 입력하세요: ");
		int t_birth[6] = { 0, };
		char temp = ' ';
		for (int i = 0; i < 6; i++) {
			scanf("%c", &temp);
			if (temp == '\n') {
				printf("글자수 오류");
				flag = 1;
				system("pause");
				break;
			}
			t_birth[i] = temp - 48;
		}
		if (t_birth[0] == '~')
			return 0;
		for (int i = 0; i < 6; i++) {
			if (birth[i] == t_birth[i]) {
				flag = 2;
				break;
			}
		}
		if (flag == 2) {
			printf("기존 정보와 동일합니다.");
			system("pause");
		}
		else if (flag == 0) {
			for (int i = 0; i < 6; i++) {
				birth[i] = t_birth[i];
			}
			printf("생년월일 수정이 완료되었습니다.");
			system("pause");
			return 0;
		}
	}
}

void editPhone(int* phone) {
	getchar();
	while (1) {
		int flag = 0;
		system("cls");
		printf("새로운 휴대폰 번호를 입력하세요: ");
		int t_phone[11] = { 0, };
		char temp = ' ';
		for (int i = 0; i < 11; i++) {
			scanf("%c", &temp);
			if (temp == '\n') {
				printf("글자수 오류");
				flag = 1;
				system("pause");
				break;
			}
			t_phone[i] = temp - 48;
		}
		if (t_phone[0] == '~')
			return 0;
		for (int i = 0; i < 6; i++) {
			if (phone[i] == t_phone[i]) {
				flag = 2;
				break;
			}
		}
		if (flag == 2) {
			printf("기존 정보와 동일합니다.");
			system("pause");
		}
		else if (flag == 0) {
			for (int i = 0; i < 11; i++) {
				phone[i] = t_phone[i];
			}
			printf("휴대폰 번호 수정이 완료되었습니다.");
			system("pause");
			return 0;
		}
	}
}