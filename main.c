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
	int num_account = 3;	//DB�� ��ϵ� ������ �� ����



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
				

				if (login_id_num != -1) {	//�����ڰ� �ƴ� �Ϲ� ȸ�� �α����� ���
					flag = 1;
					login = readAccountInfo(login_id_num); //�α����� ���� ���� ����ü�� ����
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
				else {	//������ �α���
					checkSecondPw();
					flag = 1;
					while (flag) {
						flag = adminMenu(num_account, &targetAccount);

					}
				}

				break;
			case 3:
				// ���̵� �� ��й�ȣ ã�� �Լ�
				break;
			case 4:
				system("cls");
				break; // �����ϱ�
		}
	} while (uiMainMenu() != 4);
}