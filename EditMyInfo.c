#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#pragma warning(disable:4098)

int checkPW(char* pw) {

	while (1) {
		system("cls");

		gotoxy(5, 5);
		printf("���� ���θ� Ȯ���ϱ� ���� ��й�ȣ�� �ٽ� �Է����ּ���");
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
			printf("��й�ȣ�� Ʋ���ϴ�.");
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
		printf("\t\t\t\t\t������ ���� ����"); // �� 5��
		gotoxy(5, 5);
		printf("===================================================================================");

		gotoxy(40, 7);
		printf("��й�ȣ(0)");

		gotoxy(20, 9);
		printf("���̵�");
		gotoxy(20, 10);
		printf("%s\t", (*login).id);

		gotoxy(40, 9);
		printf("�̸�(1)");
		gotoxy(40, 10);
		printf("%s\t", (*login).name);

		gotoxy(61, 9);
		printf("�г���(2)");
		gotoxy(61, 10);
		printf("%s\t", (*login).nick);

		gotoxy(20, 12);
		printf("�������(4)");
		gotoxy(20, 13);
		for (int i = 0; i < 8; i++) {
			printf("%d", (*login).birth[i]);
		}

		gotoxy(40, 12);
		printf("�޴��� ��ȣ(5)");
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
		printf("�̸��� �ּ�(3)");
		gotoxy(61, 13);
		printf("%s\t", (*login).email);

		gotoxy(10, 16);
		printf("������ ���ϴ� �׸��� ��ȣ�� �Է��ϼ���: ");

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
			printf("�������� �ʴ� �׸� ��ȣ�Դϴ�.\n");
			gotoxy(10, 18);
			system("pause");
		}
		else {
			switch (num) {
				case 0:	//��й�ȣ
					editPW(&((*login).pw));
					break;
				case 1:	//�̸�
					editName(&((*login).name));
					break;
				case 2:	//�г���
					editNick(&((*login).nick));
					break;
				case 3:	//�̸��� �ּ�
					editEmail(&((*login).email));
					break;
				case 4:	//�������
					editBirth(&((*login).birth));
					break;
				case 5:	//�޴��� ��ȣ
					editPhone(&((*login).phone));
					break;
			}
		}

	}
}

void editPW(char* pw) {

	char t_pw[PASSWORD_MAXSIZE + 2] = "";

	// ��й�ȣ �Է�
	while (true) {
		system("cls");
		printf("���ο� ��й�ȣ�� �Է��ϼ���: ");
		fgets(t_pw, PASSWORD_MAXSIZE + 2, stdin);

		t_pw[strcspn(t_pw, "\n")] = 0;

		// �޴��� �̵�
		if (t_pw[0] == '~' && strlen(t_pw) == 1) {
			return;
		}
		if (strlen(t_pw) > PASSWORD_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(pw, t_pw)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
			continue;
		}

		if (matchPassword(t_pw)) {
			if (strlen(t_pw) < 8 || strlen(t_pw) > 16) {
				printf("���ڼ� ����(�ּ� 8��~�ִ� 16��) �ʰ��Դϴ�.\n");
				system("pause");
				continue;
			}
			else {
				// �빮�� �ϳ� �̻�
				// �ҹ��� �ϳ� �̻�
				// ���� �ϳ� �̻�
				if (!isContainUpperCase(t_pw)) { printf("���ĺ� �빮�ڸ� �ϳ� �̻� �����ؾ� �մϴ�.\n"); }
				if (!isContainLowerCase(t_pw)) { printf("���ĺ� �ҹ��ڸ� �ϳ� �̻� �����ؾ� �մϴ�.\n"); }
				if (!isContainNumber(t_pw)) { printf("�ε�-�ƶ��� ���ڸ� �ϳ� �̻� �����ؾ� �մϴ�.\n"); }
				if (kreng(t_pw, strlen(t_pw))) { printf("��й�ȣ���� �ѱ��� ������� �ʽ��ϴ�.\n"); }

				// ���� �� ������ ��� ������ ��
				if (isContainNumber(t_pw) && isContainUpperCase(t_pw) && isContainLowerCase(t_pw)) {
					// �ݺ��� ���� üũ
					if (isRepeat(t_pw, strlen(t_pw))) {
						printf("��й�ȣ�� �ݺ��� ���ڰ� �ֽ��ϴ�.\n");
						system("pause");
						continue;
					}
					// ���ӵ� ���� üũ
					if (isConti(t_pw, strlen(t_pw))) {
						printf("��й�ȣ�� ���ӵ� ���ڰ� �ֽ��ϴ�.\n");
						system("pause");
						continue;
					}

					printf("��й�ȣ �Է��� �Ϸ�Ǿ����ϴ�.\n");
					system("pause");
					break;
				}
				system("pause");
				continue;
			}

		}
		else {
			printf("������ ���ڸ� ������ Ư�����ڴ� ������� �ʽ��ϴ�.!@#$%^&*\n");
			system("pause");
			continue;
		}


	}

	//��й�ȣ Ȯ��
	while (true) {
		system("cls");
		char checkPassword[PASSWORD_MAXSIZE + 2] = { 0, };
		printf("��й�ȣ Ȯ���� ���� �ٽ� �Է����ּ���.");
		fgets(checkPassword, PASSWORD_MAXSIZE + 2, stdin);
		checkPassword[strcspn(checkPassword, "\n")] = 0;
		if (strlen(checkPassword) > PASSWORD_MAXSIZE) {
			clearInputBuffer();
		}

		// �޴��� �̵�
		if (checkPassword[0] == '~' && strlen(checkPassword) == 1) {
			return;
		}

		if (!strcmp(checkPassword, t_pw)) {
			strcpy(pw, t_pw);
			printf("��й�ȣ Ȯ��&������ �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
			break;
		}
		else {
			printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
			system("pause");
			continue;
		}
	}
	
}

void editName(char* name) {

	char t_name[NAME_MAXSIZE + 2] = "";
	// �̸� �Է�
	while (true) {
		system("cls");
		gotoxy(0, 1);
		printf("�̸��� �ѱ�(�ּ� 2��~�ִ� 5��) �Ǵ� ���� ��ҹ���(�ּ� 3��~�ִ� 20��)�� �����˴ϴ�.\n");
		printf("�ѱۿ� ����� ȥ���Ͽ� ����� �� �����ϴ�. ������ ��� ���Ⱑ �����մϴ�.\n");
		gotoxy(0, 0);
		printf("���ο� �̸��� �Է��ϼ���: ");
		fgets(t_name, NAME_MAXSIZE + 2, stdin);
		t_name[strcspn(t_name, "\n")] = 0;

		gotoxy(0, 4);
		// �޴��� �̵�
		if (t_name[0] == '~' && strlen(t_name) == 1) {
			return;
		}
		if (strlen(t_name) > NAME_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(name, t_name)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
			continue;
		}

		if (kreng(t_name, strlen(t_name))) {
			if (isContainEng(t_name)) {
				printf("�ѱ۰� ����� �Բ� ����� �� �����ϴ�.\n");
			}
			else {
				gotoxy(0, 4);
				printf("�ùٸ� ���ڸ� �Է����ּ���.\n");
			}
			system("pause");
			continue;
		}
		if (matchKorean(t_name, strlen(t_name))) {

			if (!isCompleteKorean(t_name, strlen(t_name))) {
				printf("�ùٸ� ���ڸ� �Է����ּ���.\n");
				system("pause");
				continue;
			}
			if (getLength(t_name) >= 2 && getLength(t_name) <= 5) {
				strcpy(name, t_name);
				printf("�̸� ������ �Ϸ�Ǿ����ϴ�.\n");
				system("pause");
				break;
			}
			else {
				printf("�ѱ��� ������ �������� �ʰ� 2~5�ڸ� �Է��ؾ� �մϴ�.\n");
				system("pause");
				continue;
			}
		}
		else {
			if (matchEngName(t_name)) {
				if (getLength(t_name) >= 3 && getLength(t_name) <= 20) {
					strcpy(name, t_name);
					printf("�̸� ������ �Ϸ�Ǿ����ϴ�.\n");
					system("pause");
					break;
				}
				else {
					printf("����� ������ �����Ͽ� 3~20�ڸ� �Է��ؾ� �մϴ�.\n");
					system("pause");
					continue;
				}
			}
			else {
				printf("�ùٸ� ���ڸ� �Է����ּ���.\n");
				system("pause");
				continue;
			}
		}
	}

}

void editNick(char* nick) {

	char t_nick[NICKNAME_MAXSIZE + 2] = "";

	// �г��� �Է�
	while (true) {
		system("cls");
		gotoxy(0, 1);
		printf("�г��ӿ��� �ѱ�, ����, ����, ���⸦ ����� �� �ֽ��ϴ�.(�ּ�2��~�ִ�12��)\n");
		gotoxy(0, 0);
		printf("���ο� �г����� �Է��ϼ���: ");

		fgets(t_nick, NICKNAME_MAXSIZE + 2, stdin);
		t_nick[strcspn(t_nick, "\n")] = 0;

		gotoxy(0, 3);
		if (t_nick[0] == '~' && strlen(t_nick) == 1) {
			// �޴��� �̵�
			return;
		}
		if (strlen(t_nick) > NICKNAME_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(nick, t_nick)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
			continue;
		}

		// fileCheck: �ߺ��� ���̵� �ִ��� �˻��ϴ� �Լ�
		if (duplicateCheck(t_nick, NICKNAMECHECK)) {
			printf("�̹� �����ϴ� �г����Դϴ�.\n");
			system("pause");
			continue;
		}
		if (getLength(t_nick) < 2 || getLength(t_nick) > 12) {
			printf("�г����� �ѱ�, ����, ���ڷ� �̷���� 2��~12�ڸ� �Է��ؾ��մϴ�.\n");
			system("pause");
			continue;
		}
		if (matchNickname(t_nick)) {
			strcpy(nick, t_nick);
			printf("�г��� ������ �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
			break;
		}
		else {
			printf("�ùٸ� ���ڸ� �Է����ּ���.\n");
			system("pause");
			continue;
		}

	}

}

void editEmail(char* email) {

	char t_email[EMAILADDRESS_MAXSIZE + 2] = "";
	// �̸��� �ּ� �Է�
	while (true) {
		system("cls");
		printf("���ο� �̸��� �ּҸ� �Է��ϼ���: ");

		fgets(t_email, EMAILADDRESS_MAXSIZE + 2, stdin);
		t_email[strcspn(t_email, "\n")] = 0;

		// �޴��� �̵�
		if (t_email[0] == '~' && strlen(t_email) == 1) {
			return;
		}
		if (strlen(t_email) > EMAILADDRESS_MAXSIZE) {
			clearInputBuffer();
		}
		if (!strcmp(email, t_email)) {
			printf("���� ������ �����մϴ�.");
			system("pause");
			continue;
		}

		// fileCheck: �ߺ��� ���̵� �ִ��� �˻��ϴ� �Լ�
		if (duplicateCheck(t_email, EMAILCHECK)) {
			printf("�̹� �����ϴ� �̸����Դϴ�.\n");
			system("pause");
			continue;
		}

		if (getLength(t_email) > 30) {
			printf("�̸����� 30�ڸ� �ʰ��� �� �����ϴ�.\n");
			system("pause");
			continue;
		}

		if (matchEmail(t_email)) {
			strcpy(email, t_email);
			printf("�̸��� �ּ� ������ �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
			break;
		}
		else {
			printf("�ùٸ� ������ �̸��� �ּҸ� �Է����ּ���.\n");
			system("pause");
			continue;
		}
	}

}

void editBirth(int* birth) {

	char tempBirthNumber[BIRTHDAY_MAXSIZE + 2];
	//������� �Է�
	while (true) {
		system("cls");
		printf("���ο� ��������� �Է��ϼ���: ");

		fgets(tempBirthNumber, BIRTHDAY_MAXSIZE + 2, stdin);
		tempBirthNumber[strcspn(tempBirthNumber, "\n")] = 0;

		// �޴��� �̵�
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
				printf("���� ������ �����մϴ�.");
				system("pause");
				continue;
			}
		}

		if (isOnlyNumber(tempBirthNumber)) {
			if (strlen(tempBirthNumber) > 8) {
				printf("���ڼ� ����(���� 8��) �ʰ��Դϴ�.\n");
				system("pause");
				continue;
			}
			else if (strlen(tempBirthNumber) == 8) {
				if (!isRightDate(tempBirthNumber)) {
					printf("�������� �ʴ� ��¥�Դϴ�.\n");
					system("pause");
					continue;
				}
			}
		}
		if (matchBirthday(tempBirthNumber)) {
			// ���� ����ؼ� ���� ��¥ �Ǵ�
			if (isInTheFuture(tempBirthNumber)) {
				printf("�߸��� ��������Դϴ�.\n");
				system("pause");
				continue;
			}
			// ���α׷� ���� ���� ��¥ �Ǵ�
			if (!isRightDate(tempBirthNumber)) {
				printf("�������� �ʴ� ��¥�Դϴ�.\n");
				system("pause");
				continue;
			}
			//strcpy_s(birth, BIRTHDAY_MAXSIZE + 2, tempBirthNumber);
			for (int i = 0; i < BIRTHDAY_MAXSIZE; i++) {
				birth[i] = tempBirthNumber[i] - 48;
			}
			printf("������� ������ �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
			break;
		}
		else {
			printf("���ڷθ� �̷���� 8�ڸ� �Է����ּ���.\n");
			system("pause");
			continue;
		}

	}

}

void editPhone(int* phone) {

	char tempPhoneNumber[PHONENUMBER_MAXSIZE + 4] = "";

	// �޴��� ��ȣ �Է�
	while (true) {
		system("cls");
		printf("���ο� �޴��� ��ȣ�� �Է��ϼ���: ");
		tempPhoneNumber[10] = '\0';
		fgets(tempPhoneNumber, PHONENUMBER_MAXSIZE + 4, stdin);
		tempPhoneNumber[strcspn(tempPhoneNumber, "\n")] = 0;

		// �޴��� �̵�
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
				printf("���� ������ �����մϴ�.");
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
				printf("���� ������ �����մϴ�.");
				system("pause");
				continue;
			}
		}

		// fileCheck: �ߺ��� ��ȣ�� �ִ��� �˻��ϴ� �Լ�
		if (duplicateCheck(tempPhoneNumber, PHONENUMBERCHECK)) {
			printf("�̹� �����ϴ� �޴��� ��ȣ�Դϴ�.\n");
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
			
			printf("��ȭ��ȣ ������ �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
			break;
		}
		else {
			if (isOnlyNumber(tempPhoneNumber) && strchr(tempPhoneNumber, '-') || isOnlyNumber(tempPhoneNumber)) {
				printf("��ȭ��ȣ�� 10�ڸ� �Ǵ� 11�ڸ��� �Է����ּ���.\n");
			}
			else {
				printf("�ùٸ��� ���� ���ڰ� ���ԵǾ� �ֽ��ϴ�.\n");
			}
			system("pause");
			continue;
		}

	}

}