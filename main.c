#include <stdio.h>
#include "header.h"

int main() {

	Account login;
	int login_id_num = 2;	//2�� �׽�Ʈ�� ���� �ӽð�
	//�α����� ���̵� ��ȣ(= �α����� ������ DB �� ���° ������. 1������ ����)
	//�� ���� �� ���� ���� �Լ����� ���ڷ� �޾�, DB �� �ش� �ٿ� ���� ���
	int nextMenu = 0;
	bool flag = 0;	//�α��� ����



	do {
		switch (uiMainMenu()) {
			case 1:
				// ȸ������ �Լ�

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