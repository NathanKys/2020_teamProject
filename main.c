#include <stdio.h>
#include "header.h"

int main() {

	Account login;
	int login_id_num = 2;	//2는 테스트를 위한 임시값
	//로그인한 아이디 번호(= 로그인한 계정이 DB 상 몇번째 줄인지. 1번부터 시작)
	//이 값을 내 정보 보기 함수에서 인자로 받아, DB 상 해당 줄에 정보 출력
	int nextMenu = 0;
	bool flag = 1;
	do {
		switch (uiMainMenu()) {
			case 1:
				// 회원가입 함수

				break;
			case 2:
				// 로그인 함수
				// return 값을 login_id_num에 복사
				login = readAccountInfo(login_id_num); //로그인한 계정 정보 구조체에 저장

				while (flag) {
					switch (uiAfterLogin(login.nick)) {
						case 1:	// 내 정보 보기 함수

							while (uiShowMyInfo(&login) != 2) {



							}

							break;
						case 2:
							// 사용자 검색 함수
							break;
						case 3:
							// 쪽지함 함수
							break;
						case 4:
							flag = 0;
							writeAccountInfo(login_id_num, &login);
							break; //로그아웃
					}
				}

				break;
			case 3:
				// 아이디 및 비밀번호 찾기 함수
				break;
			case 4:
				system("cls");
				break; // 종료하기
		}
	} while (uiMainMenu() != 4);
}