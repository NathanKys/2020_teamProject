#include "header.h"

int checkPW(char* pw) {

	while (1) {
		printf("���� ���θ� Ȯ���ϱ� ���� ��й�ȣ�� �ٽ� �Է����ּ���.");
		char t_pw[13];
		for (int i = 0; i < 12; i++) {
			scanf("%c", t_pw[i]);
		}
		if (t_pw[0] == '~')
			return 0;
		if (!strcmp(pw, t_pw)) {
			return 1;
		}
		else {
			printf("��й�ȣ�� Ʋ���ϴ�.");
			system("pause");
		}
	}

}

int selectEdit(Account login) {

	while (1) {
		system("cls");

		gotoxy(40, 1);
		printf("��й�ȣ(0)");

		gotoxy(20, 3);
		printf("���̵�");
		gotoxy(20, 4);
		printf("%s\t", login.id);

		gotoxy(40, 3);
		printf("�̸�(1)");
		gotoxy(40, 4);
		printf("%s\t", login.name);

		gotoxy(60, 3);
		printf("�г���(2)");
		gotoxy(60, 4);
		printf("%s\t", login.nick);

		gotoxy(20, 6);
		printf("�������(4)");
		gotoxy(20, 7);
		for (int i = 0; i < sizeof(login.birth) / sizeof(int); i++) {
			printf("%d", login.birth[i]);
		}

		gotoxy(40, 6);
		printf("�޴��� ��ȣ(5)");
		gotoxy(40, 7);
		for (int i = 0; i < sizeof(login.phone) / sizeof(int); i++) {
			printf("%d", login.phone[i]);
		}

		gotoxy(60, 6);
		printf("�̸��� �ּ�(3)");
		gotoxy(60, 7);
		printf("%s\t", login.email);

		gotoxy(10, 16);
		printf("������ ���ϴ� �׸��� ��ȣ�� �Է��ϼ���.");
		char num;
		scanf("%c", &num);
		if (num == '~')
			return;
		num = num - 48;
		if (!(0 <= num && num <= 5)) {
			printf("�������� �ʴ� �׸� ��ȣ�Դϴ�.");
			system("pause");
		}
		else {
			switch (num) {
				case 0:	//��й�ȣ
					editPW(login.pw);
					break;
				case 1:	//�̸�
					editName(login.name);
					break;
				case 2:	//�г���
					editNick(login.nick);
					break;
				case 3:	//�̸��� �ּ�
					editEmail(login.email);
					break;
				case 4:	//�������
					editBirth(login.birth);
					break;
				case 5:	//�޴��� ��ȣ
					editPhone(login.phone);
					break;
			}
		}

	}
}

void editPW(char * pw) {

	while (1) {
		system("cls");
		printf("���ο� ��й�ȣ�� �Է��ϼ���.");
		char t_pw[17];
		for (int i = 0; i < 16; i++) {
			scanf("%c", t_pw[i]);
			if (t_pw[i] == '\n')
				break;
		}
		if (t_pw[0] == '~')
			return 0;
		if (strcmp(pw, t_pw)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
		}
		else {
			strcpy(pw, t_pw);
			printf("��й�ȣ ������ �Ϸ�Ǿ����ϴ�.");
			system("pause");
			return 0;
		}
	}
}

void editName(char* name) {

	while (1) {
		system("cls");
		printf("���ο� �̸��� �Է��ϼ���.");
		char t_pw[21];
		for (int i = 0; i < 20; i++) {
			scanf("%c", t_pw[i]);
			if (t_pw[i] == '\n')
				break;
		}
		if (t_pw[0] == '~')
			return 0;
		if (strcmp(name, t_pw)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
		}
		else {
			printf("�̸� ������ �Ϸ�Ǿ����ϴ�.");
			system("pause");
			return 0;
		}
	}
}

void editNick(char* nick) {

	while (1) {
		system("cls");
		printf("���ο� �г����� �Է��ϼ���.");
		char t_nick[25];
		for (int i = 0; i < 24; i++) {
			scanf("%c", t_nick[i]);
			if (t_nick[i] == '\n')
				break;
		}
		if (t_nick[0] == '~')
			return 0;
		if (strcmp(nick, t_nick)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
		}
		else if (1) {
			//�г��� �ߺ� üũ �Լ�
			system("pause");
		}
		else {
			printf("�г��� ������ �Ϸ�Ǿ����ϴ�.");
			system("pause");
			return 0;
		}
	}
}

void editEmail(char* email) {

	while (1) {
		system("cls");
		printf("���ο� �̸��� �ּҸ� �Է��ϼ���.");
		char t_email[31];
		for (int i = 0; i < 30; i++) {
			scanf("%c", t_email[i]);
			if (t_email[i] == '\n')
				break;
		}
		if (t_email[0] == '~')
			return 0;
		if (strcmp(email, t_email)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
		}
		else if (1) {
			//�г��� �ߺ� üũ �Լ�
			system("pause");
		}
		else {
			printf("�̸��� �ּ� ������ �Ϸ�Ǿ����ϴ�.");
			system("pause");
			return 0;
		}
	}
}

void editBirth(int* birth) {

	while (1) {
		int flag = 0;
		system("cls");
		printf("���ο� ��������� �Է��ϼ���.");
		int t_birth[6];
		char temp = ' ';
		for (int i = 0; i < 6; i++) {
			scanf("%c", &temp);
			if (temp == '\n') {
				printf("���ڼ� ����");
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
			printf("���� ������ �����մϴ�.");
			system("pause");
		}
		else if(flag == 0) {
			for (int i = 0; i < 6; i++) {
				birth[i] = t_birth[i];
			}
			printf("������� ������ �Ϸ�Ǿ����ϴ�.");
			system("pause");
			return 0;
		}
	}
}

void editPhone(int* phone) {

	while (1) {
		int flag = 0;
		system("cls");
		printf("���ο� �޴��� ��ȣ�� �Է��ϼ���.");
		int t_phone[11];
		char temp = ' ';
		for (int i = 0; i < 11; i++) {
			scanf("%c", &temp);
			if (temp == '\n') {
				printf("���ڼ� ����");
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
			printf("���� ������ �����մϴ�.");
			system("pause");
		}
		else if (flag == 0) {
			for (int i = 0; i < 11; i++) {
				phone[i] = t_phone[i];
			}
			printf("�޴��� ��ȣ ������ �Ϸ�Ǿ����ϴ�.");
			system("pause");
			return 0;
		}
	}
}