
#include <stdio.h>
#include "header.h"

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {

	Account login;	//로그인한 계정의 계정 정보 저장.
	Account targetAccount;	//관리자 로그인 시 관리 대상 계정
	int login_id_num = 0;	//현재 로그인된 아이디의 DB상 순서. 1부터 시작. -1은 관리자 아이디
	//로그인한 아이디 번호(= 로그인한 계정이 DB 상 몇번째 줄인지. 1번부터 시작)
	//이 값을 내 정보 보기 함수에서 인자로 받아, DB 상 해당 줄에 정보 출력
	bool flag = 0;	//로그인 상태
	int num_account = 0;	//DB에 등록된 계정의 총 개수
	num_account = readAccountNum();

	bool programFlag = 1;
	do {
		switch (uiMainMenu()) {
		case 1:
			if (signUp() == 1) {
				num_account++; //회원가입 완료 시 계정 개수 증가
			}
			break;

		case 2:

			//***login_id_num = loginFunction(&num_account); // return 값을 login_id_num에 복사
			login_id_num = 1;	//(임시)테스트를 위해 로그인 과정을 거치시 않도록 설정
			system("cls");
			// 관리자 로그인의 경우 -1을 리턴
			flag = 1;

			if (login_id_num == 0) {            
				break;
			}
				
				if (login_id_num != -1) {	//관리자가 아닌 일반 회원 로그인일 경우

				login = readAccountInfo(login_id_num); //로그인한 계정 정보 구조체에 저장
				if (login.lock) {
					printf("This account is locked. The service is not available.\n");
					system("pause");
					system("cls");
				}
				else {
					while (flag) {
						switch (uiAfterLogin(login.nick)) {
						case 1:	// 내 정보 보기 함수
							while (uiShowMyInfo(&login, login_id_num) != 2) {

							}
							break;

						case 2:
							userSearch(&login, num_account);
							// 사용자 검색 함수
							break;

						case 3:
							messageBox(login.id);
							// 쪽지함 함수
							break;

						case 4:
							flag = 0;
							break; //로그아웃
						case 5:
							login = readAccountInfo(login_id_num);
							subAdminMenu(num_account, &targetAccount, login_id_num, login.id);
							// 보조 관리자 메뉴
						}
					}
				}
			}
			else {	//관리자 로그인
				checkSecondPw();
				
				while (flag) {
					flag = adminMenu(num_account, &targetAccount);
				}
				
			}

			break;
		case 3:
			if (num_account == 0) {
				printf("계정 없음");
				break;
			}
			findaccount(num_account);
			break;
		case 4:
			programFlag = 0;
			system("cls");
			break; // 종료하기
		}
	} while (programFlag);


}
