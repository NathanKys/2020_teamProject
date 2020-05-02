#include <stdio.h>
#include "header.h"

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {

	Account login;
	Account targetAccount;	//������ �α��� �� ���� ��� ����
	int login_id_num = -1;	//���� �α��ε� ���̵��� DB�� ����. -1�� ������ ���̵�
	//�α����� ���̵� ��ȣ(= �α����� ������ DB �� ���° ������. 1������ ����)
	//�� ���� �� ���� ���� �Լ����� ���ڷ� �޾�, DB �� �ش� �ٿ� ���� ���
	int nextMenu = 0;
	bool flag = 0;	//�α��� ����
	int num_account = 12;	//DB�� ��ϵ� ������ �� ����

	bool programFlag = 1;
	do {
		switch (uiMainMenu()) {
			case 1:
				// ȸ������ �Լ�

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
							printf("���� �г���: ");
							printf("���ο� �г���: %s", login.nick);
							login.changed = 0;
							system("cls");
							system("pause");
						}
						while (flag) {
							switch (uiAfterLogin(login.nick)) {
								case 1:	// �� ���� ���� �Լ�
									while (uiShowMyInfo(&login) != 2) {

									}
									break;

								case 2:
									// ����� �˻� �Լ�
									break;

								case 3:
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
					while (flag) {
						flag = adminMenu(num_account, &targetAccount);
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
}