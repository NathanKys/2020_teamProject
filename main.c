#include <stdio.h>
#include "header.h"

int main() {

	Account login;
	int login_id_num = 2;	//2�� �׽�Ʈ�� ���� �ӽð�
	//�α����� ���̵� ��ȣ(= �α����� ������ DB �� ���° ������. 1������ ����)
	//�� ���� �� ���� ���� �Լ����� ���ڷ� �޾�, DB �� �ش� �ٿ� ���� ���
	int nextMenu = 0;
	do {
		switch (uiMainMenu()) {
			case 1:
				// ȸ������ �Լ�

				break;
			case 2:
				// �α��� �Լ�
				// return ���� login_id_num�� ����
				login = readAccountInfo(login_id_num); //�α����� ���� ���� ����ü�� ����

				do {
					switch (uiAfterLogin(login.nick)) {
						case 1:	// �� ���� ���� �Լ�

							nextMenu = uiShowMyInfo(login);
							break;
						case 2:
							// ����� �˻� �Լ�
							break;
						case 3:
							// ������ �Լ�
							break;
						case 4:
							break; //�α׾ƿ�
					}
				} while (uiAfterLogin(login.nick) != 4);

				break;
			case 3:
				// ���̵� �� ��й�ȣ ã�� �Լ�
				break;
			case 4:
				break; // �����ϱ�
		}
	} while (uiMainMenu() != 4);
}