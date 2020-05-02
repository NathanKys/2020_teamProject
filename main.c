#include <stdio.h>
#include "header.h"

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {

	Account login;	//�α����� ������ ���� ���� ����.
	Account targetAccount;	//������ �α��� �� ���� ��� ����
	int login_id_num = 2;	//���� �α��ε� ���̵��� DB�� ����. 1���� ����. -1�� ������ ���̵�
	//�α����� ���̵� ��ȣ(= �α����� ������ DB �� ���° ������. 1������ ����)
	//�� ���� �� ���� ���� �Լ����� ���ڷ� �޾�, DB �� �ش� �ٿ� ���� ���
	int nextMenu = 0;
	bool flag = 0;	//�α��� ����
	int num_account = 12;	//DB�� ��ϵ� ������ �� ����
	char** oldNick = (char**)malloc(sizeof(char*) * num_account);			//�г��� ����� ������ ���� �г��� ���

	bool programFlag = 1;
	do {
		switch (uiMainMenu()) {
			case 1:
				signUp();

				num_account++;	//ȸ������ �Ϸ� �� ���� ���� ����
				break;

			case 2:
				// �α��� �Լ� - ���ϰ��� DB�� ���° �ٿ� �ִ� ��������.(1���� ����)
				// return ���� login_id_num�� ����
				// ������ �α����� ��� -1�� ����
				flag = 1;

				if (login_id_num != -1) {	//�����ڰ� �ƴ� �Ϲ� ȸ�� �α����� ���

					login = readAccountInfo(login_id_num); //�α����� ���� ���� ����ü�� ����
					if (login.lock) {
						printf("��� �����Դϴ�. ���񽺸� �̿��� �� �����ϴ�.\n");
						system("pause");
						system("cls");
					}
					else {
						if (login.changed) {
							printf("�г����� ����Ǿ����ϴ�.\n");
							printf("���� �г���: %s\n", oldNick[login_id_num - 1]);
							printf("���ο� �г���: %s\n", login.nick);
							login.changed = 0;
							system("pause");
							system("cls");
						}
						while (flag) {
							switch (uiAfterLogin(login.nick)) {
								case 1:	// �� ���� ���� �Լ�
									while (uiShowMyInfo(&login) != 2) {

									}
									break;

								case 2:
									userSearch(&login, num_account);
									// ����� �˻� �Լ�
									break;

								case 3:
									messageBox(login.id);
									// ������ �Լ�
									break;

								case 4:
									flag = 0;
									writeAccountInfo(login_id_num, &login);
									break; //�α׾ƿ�
							}
						}
					}
				}
				else {	//������ �α���
					checkSecondPw();
					for (int i = 0; i < num_account; i++) {
						oldNick[i] = (char*)malloc(sizeof(char) * (NICKNAME_MAXSIZE + 2));
					}
					while (flag) {
						flag = adminMenu(num_account, &targetAccount, oldNick);
					}

				}

				break;
			case 3:
				// ���̵� �� ��й�ȣ ã�� �Լ�
				break;
			case 4:
				programFlag = 0;
				system("cls");
				break; // �����ϱ�
		}
	} while (programFlag);

	for (int i = 0; i < num_account; i++) {
		free(oldNick[i]);
	}

	free(oldNick);
}