#include <stdio.h>
#include "header.h"

int main () {
int number1, number2;
int login_id_num = 2;	//2�� �׽�Ʈ�� ���� �ӽð�
//�α����� ���̵� ��ȣ(= �α����� ������ DB �� ���° ������. 1������ ����)
//�� ���� �� ���� ���� �Լ����� ���ڷ� �޾�, DB �� �ش� �ٿ� ���� ���
	do {
		number1 = menu1(1);
		switch (number1) {
		case 1:
			// �α��� �Լ�
			// return ���� login_id_num�� ����
			number2 = menu1(2);
			do {
				switch (number2) {
				case 1:
					// ������ ���� �Լ�
					//readAccount(login_id_num);
					
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
			}while (number2 != 4);
			break;
		case 2:
			// ȸ������ �Լ�
			break;
		case 3:
			// ���̵� �� ��й�ȣ ã�� �Լ�
			break;
		case 4:
			break; // �����ϱ�
		}
	} while (number1 != 4);
}
