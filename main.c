#include <stdio.h>
#include "header.h"

int main() {

	Account login;
	int login_id_num = 2;	//2�� �׽�Ʈ�� ���� �ӽð�
	//�α����� ���̵� ��ȣ(= �α����� ������ DB �� ���° ������. 1������ ����)
	//�� ���� �� ���� ���� �Լ����� ���ڷ� �޾�, DB �� �ش� �ٿ� ���� ���
	int nextMenu = 0;
	bool flag = 1;
	do {
		switch (uiMainMenu()) {
			case 1:
				// ȸ������ �Լ�

				break;
			case 2:
				// �α��� �Լ�
				// return ���� login_id_num�� ����
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